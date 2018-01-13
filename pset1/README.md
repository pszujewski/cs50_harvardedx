### Lecture 1

**Introduction**
The basis of Computer science is input and outputs and problem solving. Between the inputs and outputs are the algorithms.

A note on The Binary system
A single number in binary is a bit. 8 bits makes a byte.
Transistors are millions of switches that turn on and off that represent lots and lots of zeros and ones.

A note on ASCII
The world decided that certain decimal numbers (reflected in binary) would express letters -> IE H is 72
Mapping binary numbers to letters is ASCII

A note on the concept of 'threading'
Multi-threading literally allows you to do multiple things at the same time. Programs can be multi-threaded. A thread is one thing a computer can do.

**C Programming**
C programs generally have a 'main' function that executes the program.
To execute a C program we first need to translate our code into machine code, which is just zeros and ones. In certain contexts these binary patterns might refer to numbers, strings, or even colors.
The CPU is the 'brains inside the computer.' It stands for Central Processing Unit. Intel makes a lot of CPUs for computers. The 'CPU spec' maybe stipulates that certain patterns of bytes mean certain things. Certain patterns of zeros and ones mean 'add these two numbers', 'print this', or 'this is a string.'
We can use software written on this spec called compilers (compilers are themselves software programs) to convert compiled languages (the higher-level language), or your source code to machine code. The source code is the 'input' to the compiler program. The machine code and the 'executable' make up the 'output.' A compiler really just is a series of algorithms that converts the source code to machine code.
CS50.io for the CS50 IDE, which runs on a linux virtual machine. In the IDE you have access to the terminal for executing CLIs.
Clang is a C compiler that is pre-installed in CS50 IDE.
In the terminal you create a C executable with clang by running

```bash
# where hello.c is the name of your c source code file.
$ clang hello.c
```

This creates a file a.out, since you haven't given it a name. Meaning assembly output.
An executable is a 'runnable' program (file). 

A Note on RAM (memory)
RAM is where programs live while they are running. RAM is faster than your hard disk. This is where files/ programs run. You only have a finite amount of RAM. A finite number of transistors.

A Note on Compiling
Compiling is an umbrella term for several steps, including:
pre-processing, compiling, assembling, linking.
These 4 things are done when compiling a program.
pre-processing: When the target C file to compile has the '#' it is a pre-processing directive that says: 'Hey computer, read this before you compile my own code because I use it.'
Compiling goes from source code to assembly code. Assembly code is just more arcane but still human readable. Assembling takes the assembly code and translates to Binary.
Linking links included libraries and your source code.

**C Data Types (Built into the language)**

int
integers always take up 4 bytes of memory or 32 bits (8*4)
The range of values they can store is limited to 32 bits.
int includes negative numbers. Half the values you can fit in a int are negative and half are positive.
You can have an unsigned int, which basically doubles the number of integers you can take on at the expense of no longer allowing negative values. So if you know you will have a value greater than 2 billion and less than 4 billion, but never negative, unsigned ints are useful. Unsigned is a qualifier. It is not a separate data types.

char
allows to take up 1 byte of memory, so 8 bits. Thanks to ascii we map numbers between 0 to 127 to characters. So 'A' has a different ascii value than 'a'

float
used for storing real-numbers, which are numbers that have a decimal point. They always take up 32 bits of memory, so 4 bytes. With a limited number of bits we are limited as to how precise we can be when defining floats (especially considering that some of that memory will be allocated to the integer part of the float). Describing the range of a float is not clear. Pi for example has an integer part which is 3, while the decimal part is technically endless. Floats have a precision problem because we only have 32 bits to work with.

double
are like floats are used to store floating point real-numbers. They can store 8 bytes of data (64 bits). So a double is just a float but with an extra 32 bits to work with your real numbers.

void
this is a type. It is not a data type. It is used for functions that don't have a return value. 'A void function' doesn't return any thing.

Data types Provided by CS50
bool - true and false.

string - ust an array of chars.