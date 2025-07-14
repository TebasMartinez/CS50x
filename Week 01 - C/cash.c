#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickles(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give customer
    int quarters = calculate_quarters(cents);

    // Subtract the value of those quarters from cents
    cents = cents - (quarters * 25);

    // Calculate how many dimes you should give customer
    int dimes = calculate_dimes(cents);

    // Subtract the value of those dimes from remaining cents
    cents = cents - (dimes * 10);

    // Calculate how many nickels you should give customer
    int nickles = calculate_nickles(cents);

    // Subtract the value of those nickels from remaining cents
    cents = cents - (nickles * 5);

    // Calculate how many pennies you should give customer
    int pennies = calculate_pennies(cents);

    // Subtract the value of those pennies from remaining cents
    cents = cents - pennies;

    // Sum the number of quarters, dimes, nickels, and pennies used
    int sum = quarters + dimes + nickles + pennies;

    // Print that sum
    printf("%i\n", sum);
}

int calculate_quarters(int cents)
{
    // Calculate how many quarters you should give customer

    int quarters;
    for (quarters = 0; cents >= 25; quarters++)
    {
        cents = cents - 25;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    // Calculate how many dimes you should give customer

    int dimes;
    for (dimes = 0; cents >= 10 && cents < 25; dimes++)
    {
        cents = cents - 10;
    }
    return dimes;
}

int calculate_nickles(int cents)
{
    // Calculate how many nickles you should give customer

    int nickles;
    for (nickles = 0; cents >= 5 && cents < 10; nickles++)
    {
        cents = cents - 5;
    }
    return nickles;
}

int calculate_pennies(int cents)
{
    // Calculate how many pennies you should give customer

    int pennies;
    for (pennies = 0; cents >= 1 && cents < 5; pennies++)
    {
        cents = cents - 1;
    }
    return pennies;
}
