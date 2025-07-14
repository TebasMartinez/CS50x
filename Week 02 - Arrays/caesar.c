// Encrypts a user generated message with a user generated key following Caesar’s encryption algorithm

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // If program is executed without any command-line arguments or with more than one command-line
    // argument, print error message & return 1

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // If any of the characters of the command-line argument is not a decimal digit,
    // print error message & return 1
    for (int i = 0, j = strlen(argv[1]); i < j; i++)
    {
        int arg = isdigit(argv[1][i]);
        if (arg == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Argv[1] is a non-negative integer
    int arg = atoi(argv[1]);
    if (arg < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Prompt user for "plaintext:  "
    string plaintext = get_string("plainttext:  ");

    // For each character in plaintext
    for (int i = 0, j = strlen(plaintext); i < j; i++)
    {
        // Check if it's a letter
        int letter = isalpha(plaintext[i]);
        if (letter != 0)
        {
            // Check if letter is upper case
            int upper = isupper(plaintext[i]);
            if (upper != 0)
            {
                // Encrypt upper case letter
                plaintext[i] = ((plaintext[i] - 65 + arg) % 26) + 65;
            }
            else
            {
                // Encrypt lower case letter
                plaintext[i] = ((plaintext[i] - 97 + arg) % 26) + 97;
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}
