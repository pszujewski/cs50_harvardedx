### Lecture 4

What does the memory that is allocated to a program look like? And what are its different sections? What does it mean to allocate memory to a program?

**Program Memory**
Whenever a program is run, the OS gives the program 'the illusion' of a really big chunck of memory, isolated only for that program's consumption. The OS lays out the program's memory in a fairly standard way. There are different sections of this layout. For example, one section is for environment variables, another is for the 'stack,' another is for the 'heap'... initialized data, text...
text is the segment of memory where your program's zeros and ones live. Those zeros and ones are loaded into your hard disk or your solid state disk of the computer.

**The Stack**
The stack is a frame or 'segment of memory. You can think of the stack as being made up of 'trays.' A chunk of the stack is allocated to functions, and the local variables contained in functions take up the space of that chunk. So for example, if 'main' is a function, it is allocated memory from the stack. If main calls a function called swap, then swap is allocated a different chunk of the stack above main ('above' -> by design). These chunks are known as 'stack frames.' When a function returns, the actual bits still hold those values, but the stack frame 'forgets' about the stack frame that corresponded to the function that finished executing.
When a function calls another function and passes it inputs, those inputs are copies.
The stack is where the memory is managed for each executing function. Function stacks are layered on top of each other in the stack, and are only 'un-layered' as the function return. The stack grows up and then down as functions return.

**What is in a stack frame?**
Recall that a frame in the stack is allocated for each function. The stack grows as functions pile up, and shrinks as functions return. Each frame, in addition to holding the memory associated with a function's local variables (arguments provided included), also holds other things as well, such as the 'return address' for a function (so where the return value should be stored in memory). When 'foo' is done executing it returns based on the return address.

