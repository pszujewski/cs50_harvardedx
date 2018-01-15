### Lecture 5

Introduction to Python and key Python Features

Python is an interpreted language. You don't have to compile them and then run the resulting machine code.

Instead, you run the python interpreter, which runs your program. Underneath the hood, it is compiling it (and doing other stuff). You are running a program called python (which is the interpreter) that compiles your python source code into byte code and then proceeds to interpret your byte code line by line.

```bash
$ python hello.py
```

Python 3 is differentiated from 2 because the python community introduced enough breaking changes to warrant the differentiation.

We still get imprecision when working with floating point values. This is because only a finite number of bits are used to represent a floating point value.

```python
f = cs50.get_float()
c = 5 / 9 * (f - 32)

print("{:.1f}".format(c))
```

**The sys global module**

Similar to the Process object in NodeJS, sys contains data on the currently running process.
The following code gets reads the number of command line arguments provided and prints one.

```python
import sys

if len(sys.argv) == 2:
     print("Hello, {}".format(sys.argv[1]))
else:
     print("Hello, world")
```

The notion of the 'argument vector' exists in python as well as C

```python
import sys

for i in range(len(sys.argv)):
     print(argv[i])
```

To exit a python process, you can do the following, where exit(0) indicates success by convention, and any other number will indicate an error code. You don't return 'exit.'

```python
import sys

if len(sys.argv) != 2:
     print("Missing command-line arguments")
     exit(1)

print("Hello, {}".format(sys.argv[1]))
     exit(0)
```

Similar to JS, strings in python are immutable, so their values cannot be changed. Immutability is a feature of the string class in python. This is different from C, where strings were simply arrays of characters that began at one memory address and ended at another with '/0'. There is no notion of objects in C. Structs are different in that structs are designed to only hold data (think dorm, name, location...) whereas objects can include full fledged encapsulated functionality via methods, which are functions that are attached to a particular object. Thus a string in python is actually a class. It contains methods (such as .format() or .capitalize()) in addition to actually (underneath the hood) holding the characters that actually form the string. These methods allow you to operate on the string in very dynamic way. Immutability for strings in python also means that you can directly compare two strings.

```python
s = 'Peter'
t = 'Peter'

s == t # resolves to true
```

In C, this would not be the case because strings in C are nothing more than pointers to memory addresses that point to the beginning of a string and conventionally end with '/0'. Thus, if you were to try and compare to strings in C in the same manner as above, you would ultimately be trying to compare two hex values that corresponded to memory addresses (on either the stack or the heap, depending on how the program allocated the memory for the strings). This comparison would resolve to false because the memory addresses would not be the same. Thus, C provides the strcompare() function to compare two strings, which most likely iterates over the characters of each string and compares them. It is important to stress that immutability in strings in python is a feature of the language. It is a choice that was made to allow for strings to be treated as you might use an integer or character in C.

**Python Class and basic file i/o**

```python
class Student:
     def __init__(self, dorm, name):
          self.dorm = dorm
          self.name = name // instance variables of the class
```

```python
class Dictionary

     def __init__(self):
               self.words = set()

         def load(self, dictionary):
                file = open(dictionary, "r")
          for line in file:
               self.words.adds(line.rstrip("\n"))
          file.close()
          return True

      def check(self, word):
          return word.lower() in self.words
```

You can implement a python web server that listens on TCP port 80 for HTTP requests using native python module http.server

Definition of a web server: A piece of software that when you run it just starts listening on the internet (on your computer's IP address, and on TCP post 80) for incoming HTTP requests, and then responds to them as the programmer sees fit.

Your python web server can write to the web socket connection between the client and itself.

Every computer has a localhost address. Every computer by default has a local IP address at 127.0.0.1, so if you listen on port 8080 of your localhost, you would access it in the browser at http://127.0.0.1:8080
In other words, you want your browser to take to your local computer at that local address on the port 8080.

# Python Lists, Tuples, and Dicts

```python
nums = [1, 2, 3, 4]
nums = [len(nums):] = [5, 6] # slicing syntax
```

A tuple is an ordered immutable set of data. They are great for associating collections of data. They are great for associating collections of data where those values are unlikely to change.

List of tuples

```python
presidents = [
     ("George Washington", 1789),
     ("John Adams", 1797),
     ("Thomas Jefferson", 1801),
     ("James Madison", 1809)
]

# iterate over list of tuples
for prez, year in presidents:
     print("In {1}, {0} took office".format(prez, year))
```

Python Dictionaries - key/value pairs

```python
pizzas = {
     "cheese": 9,
     "pepperoni": 10,
     "vegetable": 11,
     "Buffalo chicken": 12
}
```
You could iterate over this dictionary with a for loop, just like with a list

```python
for pie in pizzas:
     print(pie)
```
You could iterate over the values instead of the keys with the following

```python
for pie, price in pizzas.items(): # actually makes the dictionary items' values into a list
     print(price)
```

Python does not coerce ints to strings, must do the following

```python
print("A pizza costs $" + str(price))
```

Classes in python require an initialization function, also known as a constructor, which sets the starting values of the class' (the class is an object) properties. A class can be thought of as a 'type' of an object. It is a special and unique object, but an object nonetheless. In defining a method on an object, 'self' should always be the first parameter.

Python can generate new lists with the following syntax. It is basically like mapping over an array in JS. It's called list comprehension

```python
my_list = []
for i in range(10):
     my_list.append(i)

# is equivalent to:

my_list = [i for i in range(10)]
```  

