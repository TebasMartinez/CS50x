#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Prompt the user for the pyramid's height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // Print a pyramid of hat height
    int m = n - 1;
    for (int i = 0; i < n; i++)
    {
        // Print row of bricks
        print_row(m, i + 1);
        m--;
    }
}

void print_row(int spaces, int bricks)
{
    // Print spaces
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    // Print bricks
    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }
    printf("\n");
}
