// Calculates the approximate (US) grade level needed to comprehend a given text

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    // index = 0.0588 * L - 0.296 * S - 15.8,
    // L = average number of letters per 100 words in the text,
    // S = average number of sentences per 100 words in the text
    float L = letters / (words / 100.0);
    float S = sentences / (words / 100.0);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int roundindex = (int) round(index);

    // Print the grade level
    if (roundindex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (roundindex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", roundindex);
    }
}

int count_letters(string text)
{
    // Return the number of letters in text
    int sum = 0;
    for (int i = 0, t = strlen(text); i < t; i++)
    {
        int current_char = isalpha(text[i]);
        if (current_char != 0)
        {
            sum++;
        }
    }
    return sum;
}

int count_words(string text)
{
    // Return the number of words in text. The number of words in a text is equal to the number of
    // spaces + 1 (because of the first word)
    int sum = 1;
    for (int i = 0, t = strlen(text); i < t; i++)
    {
        if (text[i] == ' ')
        {
            sum++;
        }
    }
    return sum;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
    int sum = 0;
    for (int i = 0, t = strlen(text); i < t; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sum++;
        }
    }
    return sum;
}
