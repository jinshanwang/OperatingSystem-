#ifndef ARBqueue_H
#define ARBqueue_H
#include <stdio.h>
#include <math.h>
typedef struct bit
{
  int ubit;              //usebit
  struct bit* bit_next;
  struct bit* bit_previous;
}bit;
bit* InitBit();
bit* push_back(bit* HEAD,int usebit);
bit* delete_last_bit(bit* HEAD);
int getLength(bit* HEAD);
int calculation(bit* HEAD);
bit* reset(bit* HEAD);
void printqueue(bit* HEAD);
int power(int base,int exponent);
bit* modifyBitQueue(bit* HEAD,int usebit);
bit* BitQueueCopy(bit* HEAD);
#endif
