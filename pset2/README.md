### Lecture 1

**Introduction**

Last week we looked at integer overflow, which is the reality that if you only have a finite amount of memory (or specifically a finite number of bits), you can only count so high.
We also saw floating point imprecision, which is the reality that with only a finite number of bits allocated for a float (whether 32 or 64), you can only hold so many numbers past a decimal point. When trying to express 1/3 for example in binary, things get tricky and imprecision piles up. Acomupter cannot represent an infinite number of numbers given finite space.

Cryptography
The input is plaintext and the output is ciphertext. The algorithm typically includes a 'key' by which the plaintext is scrambled.
You should be able to pass the ciphertext into another program that spits out the plain text using the key.

Typecasting
A string is a sequence of characters in your RAM (memory). It is stored in an array.
characters are just an abstraction on top of numbers and number are chars just depends on context.
Think of ASCII.
Typecasting is converting between data types.

**Arrays and memory**

How does the computer keep track of which byte of memory holds a char in a string? Underneath the hood, what C does when storing strings that the human types in is it seperates them by '\0' which is a special character. Which corresponds to 8 0 bits in a row. IT IS 8 ZERO BITS. Its is a line in a sand, that says everything to the left is one data type thing and to the right is another data type thing. \0 is also called null zero. This is because strings by design have a dynamic number of characters. You don't know how many characters in advance you will need for the string. So it uses this \0 as like the equivalent of the period. So floats, doubles, ints have a fixed number of bytes whereas this strinng implementation does not.
Array is a chunk of contiguous memory. You take computer's memory, or RAM, and you are carving it out. Back to back to back to back.

Abstraction is laying basic principles on top of each other. There is no magic underneath the hood.

When you run a program at the command line, you are filling in an 'argument vector.' Automatically, the OS is going to hand to your program a list of all the arguments handed to your program.
via argv, you have access to all the inputs to a program. It is an array.
Array = list of similar values back to back to back. It is a chunk of contiguous memory, each of whos element are back to back to back.
Each char in a string takes up a byte. A string is just an array of chars (an actual data type).

The main function
It's return value is defined as an int. Why? Main returns 0 if all went well, but somewhat intuitively because we always think of zero as being equivalent to false. For main, 0 means all is well. Whereas any other int it might return (any non-zero value) can correspond to an ERROR CODE.
In addition to void as its argument, main can also take

```C
int main(int argc, string argv[])
{
     // program goes here
}
```
Where the two arguments correspond to 'argument count' and an array of strings (which by default is a 2-d array because of the nature of strings being an array of chars) called argv, which holds all the arguments passed to the program.

Real numbers are floats. They are numbers with decimal values and are represented in C as floats.
Doubles are floats but they offer a more 'PRECISE' way to represent real numbers (floating point numbers).

Variable Scope
Scope is a characteristic of a variable that defines from which functions a variable can be accessed. There are two primary scopes in C: local scope and global scope. Locally scoped variables can only be accessed within the functions in which they're created. Global variables can be accessed any where. All functions can access it.

When a function receives a variable as input, it receives copies of those variables. Not the variables themselves.

```C
#define PI 3.14
#define COURSE "CS50"
```
Note that there is no semi-colon. When compiled, the compiler will replace all instances of your constant in the program with the 'replacement value.' This is analogous to find/replace declaration. When the program is compiled, the first thing that will happen is the find/replace defined by this define statement. The all capitals are a convention. The constant shouldn't be confused with a variable.

