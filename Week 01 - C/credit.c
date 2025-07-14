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
    long d1 = get_digit(1, creditcard);
    long d2 = get_digit(2, creditcard);
    long d3 = get_digit(3, creditcard);
    long d4 = get_digit(4, creditcard);
    long d5 = get_digit(5, creditcard);
    long d6 = get_digit(6, creditcard);
    long d7 = get_digit(7, creditcard);
    long d8 = get_digit(8, creditcard);
    long d9 = get_digit(9, creditcard);
    long d10 = get_digit(10, creditcard);
    long d11 = get_digit(11, creditcard);
    long d12 = get_digit(12, creditcard);
    long d13 = get_digit(13, creditcard);
    long d14 = get_digit(14, creditcard);
    long d15 = get_digit(15, creditcard);
    long d16 = get_digit(16, creditcard);

    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then
    // add those products’ digits together.
    long sumevens = pd(d2 * 2) + pd(d4 * 2) + pd(d6 * 2) + pd(d8 * 2) + pd(d10 * 2) + pd(d12 * 2) +
                    pd(d14 * 2) + pd(d16 * 2);

    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    long sumodds = d1 + d3 + d5 + d7 + d9 + d11 + d13 + d15;
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
