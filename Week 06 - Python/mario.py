from cs50 import get_int

height = get_int("Height: ")
bricks = 1

while height > 8 or height < 1:
    height = get_int("Height: ")

while height > 0:
    print(" " * (height - 1), "#" * bricks, "  ", "#" * bricks, sep="")
    height -= 1
    bricks += 1