If the stack grows without end or just grows too much (example of recursion that doesn't end due to no base case), to the point where it exceeds the heap and you run out of 'stack space,' you experience what's known as 'stack overflow.'

**The heap**
The heap is understood as being 'above' the stack and containing a 'pool of available memory' that you can draw from at any point.
If the heap grows down too far, you experience 'heap overflow'

Both heap overflow and stack overflow are known as buffer overflow

**How does get_string() work exactly?**
Recall that strings are arrays of characters. An array is a contiguous block of memory. At each index position of the array, you will find a character, and the end of the string is denoted with a \0.
get_string creates the array and returns a reference (the address) to the first index position of the string in memory. It does not actually return the whole string. The variable that receives the return value of get_string knows that it returns the 'memory address' of the first character. It reads the array starting at that memory address and until it hits the \0 in order to 'read' the string.
get_string therefore provides a sort of 'map' for the string.

**char * and the 'star' operator **
This denotes that it is not literally a char but a pointer to a star.

```
int* pk = ... -> this is a pointer-to-an-int variable. It holds a pointer exclusively
int *n = malloc(sizeof(int)); -> malloc returns a pointer. Here we dereference the pointer it returns RIGHT AWAY using the star operator, which gives us immediate access to the value(s) at that memory address. Note the difference between the first two.
```
**malloc()**
Returns a contiguous chunk of memory. It accepts an integer as an argument which identifies the number of bytes you need. It actually returns a 'pointer' to this chunk of memory.

**The star operator continued**
The star (*) operator denotes that a variable is actually a pointer, and does not hold a copy of another variable. Consider the following function

```c
void swap(int *a, int *b)
{
     int tmp = *a;
     *a = *b;
     *b = tmp;
}
```

```c
swap(&x, &y);
```

Here, a and b (thanks to the star operator) hold pointers to certain chunks or memory, and not real values.  The first line within the block of the function denotes, 'go to the address in a and get its value. Store it at as the address held by star b.' The star operator is admittedly confusing.
Secondly, the ampersand operator says, 'give me the address (pointer map) of x and y.' It is important to note that the address is literally an integer. The star just says (in this context), this integer is actually a pointer, which 'points' to an address in memory.

A string is equal to a char * because a string is after all just a pointer to where a series of characters live in memory.

We can iterate over a 'string' without using array syntax, which in C is actually just syntactic sugar. Using a for loop we can access each character in a string with:

```c
printf("%c\n", *(s + 1));
```

Where s is the char * containing the pointer address for the beginning of a string. Expressing how to print each character is a form of 'pointer arithmetic.' this is functionally equivalent to accessing each character based on array bracket notation. This is doing math with pointers.

**Memory Leak**
A memory leak occurs when a program asks for memory continuously without freeing it up or giving it back to the OS when it has finished needing that memory.
valgrind is a program that will read your C code and evaluate if you have any memory leaks, or any improper memory usage.

```bash
$ valgrind --leak-check=full ./memory
```

Those flags gives you more detail regarding the memory leak if there is one.

```c
int *x = malloc(10 * sizeof(int));
```

The code directly above gives you 10 times 4 bytes. Recall that an integer is 4 bytes large. Recall 8 bits make up 1 byte. Malloc here returns a memory address and *x serves as a pointer to a chunk of memory of 40 bytes. This equivalent to what an array is and each byte can be accessed with bracket notation.

As an aside, when a program is finished running, all the memory given to that program by your OS is automatically freed. But in a long-running program, memory leaks can definitely be an issue.

**What is in a stack frame?**
Recall that a frame in the stack is allocated for each function. The stack grows as functions pile up, and shrinks as functions return. Each frame, in addition to holding the memory associated with a function's local variables (arguments provided included), also holds other things as well, such as the 'return address' for a function (so where the return value should be stored in memory). When 'foo' is done executing it returns based on the return address.

The image above breaks down a 'frame' in the stack for a given function. Notice that the top is 'unallocated stack space.' This denotes where the next frame will live. Otherwise, you have a section for local variables, which here is holding an array of type char with 12 'indices.' (each index can hold a char). Below that section, we have a slice reserved for storing the arguments provided to the function, here there is one argument, char *bar (which is equivalent to a string). Below that is the return address, where the return value of the function is sent.

If you make a mistake (or a hacker hacks into your program) and you go beyond the bounds of the
c array (memory chunk), you will actually be touching memory that could overwrite other local variables, arguments, or return addresses in that stack frame.

**JPEG**

JPEG is a common format for images capable of storing millions of different color combinations and can be easily compressed as well. Images are made of pixels that map to a certain color (each pixel). BMP (Bitmap)

What is a file? What is the difference between a JPEG (file), Word document (file), Excel (File), etc?
They are all files that contain bytes (bits - 0 and 1). But the key differences that make them unique is there particular patterns. Usually the patterns of zeros and ones at the beginning of each file denotes the 'type' of file it is. For example JPEGs all start with the same pattern of 255 216 255. That demarcates the start of a JPEG. Each pixel in an image has 24 bits (RGB) that denote a specific color for that pixel (how much red, green, and blue) is given to that one pixel.

"Files are just a sequence of bits, and if we think of each byte as having some offset from the beginning, we can specify exactly what should be in a file for it to be valid."

**Structs in C**
Defining a 'student' struct in C with two fields.

```c
// You then can use this struct as basically a data type
typedef struct
{
      string name;
      string dorm;
}
student;
```

```c
// creates an array with space for 3 'student' data items
student students[3];

// you can access the 'name' field on the second student with =>
students[1].name;
```

**More on the Hexadecimal system**
This is a base-16 system ranging from 0 - 9, a, b, c, d, e, f
It always computer scientists to express something close to binary but the advantage of hexadecimal is that it is much more human understandable.
16 is a power of 2, and so each hexadecimal digit corresponds to a unique ordering arrangement of 4 bits.

So binary string 1111 corresponds to hexadecimal digit 'F'. To distinguish hexadecimal numbers from decimal numbers, we usually prefix hexadecimal number with '0x.' It's just a clue to humans that we are dealing with a hexadecimal number. Although often this prefix is unnecessary because the use of the letters makes it clear that we are dealing with hexadecimal numbers.

Recall that binary has place values: there is a 1s place, 2s place, 4s place, 8s place... In decimal the places are 1, 10, 100, 1000. In hexadecimal they are not powers of 2 or 10, but powers of 16.
0x397 has a 3 in the 16^2 place, 9 in the 16^1 place and 7 in the 16^0 place. So that's 3 * 256, 9 * 16, and 7 * 1, which comes out to 919 expressed in decimal.

It's easy to convert from binary to hexadecimal. If you have a long string of binary digits, you start by grouping them in groups of 4 (start from right) and then converting each group of 4 into a hexadecimal number.

**The binary number 1101**
Recall that, working from left to right, we have the places: 2^3, 2^2, 2^1, 2^0.
This number has a 1 in the 8s place, a 1 in the 4s place, a 0 in the 2s place and a 1 in the 1s place.
In decimal this is 13. in Hex it's D
Often memory addresses are expressed in hexadecimal.

**Pointers more in depth.**
Pointers concept is arguably difficult but it is important to cultivate pointer discipline. Pointers give us a different way to pass data between functions. When functions pass variable 'by value' they are passing essentially copies of the data.
If we use pointers instead, we have the power to pass the actual data itself. That means a change to that data in one function can impact that data in another function.

**Refresher on Memory**
On your computer's system, you have a 'hard disk drive' or a 'solid state drive,' which is where your computer's files are stored (remember, everything is a file and pattern of bits). Disk Drives are just storage space. We can't work directly there as programmers. Instead we can only work in RAM (random access memory). You have less RAM than space in your HDD or SSD. Indeed 'manipulation (the changing or 'moving around') and use of data from files can only take place in RAM, so we have to move data there.  Memory in turn, is basically a huge array of 8-bit wide bytes.

You can shut off and turn your computer back on and still have your files, because they are stored in your HDD or SSD. RAM is where your volatile data lives (all the data that can change). When you turn off your computer, all the data in RAM is destroyed, which is why you need an HDD or SSD. To provide a permanent location for data/ files. When we talk about ''memory,' we are talking about RAM. For example, if you start running a C program that creates an integer, 4 bytes of RAM are set aside (or filled...) for that integer since that's the size of an integer in C, and if you create a char, 1 byte is set aside.

Memory is a huge array of byte-sized cells. The most important thing to remember about pointers is that they are nothing more than an address to locations in memory where a given variable lives. A pointer is a data item whose value is a memory address. The type of the pointer describes the type of the data that lives at that memory address. You should always set the value of a pointer to something meaningful immediately, you should set it to NULL and not just try to leave it 'undefined.'

**The '&' ampersand operator**
Another way to make a pointer is to extract the address of a pointer using the '&', or address extractor operator.
If x is an integer of type int, then &x is a 'pointer-to-int' whose value is the address in memory of 'x.' Keep in mind that the '&' is operating on the existing x variable. It extracts the memory address of that variable. Another example: If arr is an array of doubles (recall that 'double' is a data-type of size 8 bytes), then &arr[i] is a pointer-to-double whose value is the memory address of the i-th value of arr.

**The dereferencing operator**
This makes things a little confusing because the * is used here as well. We define of pointer-to-variable using star as follows

```c
int k = 5;
int* pk = &k
// extract memory address of k using '&' operator and save the address in pk, which is of type  //'pointer-to-int'
```
This says pk gets the address of k (the address of k's bytes). pk holds a pointer to k. It tells us where k lives and allows us to work with the data at that location. We can use the dereferencing operator to actually access the data at a memory address. It goes to the pointer reference, accesses the data, and allows you to manipulate it at will.

**Pointers example**

```c
// create variable k
int k = 5;
// extract and save the memory address of k in pk
int* pk = &k;
// dereference pk (go to address pointed to by pk and change the value at that address to 35)
*pk = 35;
// create new variable 'm'
int m = 4;
// extract m's memory address and make pk point to it instead of the address of k
pk = &m;
```

**Dynamically Allocating Memory**
We can use pointers to get access to memory allocated at run-time. This memory is not allocated at compile-time. Dynamically allocated memory comes from a pool of memory known as the heap. Recall that the heap is a section of the overall memory allocated by the OS to a program, allowing the program to run. Memory used at compile-time comes from the stack, I believe. The stack broken up for each function, and contains each function's local variables. It is important to remember that dynamically allocated memory comes from the heap while statically allocated memory comes from the stack.

```c
// statically obtain an integer
int x;
// dynamically obtain an integer
int *px = malloc(sizeof(int));
// here we obtain the pointer from malloc and dereference the variable at once.
```

```c
// Array of floats on the stack
float stack_array[x];
// Array of floats on the heap
float* heap_array = malloc(x * sizeof(float));
```

Dynamically allocated memory is not automatically returned to the system, which causes a memory leak if you don't free it.

```c
char* word = malloc(50 * sizeof(char));

// do stuff with word and free the dynamically allocated memory

free(word);
```

Three golden rules of dynamically allocating memory with malloc
1) Every block of memory that you malloc must then be freed.
2) Only memory that you malloc should be freed.
3) Do not free a block of memory more than once.

