#define _GNU_SOURCE /* See feature_test_macros(7) */
#include <cs50.h>
#include <math.h>
#include <stdio.h>

long get_digit(long digitposition, long creditcard);
long checksum(long creditcard);
long pd(long evennumber);

int main(void)
{
    // Check credit card validity
    long creditcard = get_long("Number: ");
    if (checksum(creditcard) != 0)
    {
        printf("INVALID\n");
    }

    // Check if AMEX (15 digits, starts with 34 or 37)
    else if (get_digit(15, creditcard) == 3 &&
             (get_digit(14, creditcard) == 4 || get_digit(14, creditcard) == 7))
    {
        printf("AMEX\n");
    }

    // Check if MASTERCARD (16 digits, starts with 51, 52, 53, 54, or 55)
    else if (get_digit(16, creditcard) == 5 &&
             (get_digit(15, creditcard) == 1 || get_digit(15, creditcard) == 2 ||
              get_digit(15, creditcard) == 3 || get_digit(15, creditcard) == 4 ||
              get_digit(15, creditcard) == 5))
    {
        printf("MASTERCARD\n");
    }

    // Check if VISA (13 or 16 digits, starts with 4)
    else if (get_digit(13, creditcard) == 4 || get_digit(16, creditcard) == 4)
    {
        printf("VISA\n");
    }

    // Credit card passes checksum, but it's not a registered number
    else
    {
        printf("INVALID\n");
    }
}

// Get individual credit card digit from right to left
long get_digit(long digitposition, long creditcard)
{
    if (digitposition == 1)
    {
        long digit = creditcard % (long) exp10(1);
        return digit;
    }
    else
    {
        long digit = (creditcard / (long) exp10(digitposition - 1)) % (long) exp10(1);
        return digit;
    }
}

long checksum(long creditcard)
{
    // Find digits in credit card, from right to left

    long sumevens = 0;
    long sumodds = 0;
    for (int i = 1; i <= 16; i++)
    {
        long digit = get_digit(i, creditcard);
        if (i % 2 == 0)
        {
            // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then
            // add those products’ digits together.
            sumevens = sumevens + pd(digit * 2);
        }
        else
        {
            // Add digits that weren't multiplied by 2
            sumodds = sumodds + digit;
        }
    }

    // Add both sums
    long sumboth = sumevens + sumodds;

    // Return last digit of the total
    long total = sumboth % 10;
    return total;
}

// Add even digits' products' digits
long pd(long evennumber)
{
    long result = (evennumber / 10) + (evennumber % 10);
    return result;
}
