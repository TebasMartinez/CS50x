import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        if not request.form.get("addcash"):
            return apology("cash amount missing", 400)
        else:
            currentcash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            newcash = currentcash[0]["cash"] + int(request.form.get("addcash"))
            db.execute ("UPDATE users SET cash = ? WHERE id = ?", newcash, session["user_id"])
            return redirect("/")
    else:
        shares = db.execute("SELECT id, date, symbol, SUM(shares) as shares, user_id, price FROM purchases WHERE user_id = ? GROUP BY symbol", session["user_id"])
        grandtotal = 0
        for share in shares:
            quote = lookup(share["symbol"])
            share["price"] = quote["price"]
            share["total"] = share["price"] * share["shares"]
            grandtotal = grandtotal + share["total"]
            share["price"] = usd(share["price"])
            share["total"] = usd(share["total"])

        cashdic = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = usd(cashdic[0]["cash"])
        grandtotal = usd(grandtotal)
        return render_template("index.html", shares=shares, cash=cash, grandtotal=grandtotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        if lookup(request.form.get("symbol")) == None:
            return apology("symbol doesn't exist", 400)
        if not request.form.get("shares"):
            return apology("must provide number of shares", 400)
        shares_str = request.form.get("shares")
        if not shares_str.isdigit():
            return apology("shares must be a positive integer", 400)
        if int(request.form.get("shares")) <= 0:
            return apology("must provide a positive number of shares", 400)
        s = lookup(request.form.get("symbol"))
        currentprice = s["price"]
        sharesprice = currentprice * int(request.form.get("shares"))
        cash_row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash_row[0]["cash"]
        if sharesprice > cash:
            return apology("can't afford that number of shares", 400)
        else:
            db.execute("INSERT INTO purchases (date, symbol, shares, user_id, price) VALUES (?, ?, ?, ?, ?)", datetime.now(), request.form.get("symbol"), request.form.get("shares"), session["user_id"], currentprice)
            currentcash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            remainingcash = currentcash[0]["cash"] - sharesprice
            db.execute("UPDATE users SET cash = ? WHERE id = ?", remainingcash, session["user_id"])
            return redirect("/")
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT id, date, symbol, user_id, price, shares FROM purchases WHERE user_id = ?", session["user_id"])
    for transaction in transactions:
        transaction["price"] = usd(transaction["price"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("invalid symbol", 400)
        s = lookup(request.form.get("symbol"))
        if s == None:
            return apology("invalid symbol", 400)
        return render_template("quoted.html", name=s["name"], symbol=s["symbol"], price=usd(s["price"]))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        if not request.form.get("password"):
            return apology("must provide password", 400)
        if not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("confirmation doesn't match password", 400)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password"), method='scrypt', salt_length=16))
        except ValueError:
            return apology("username already exists", 400)
        return redirect("/")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        shares = db.execute("SELECT id, date, symbol, SUM(shares) as shares, user_id, price FROM purchases WHERE user_id = ? GROUP BY symbol", session["user_id"])
        symbol_list = [share["symbol"] for share in shares]
        if not request.form.get("symbol"):
            return apology("must select a stock", 400)
        if request.form.get("symbol") not in symbol_list:
                return apology("must select a stock you own", 400)
        if int(request.form.get("shares")) < 1:
            return apology("must sell a positive number a shares", 400)
        currentshares = db.execute("SELECT SUM(shares) as shares FROM purchases WHERE user_id = ? AND symbol = ? GROUP BY symbol", session["user_id"], request.form.get("symbol"))
        if int(request.form.get("shares")) > currentshares[0]["shares"]:
            return apology("user doesn't own enough shares", 400)
        s = lookup(request.form.get("symbol"))
        currentprice = s["price"]
        db.execute("INSERT INTO purchases (date, symbol, shares, user_id, price) VALUES (?, ?, ?, ?, ?)", datetime.now(), request.form.get("symbol"), -int(request.form.get("shares")), session["user_id"], currentprice)
        currentcash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        remainingcash = currentcash[0]["cash"] + (currentprice * int(request.form.get("shares")))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remainingcash, session["user_id"])
        return redirect("/")
    else:
        symbols = db.execute("SELECT symbol FROM purchases WHERE user_id = ? GROUP BY symbol", session["user_id"])
        symbol_list = [symbol["symbol"] for symbol in symbols]
        return render_template("sell.html", symbol_list=symbol_list)