```c
int* b = malloc(sizeof(int));
// the pointer-to-int variable b lives on the stack, but it points to memory that lives on the heap.
// b contains the address.
```

**Structures continued**
Provide a way to unify different native variable types into a new 'type' that we can assign a unique type name. Typically, the grouping of these types has a logical connection. Structures can be thought of as a super-variable.
We typically define a structure outside of functions, at the top of our program or in separate .h header files.
If you have a 'struct car' you can use it as a factory to define structs of type car.

You can dynamically allocate memory for structs. Note that you only use the arrow operator if your struct is saved by pointer and you need to dereference it (so, only if it was created with dynamically allocated memory).

```c
// get the reference to the memory from the heap
struct car *his_car = malloc(sizeof(struct car));

// access the fields
// this says 'dereference his_car and access the field year' That's the arrow operator.
his_car -> year = 2011;

// alias char* to string
typedef char* string

// define and alias struct car to car_t
struct car
{
     int year;
     char model[10];
     char plate[7];
};

typedef struct car car_t;

you can also
typedef struct car
{
     ...
};
car_t;
```

**Pixels**
Different image types can specify a different number of bits per pixel. In the Bitmap example we looked at, each pixel was represented by 3 bytes (24 bits). So past the BMP headers at the top of a BMP file, every 24-bit sequence represents a pixel's color. Files are just sequences of bits. The file's metadata (total width, height, etc) is contained in the headers.

File formats exist because the world has standardized what bytes mean what. Mapping different structs to a large sequence of bytes (file), allows us to make sense of the different parts of the file. It allows us to attach names (properties) to different sequences of bytes within the file. It allows us to think of the file instead as a sequence of structs.
