#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);
void print_bricks(int bricks);

int main(void)
{
    // Prompt the user for the pyramid's height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Print a pyramid of that height
    int spaces = n - 1;
    for (int i = 0; i < n; i++)
    {
        // Print row of bricks
        print_row(spaces, i + 1);
        spaces--;
    }
}

void print_row(int spaces, int bricks)
{
    // Print spaces
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    // Print first line of bricks
    print_bricks(bricks);

    // Print gaps
    printf("  ");

    // Print second line of bricks
    print_bricks(bricks);

    printf("\n");
}

void print_bricks(int bricks)
{
    // Print bricks
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}
