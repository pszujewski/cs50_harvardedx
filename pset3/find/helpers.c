/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

void bubble_sort(int values[], int n);
void sub_array(int target[], int src[], int idx_start, int idx_stop);
void print_array(int src[], int len);

/**
 * Returns true if value is in array of n values, else false.
 */
// Searching algorithm
bool search(int value, int values[], int n)
{
    if (n < 0)
    {
        // handles negative numbers
        // this algorithm only deals with
        // positive integers.
        return false;
    }

    bool is_even = n % 2 == 0;

    // Where is the middle of the array?
    int mid_idx;
    if (is_even)
    {
        // this isn't exactly the middle of
        // the array but it's close.
        mid_idx = n / 2;
    }
    else
    {
        if (n < 2)
        {
            // there is only one item
            // left in the values array
            // at index position '0'
            mid_idx = 0;
        }
        else
        {
            // Total number of items in the array
            // is odd, so there is an 'exact' middle
            mid_idx = (n + 1) / 2;
        }
    }

    // Do we have the target?
    // Look at the val in middle
    // of the array
    int curr = values[mid_idx];
    if (curr == value)
    {
        // found needle in haystack
        return true;
    }

    // Do we go left?
    if (mid_idx > 0 && curr > value)
    {
        // Declare a new array and establish size as
        // up to the mid_idx
        int left[mid_idx];
        sub_array(left, values, 0, mid_idx);
        // search on left side of the array
        // using recursion
        return search(value, left, mid_idx);
    }

    // Do we go right?
    if ((mid_idx + 1) < n && curr < value)
    {
        int size = n - (mid_idx + 1);
        int right[size];

        sub_array(right, values, mid_idx + 1, n);
        // search on right side
        return search(value, right, size);
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Bubble sort implementation in
    // O(n^2) running-time.
    bubble_sort(values, n);
    // Prints out all the values in order.
    for (int j = 0; j < n; j++)
    {
        printf("%i\n", values[j]);
    }
    return;
}

void bubble_sort(int values[], int n)
{
    bool swaps = true;
    while (swaps)
    {
        // if no swaps occur this stays false and
        // will break us out of the while loop.
        swaps = false;
        for (int i = 0; i < n - 1; i++)
        {
            int actual = values[i];
            // look to see if the next value in array is less
            // than 'actual', if so switch them.
            if (actual > values[i + 1])
            {
                //swap their positions in the array
                values[i] = values[i + 1];
                values[i + 1] = actual;
                // We'll need to continue our while loop
                // since a swap occurred, so flip the switch
                swaps = true;
            }
        }
    }
}

void sub_array(int target[], int src[], int idx_start, int idx_stop)
{
    // generates a sub array from a given source array.
    // Sub array can be generated from any starting and
    // and ending indexes of the source array.

    // we build out a totally new array, so the
    // initial idx position of the sub array is '0'
    int sub_idx = 0;
    for (int i = idx_start; i < idx_stop; i++)
    {
        target[sub_idx] = src[i];
        sub_idx++;
    }
}

void print_array(int src[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", src[i]);
    }
    printf("\n");
}



