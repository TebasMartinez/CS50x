#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int checkscore(string word);

int main(void)
{
    // Prompt the user for two words
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // Compute the score of each word
    int p1 = checkscore(player1);
    int p2 = checkscore(player2);

    // Print scores and the winner
    if (p1 > p2)
    {
        printf("Player 1 wins!\n");
    }
    else if (p2 > p1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int checkscore(string word)
{
    int score = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Check if the character is a letter
        int m = isalpha(word[i]);
        if (m != 0)
        {
            // Change each letter to uppercase
            word[i] = toupper(word[i]);

            // Sum score of each letter to main score
            score += POINTS[word[i] - 65];
        }
        else
        {
            score += 0;
        }
    }
    return score;
}
