from cs50 import get_string


def main():
    creditcard = get_string("Number: ")
    if checksum(creditcard) != 0:
        print("INVALID")

    # Check if Check if AMEX (15 digits, starts with 34 or 37)
    elif getdigit(15, creditcard) == 3 and getdigit(14, creditcard) in (4, 7):
        print("AMEX")
    # Check if MASTERCARD (16 digits, starts with 51, 52, 53, 54, or 55)
    elif getdigit(16, creditcard) == 5 and getdigit(15, creditcard) in (1, 2, 3, 4, 5):
        print("MASTERCARD")
    # Check if VISA (13 or 16 digits, starts with 4)
    elif getdigit(13, creditcard) == 4 or getdigit(16, creditcard) == 4:
        print("VISA")
    # Credit card passes checksum, but it's not a registered number
    else:
        print("INVALID")

# Get individual credit card digit from right to left


def getdigit(digitposition, creditcard):
    digit = (int(creditcard) // 10 ** (digitposition - 1) % 10)
    return digit


def checksum(creditcard):
    sumevens = 0
    sumodds = 0
    digitposition = 1

    for n in creditcard:
        # Multiply every other digit by 2, starting with the number’s second-to-last digit, and then
        # add those products’ digits together.
        digit = getdigit(digitposition, creditcard)
        if (digitposition % 2 == 0):
            sumevens = sumevens + ((digit*2) // 10) + ((digit * 2) % 10)
        else:
            # Add digits that weren't multiplied by 2
            sumodds = sumodds + digit
        digitposition += 1

    # Add both sums
    sumboth = sumevens + sumodds

    # Return last digit of the total
    total = sumboth % 10
    return total


main()
