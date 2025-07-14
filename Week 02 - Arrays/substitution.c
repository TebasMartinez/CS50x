#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int checkalpha(string key);
int checkall(string key);

string upperalphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string loweralphabet = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, string argv[])
{
    string key = argv[1];

    // If program is executed without any command-line arguments or with more than one command-line
    // argument, print error message & return 1

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // If the key is invalid (as by not containing 26 characters, containing any character that is
    // not an alphabetic character, or not containing each letter exactly once)
    int lenght = strlen(argv[1]);
    if (lenght != 26 || checkalpha(key) == 1 || checkall(key) == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Request plain text
    string plaintext = get_string("plaintext: ");
    char ciphertext[strlen(plaintext) + 1]; // +1 for NULL value closing the string

    // For each character in plaintext
    for (int i = 0, j = strlen(plaintext); i < j; i++)
    {
        // Check if it's a letter
        if (isalpha(plaintext[i]))
        {
            // Check if letter is upper case
            if (isupper(plaintext[i]))
            {
                // Encrypt upper case letter
                for (int k = 0; k < 26; k++)
                {
                    if (plaintext[i] == upperalphabet[k])
                    {
                        ciphertext[i] = toupper(key[k]);
                    }
                }
            }
            else
            {
                // Encrypt lower case letter
                for (int k = 0; k < 26; k++)
                {
                    if (plaintext[i] == loweralphabet[k])
                    {
                        ciphertext[i] = tolower(key[k]);
                    }
                }
            }
        }
        else
        {
            for (int k = 0; k < 26; k++)
            {
                ciphertext[i] = plaintext[i];
            }
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

// Check that all characters in the key are alphabetical
int checkalpha(string key)
{
    for (int i = 0, j = strlen(key); i < j; i++)
    {
        int letter = isalpha(key[i]);
        if (letter == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Check that each letter appears in the key exactly once
int checkall(string key)
{
    bool seen[26] = {false};
    for (int i = 0, j = strlen(key); i < j; i++)
    {
        for (int k = 0; k < 26; k++)
        {
            if (key[i] == upperalphabet[k] || key[i] == loweralphabet[k])
            {
                seen[k] = true;
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (seen[i] != true)
        {
            return 1;
        }
    }
    return 0;
}
