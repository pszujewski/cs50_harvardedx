### Lecture 5

Common Data Structures

**RAM**
Random access memory where we can store bunches and bunches of bytes. Each byte in a computer's memory has an address. When an infinite loop occurs, stack frames are constantly being placed on top of each other until program memory dries up and hits the heap.

**Problem with Arrays**
You have to decide in advance how large the array is. You can't just grow it. To grow it, you would have to allocate new contiguous blocks of memory and then copy over your array before then growing it as you need.

**Linked Lists**
Lists threaded together with pointers.

What if you could dynamically allocate new space to your list. You could define a struct called a node that contains a data item and a pointer to the next node. With a linked list, you might want to delete, search, or insert. The use of Linked List is primarily for when you don't know in advance how much memory you need.

```c
typedef struct node
{
     int n;
     struct node *next; // a pointer to the next node. Declares the 'variable' as a pointer - no deref
}
node;
```

The start of the list has to be a bit different, since it needs to simply point to the start of the list. The last pointer needs to point to null.
When discussing the Big-O run time of algorithms, recall that we are exclusively concerned with the upper bound.
The upper bound of searching a linked list is done in linear (n) time.
The upper bound of inserting (assuming we don't need to sort) is constant O(1), since we can insert it at the beginning. Keeping it sorted, incurs a linear time cost.
Delete is O(n) because it could be any where and you don't have random access in a linked list.

**Stack**
Main methods are push and pop. The last in is the first out (lifo). You can only grab or access off the top. This is good for letting you keep track of what you did most recently.
Queue
These are abstract data types that can be implemented in multiple ways.
Binary Search Tree
For every node in a tree, its left child is less than it and its right child is greater than it.

**Hash Table**
You can think of a table as an array that includes a linked list. Its a way of sorting things with close to O(1) time complexity. So in a hash table you might an array of pointers to the first nodes of different linked list. Now that we have malloc, linked lists are possible. And you also just need some sort of algorithm to decide how large you original array might be.
In worst case, a hash table devolves into O(n).

**Tries**
Tries are pointers to arrays that point to individual characters (if storing characters). Searching, sorting, and inserting can be done in constant time. But mapping out the actual abstract data structure can be complex.

**MakeFiles**
Recall that make automates the compilation of your code so that you don't have to execute Clang automatically with a whole bunch of switches. However, as your programs grow in size and you seek to break up your code into separate files, make won't be able to infer how to compile your code across the different source files, so you'll need to use a MakeFile and update its configuration.

