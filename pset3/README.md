### Lecture 3

Big O Notation, Strings in C, Arrays, Algorithms (searching and sorting)

**Strings in C**
Strings are saved in memory (in RAM) as a an array of characters. The specific implementation of a string denotes that the final 'box' or 'byte of memory' inside computer that denotes the end of a string in memory is '\0' character. The \0 is is just 8 zero bits. Recall that 8 bits makes 1 byte. That is the end of the string.

**Arrays**
Arrays are a generic data structure.
Binary search is a divide and conquer algorithm. If you know the set is sorted least to most, you start in middle in searching for the target value.
Linear search is different. You start at beginning and if you find the element, you return true.
pseudo code for binary search

```
look at middle of array
if element you are looking for
     return true
else if element is greater than target
     recurse -> search the left of element
else if element is less than target
     recurse -> search the right of element
else
     return true
```

Selection sort is when you iteratively select the smallest one at a time on each pass.

```
for i from 0 to n-1
     find smallest element from beginning to end of list
     swap smallest with i'th element
```

Bubble sort - You look at 2 at a time iteratively until you make no more changes. The greatest
'bubbles' to the end.

```
repeat until no swaps
     for i from 0 to n-2
     if i'th and i+1'th element are out of order
          swap them
```
Insertion sort

```
for i from 0 to n-1
     call 0'th through i-1th elements the 'sorted side'
   remove the i'th element
   insert it into the sorted side order
```

**Big-O Notation**
Measuring algorithm run-time: What's most important is consistency in the unit of measurement you use and not necessarily the unit itself. We measure the order of growth.
Big-O is the upper bound of the run-time. In other words, its the worst case. Capital omega notation is measuring the lower-bound of the run-time (so the opposite). A computer can only look at one item at a time.

The running-time (run-time) of bubble sort is on the order of n^2, so it is O(n^2). Mathematically speaking this is not a formal proof. In fact if you actually mathematically express the run-time of bubble sort, it is really (n - 1) + (n - 2) + (n - 3) ... which is (n - 2)^2 - n/2. But We are most concerned with the 'essence of this formula' because the n^2 has a dominant effect. So we say the run-time is O(n^2). Big O is a formal computer science notation for measuring algorithm run-time.
For bubble sort, the Big O at worst is O(n^2). Comparison based algorithms tend to be O(n^2). The Capital-Omega notation is O(n) at best if it's already sorted.

When Big O and Omega are the same you can express the order of growth in Theta notation.

**Merge Sort**
A key is the pointer that follows along the two halves. Technically merge sort needs more RAM.
Any time we see division and conquering, the run-time is typically logarithmic running time.
With the pointer, we always do n steps. So the run-time order of growth is O(n log n).