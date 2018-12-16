// a1710974 Jinshan Wang
// a1701108 Jiarong Fan
#ifndef page_h
#define page_h
#include <stdio.h>
#include "ARBqueue.h"

typedef struct page
{
  char* operationType;
  char* address;
  long long pageNum;
  int mbit;              //modify bit
  int usebit;
  long arrival_time;
  bit* usebitqueue;
  long Deximal_usebit;
  struct page* next;
  struct page* previous;
}page;
//method
void SC(FILE *fp,int PAGESIZE,int NUMPAGES);
void ESC(FILE *fp,int PAGESIZE,int NUMPAGES);
void ARB(FILE *fp,int PAGESIZE,int NUMPAGES,int INTERVAL);
void EARB(FILE *fp,int PAGESIZE,int NUMPAGES,int INTERVAL);
int  EARB_helper(page* head,int NUMPAGES);
page* EARB_buffer(page* head,int NUMPAGES);
page*  ESC_loopA(page* pointer, int NUMPAGES);
page*  ESC_loopB(page* pointer, int NUMPAGES);
page* initialize(int size);
long long getPageNum(char*address, int pagesize);
page*  find(page* head,long pageNum,int NUMPAGES);
page*  find_buffer(page* VicPointer, int NUMPAGES);
page* ARB_buffer(page* head, int NUMPAGES);
void  Push_Usebit(page* head, int NUMPAGES);
void traverse(page* head, int NUMPAGES);
void freeBitQueue(bit* min_bitQueue);
int isfull(page* head, int NUMPAGES);
#endif
