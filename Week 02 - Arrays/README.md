# Week 2 - Arrays

[Link to Problem Set 2](https://cs50.harvard.edu/x/2025/psets/2/)

## Index
- Compiling
- Compiling steps
- [Command line arguments](https://cs50.harvard.edu/x/2025/shorts/command_line_arguments/)
- Debugging ([1](https://cs50.harvard.edu/x/2025/shorts/debugging_step_through/), [2](https://cs50.harvard.edu/x/2025/shorts/debugging_step_into/))
- Data types in C
- [Functions](https://cs50.harvard.edu/x/2025/shorts/functions/)
- [Variables and scope](https://cs50.harvard.edu/x/2025/shorts/variables_and_scope/)
- [Arrays](https://cs50.harvard.edu/x/2025/shorts/arrays/)

## Notes from lecture
### Compiling
Compilers turn code into 0s and 01s, source code into machine code \
When we are using _make-_ in the terminal we're using a compiler \
A common compiler is **clang**, but it names programs 'a.out' by default \
So if we use
> clang hello.c

we get a program named 
> a.out 

#### Arguments
Arguments are inputs to a program. Clang supports additional arguments at command line, so we can name our programs. \
So if we use
> clang -o hello hello.c

we get 
> hello 

However, if we want to use additional third-party libraries like the one created by CS50, we need to preinstall it and add an additional argument  
> clang -o hello hello.c -lcs50

The _l_ from the argument _-lcs50_ stands for _link_.

#### Compiling steps
**Preprocesing** -> anything that starts with # \
**Compiling** -> code gets translated from one language (C in this case) to another language called assembly code (which varies between devices e.j. mac, pc, etc.) \
**Assembling** ->  assembly code gets converted to 0s and 1s \
**Linking** -> the previous three steps create as many files as libraries used +1 (the one we created), written with 0s and 01, in this step all these files are combined. 

#### Debugging
printf \
debug50 (debugger available in the real world, not exclusive to CS50)

#### Data types in C
bool - 1 byte (8 bits) \
int - 4 bytes (32 bits) \
long - 8 bytes (64 bits) \
float - 4 bytes \
double - 8 bytes \
char - 1 byte \
string - ? bytes (it depends how long the text/content is) \
...

### Arrays
First of the **data structures** we will learn. \
An array is a sequence of values (all of which are the same data type) back to back to back in memory.
> int scores[3];



