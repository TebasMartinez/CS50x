from cs50 import get_string


def main():
    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # index = 0.0588 * L - 0.296 * S - 15.8

    L = letters / (words / 100)
    S = sentences / (words / 100)
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    sum = 0
    for c in text:
        if c.isalpha():
            sum += 1
    return sum


def count_words(text):
    # Number of words equals the number of spaces + 1
    sum = 1
    for c in text:
        if c == " ":
            sum += 1
    return sum


def count_sentences(text):
    sum = 0
    for c in text:
        if c in (".", "?", "!"):
            sum += 1
    return sum


main()
