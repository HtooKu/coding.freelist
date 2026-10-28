#include <iostream>
#include <stdlib.h>
#include "freeList.h"

using namespace std;

freeList::freeList(long int* inRAM, int size) {
    head = inRAM;
    head[0] = size - 2;
    head[1] = 0;
}

long int*
freeList::reserve_space(int size) {
    if (head == nullptr || head[0] < size + 2) {
        return nullptr;
    }

    long int old_size = head[0];
    long int old_next = head[1];

    long int* allocated = head + 2;
    long int* remaining = head + size + 2;

    head[0] = size;
    head[1] = 0;

    remaining[0] = old_size - size - 2;
    remaining[1] = old_next;

    head = remaining;

    return allocated;
}

void
freeList::free_space(long int* location) {
    if (location == nullptr) {
        return;
    }

    long int* chunk = location - 2;
    chunk[1] = (long int)head;
    head = chunk;
}

void
freeList::coalesce_forward() {
    long int* chunk = head;

    while (chunk != nullptr && chunk[1] != 0) {
        long int* next = (long int*)chunk[1];

        if (chunk + chunk[0] + 2 == next) {
            chunk[0] += next[0] + 2;
            chunk[1] = next[1];
        } else {
            chunk = next;
        }
    }
}
// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}