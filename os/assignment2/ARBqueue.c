#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ARBqueue.h"


// ARB 序列的初始化
bit* InitBit(){
  bit* HEAD;
  HEAD=(bit*)malloc(sizeof(bit));
  HEAD->bit_next    =NULL;
  HEAD->bit_previous=NULL;
  // 创建一个八位的控制块
  int i;
  for ( i = 0; i < 8; i++) {
      HEAD=push_back(HEAD,0);

  }
  return HEAD;
}


// usebit 的添加
bit* push_back(bit* HEAD, int usebit){
  bit* newbit;
  newbit = (bit*)malloc(sizeof(bit));
  newbit->ubit=usebit;
  // 1.record a new usebit
  // when the queue is empty
  if (HEAD->bit_next==NULL) {
    HEAD->bit_next=newbit;
    newbit->bit_next=NULL;
    newbit->bit_previous=HEAD;
  }
  // when the queue is not empty
  else{
    bit* first= HEAD->bit_next;
    HEAD->bit_next=newbit;
    newbit->bit_next=first;
    first->bit_previous=newbit;
    newbit->bit_previous=HEAD;
  }
  // 2.pop_back a old usebit
  // if the length is more than 8 bits
  int Length = getLength(HEAD);
  if (Length > 8) {
    HEAD=delete_last_bit(HEAD);
  }
  return HEAD;
}


// 队列的长度
int getLength(bit* HEAD){
  int counter=0;
  bit* current = HEAD->bit_next;
  while (current!=NULL) {
    counter++;
    current=current->bit_next;
  }
  return counter;
}


// 删除最后一个bit
bit* delete_last_bit(bit* HEAD){
  bit* current = HEAD->bit_next;
  while (current->bit_next!=NULL) {
    current=current->bit_next;
  }
  bit* previous_bit=current->bit_previous;
  previous_bit->bit_next=NULL;
  free(current);
  return HEAD;
}


// 计算队列的值
// 把二进制转化为十进制
int calculation(bit* HEAD){
  bit* current=HEAD->bit_next;
  int total    = 0;
  int exponent = 7;
  while (current != NULL) {
    total = total + (current->ubit*power(2,exponent));
    exponent--;
    current=current->bit_next;
  }
  return total;
}
bit* reset(bit* HEAD){
  int counter=0;
  bit* current=HEAD->bit_next;
  while (current!=NULL) {
    if (counter==0) {
      current->ubit=1;
    }else{
      current->ubit=0;
    }
    counter++;
    current=current->bit_next;
  }
  return HEAD;

}
void printqueue(bit* HEAD) {
  bit* current=HEAD->bit_next;
  while (current!=NULL) {
    printf("%d", current->ubit);
    current=current->bit_next;
  }
  printf("\t\t" );
}
int power(int base, int exponent){
  int sum=1;
  while (exponent!=0) {
    sum=sum*base;
    exponent--;
  }
  return sum;
}
bit* modifyBitQueue(bit* HEAD,int usebit){
  bit* modifyBitNode= HEAD->bit_next;
  modifyBitNode->ubit=usebit;
  return HEAD;
}
// getting a copy of the original Queue and push 3 INTERVALs back
bit* BitQueueCopy(bit* HEAD){

  bit* newQueue=InitBit();

  bit* newQueueCurrent=newQueue->bit_next;

  bit* current=HEAD->bit_next;

  while (current!=NULL) {
    newQueueCurrent->ubit=current->ubit;
    current=current->bit_next;
    newQueueCurrent=newQueueCurrent->bit_next;
  }
  int i;
  for ( i = 0; i < 3; i++) {
    newQueue=push_back(newQueue,0);
  }

  return newQueue;
}
void freeBitQueue(bit* HEAD) {
  bit* current=HEAD->bit_next;
  while (current!=NULL) {
    HEAD->bit_next=current->bit_next;
    free(current);
    current=HEAD->bit_next;
  }
  free(HEAD);
}
