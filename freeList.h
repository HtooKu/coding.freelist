#include <iostream>
#include <stdlib.h>
using namespace std;

class freeList {
public:

  // Constructor: Taking a pointer to an array of long ints and its
  // size, it sets up the simulated memory with the appropriate header
  // information.
  freeList( long int*, int size );

  // reserve_space: Taking a size as the number of long int's (note
  // that because we are working with a 64-bit physical machine, each
  // addressable location does not contain bytes (8 bits), but long
  // ints (64 bits, or 8 bytes).

  // It returns the address of the allocation space, which is 2 long
  // ints AFTER the header because those two hold the meta data. 
  // Make sure to update the head pointer to not just the
  // size but two more to account for this overhead.
  
  // NOTE: if you add 4 to head, which is a pointer, the program will
  // automatically convert that 4 to 32 because it is
  // equizalent to 32 bytes (4x64 bits = 4x8bytes = 32)
  long int* reserve_space( int size );

  // free_space: Given a pointer value, it updates the table to add
  // the chunk referened by the input pointer to the front of free
  // list and update head to now refer to it. Whatever head refers to
  // should be updated to be the "next" field of this chunk.

  // Note that the input pointer is referring to the start of the data
  // of this chunk, so you need to go to two spots before it to access
  // the header.
  void free_space( long int* pntr );

  // Manipulate the RAM so that it coalesces chunks when are immediately 
  // following another. This function only looks forward and does NOT 
  // find chunks that precede the one under consideration, however.
  // Think of this function as being able to traverse down a linked list
  // but cannot go backwards.
  void coalesce_forward();

  // the print function is given to you that outputs the contents of
  // the free list as currently represented in simulated memory.
  void print();

private:
  long int * head;    
};

