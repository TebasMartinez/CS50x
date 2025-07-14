# Week 3 - Algorithms

[Link to Problem Set 3](https://cs50.harvard.edu/x/2025/psets/3/)

## Index
- Algorithms
- Running time
- [Linear search](https://cs50.harvard.edu/x/2025/shorts/linear_search/)
- [Binary search](https://cs50.harvard.edu/x/2025/shorts/binary_search/)
- Asymptotic notation
- [Recursion](https://cs50.harvard.edu/x/2025/shorts/recursion/)
- Data structures
- Sorting
  - [Selection sort](https://cs50.harvard.edu/x/2025/shorts/selection_sort/)
  - [Bubble sort](https://cs50.harvard.edu/x/2025/shorts/bubble_sort/)
  - [Merge sort](https://cs50.harvard.edu/x/2025/shorts/merge_sort/)
- [Call Stacks](https://cs50.harvard.edu/x/2025/shorts/call_stacks/)

## Notes from lecture
Algorithms are step by step instructions to solve a problem.

### Asymptotic notation
**Running time** of algorithms are represented in Computer Science with a capital letter O and a descriptive formula between parenthesis. E.g. O(n), O(log n) \
Very common running times are: \
O(n²) \
O(n log n) \
O(n) - linear search \
O(log n) - binary search \
O(1) \
The Ω (capital Omega) represents the **lower bound**, how many steps it will take with that algorithm to solve a problem _in the best case_. Represented as Ω(n²), Ω(n log n), Ω(n), etc. \
Ω(1) is the case for both linear and binary search, because we could simply get lucky and solve the problem in the first try. \
The Θ (capital theta) is used when big O and Ω are exactly the same. Θ(n²), Θ(n log n)... It doesn't apply for linear or binary search.

### Data structures
New syntax: you can create your own type that is a structure:
````
typedef struct
{
   string name;
   string number;
}
person;
````

#### Sorting
##### Selection sort
**O(n²), Ω(n²)**
````
For i from 0 to n-1
   Find smallest number between number[i] and number [n-1]
   Swap smallest number with numbers[i]
````

##### Bubble sort
**O(n²), Ω(n²)**
````
Repeat n times 
   For i from 0 to n-2 
      If number[i] and number[i+1] out of order 
         Swap them
````

**O(n²), Ω(n)**
````
Repeat n times
   For i from 0 to n-2
      If number[i] and number[i+1] out of order
         Swap them
      If no swaps
         Then quit
````
##### Merge sort
**O(n log n), Ω(n log n)**
````
If only one number
   Quit
Else
   Sort left half of numbers
   Sort right half of numbers
   Merge sorted halves
````
### Recursion
Technique that helps us solve the problem a little better, minimizing the number of comparisons we're doing. \
An algorithm (or, in maths, a function) is *recursive* if it calls itself.

[Example](https://github.com/code50/203688711/blob/588c32aacda99a807a06980bb3bb9e443b48d112/week3lecture/recursion.c) of recursion in C:
````
#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    int height = get_int("Height: ");
    draw(height);
}

void draw(int n)
{
    if (n <= 0)
    {
        return;
    }

    draw(n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}
````

## Notes from [Call Stacks](https://cs50.harvard.edu/x/2025/shorts/call_stacks/)
- When you call a function, the system sets aside space in memory for that function to do its necessary work.
   - We frequently call such chunks of memory **stack frames** or **function frames**.
- More than one function's stack frame may exist in memory at a given times. If main() calls move(), which then calls direction(), all three functions have open frames.
- These frames are arranged in a **stack**. The frame for the most recently called function is always on the top of the stack.
- When a new function is called, a new frame is **pushed** onto the top of the stack and becomes the active frame.
- When a function finishes its works, its frame is **popped** off of the stack, and the frame immediately below it becomes the new, active, function on the top of the stack. This function picks up immediately where it left off.

## Notes from [Recursion](https://cs50.harvard.edu/x/2025/shorts/recursion/)
Every recursive function has two cases that could apply, given any input:
- The _base case_, which when triggered will terminate the recursive process.
- The _recursive case_, which is where the recursion will actually occur.

In the mathematical factorial function (n!), n! equals all positive integers less than or equal to n, multiplied together.

In programming, we'll define the mathematical function n! as fact(n).
```
fact(1) = 1
fact(2) = 2 * 1
fact(3) = 3 * 2 * 1
fact(4) = 4 * 3 * 2 * 1
fact(5) = 5 * 4 * 3 * 2 * 1
```
or, what is the same:
````
fact(1) = 1
fact(2) = 2 * fact(1)
fact(3) = 3 * fact(2)
fact(4) = 4 * fact(3)
fact(5) = 5 * fact(4)
````
therefore:
````
fact(n) = n * fact(n-1)
````

Recursion for the factorial function in C:
````
int fact(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * fact(n-1);
    }
}
````
Since we have only one branch inside the conditionals, we're able to remove the curly braces for style:
````
int fact(int n)
{
    if (n == 1)
        return 1;
    else
        return n * fact(n-1);
}
````
