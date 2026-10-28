#include <iostream>
#include <stdlib.h>
using namespace std;

class freeList {
public:

  freeList(long int* arr, int size){
  head = arr; 
  head[0] = size - 2;
  head[1] = 0;
}
  long int* reserve_space( int size ){
    if (head[0] < size + 2) {
      return nullptr; // Not enough space
    }
    //Save Origginal free chunk info
    long int old_head_value = head[0];
    long int old_next_value = head[1];

    // Update the header of the allocated chunk
    long int* ptr = head + 2;

    //calculte where free remaing chunk begins
    long int* new_head = head + size + 2;

    //set up allocated chunk header
    head[0] = size;
    head[1] = 0;

    //setup remaing free chunk header
    new_head[0] = old_head_value - size - 2;
    new_head[1] = old_next_value;

    head = new_head; // Update head to point to the new free chunk
    return ptr;
  }
  
  void free_space( long int* pntr ){ 
    long int* chunk = pntr - 2;
    chunk[1] = (long int)head;
    head = chunk;
    }

 
  void coalesce_forward(){
    long int* chunk = head;
    while (chunk != nullptr && chunk[1] != 0) {
    long int* next_chunk = (long int*)chunk[1];

      if (chunk + chunk [0] + 2 == next_chunk) {
        chunk[0] += next_chunk[0] + 2;
        chunk[1] = next_chunk[1];
    } else {
      chunk = next_chunk;
    }
    }
    }  // the print function is given to you that outputs the contents of
  // the free list as currently represented in simulated memory.
  void print();

private:
  long int * head;    
};
