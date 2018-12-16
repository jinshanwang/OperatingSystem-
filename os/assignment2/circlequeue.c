// a1710974 Jinshan Wang
// a1701108 Jiarong Fan
#include "page.h"
#include <stdio.h>
#include <stdlib.h>


page* initialize(int size)
{
  page* head= (page*)malloc(sizeof(page));
  head->next=NULL;
  page* current= (page*)malloc(sizeof(page));
  page* lastNode= (page*)malloc(sizeof(page));
  current=head;
  head->mbit=0;
  head->usebit=0;
  head->pageNum=-1;
  head->arrival_time=-1;
  head->usebitqueue=InitBit();
  for(int i=0; i<size; i++)
  {
    page* newNode= (page*)malloc(sizeof(page));
    newNode->mbit=0;
    newNode->usebit=0;
    newNode->pageNum=-1;
    newNode->arrival_time=-1;
    newNode->usebitqueue=InitBit();
    current->next=newNode;
    lastNode=current;
    current=current->next;
  }
  lastNode->next=head;
  return head;
}
long long getPageNum(char*address, int pagesize)
{
  long long pageNum=strtol(address,NULL,16)/pagesize;
  return pageNum;
}

page* find(page* head,long pageNum,int NUMPAGES){
  int i;
  page* current = head;
  for (i = 0; i < NUMPAGES; i++) {
    if (current->pageNum==pageNum) {
      return current; // true
    }
    current=current->next;
  }
  return NULL; //false
}
page*  ESC_loopA(page* pointer, int NUMPAGES)
{
  int i;
  page* current = pointer;
  for (i = 0; i < NUMPAGES; i++) {
    if (current->usebit==0 && current->mbit==0) {
      return current; // true
    }
    current=current->next;
  }
  // return NULL; //false
  return ESC_loopB(current,NUMPAGES);
}
page*  ESC_loopB(page* pointer, int NUMPAGES)
{
  int i;
  page* current = pointer;
  for (i = 0; i < NUMPAGES; i++) {
    if (current->usebit==0 && current->mbit==1) {
      return current; // true
    }
    else{
      current->usebit=0;
    }
    current=current->next;
  }
  return ESC_loopA(current,NUMPAGES); //false
}
page*  find_buffer(page* VicPointer, int NUMPAGES){
  return ESC_loopA(VicPointer,NUMPAGES);
}

page* ARB_buffer(page* head, int NUMPAGES)
{

  page *min=head;
  min->Deximal_usebit=calculation(min->usebitqueue);


  page *current=head;
  current=current->next;

  for(int i=0; i<NUMPAGES-1; i++)
  {

    current->Deximal_usebit=calculation(current->usebitqueue);
    if (current->usebit==1 && current->Deximal_usebit==0) {
      current=current->next;
      continue;
    }
    else if(current->Deximal_usebit < min->Deximal_usebit)
    {
      min=current;
    }
    else if(current->Deximal_usebit == min->Deximal_usebit)
    {
      if(current->arrival_time < min->arrival_time)
      {
        min=current;
      }
    }
    current=current->next;
  }

  return min;
}

void Push_Usebit(page* head, int NUMPAGES)
{
  page* current=head;
  for(int i=0; i<NUMPAGES; i++)
  {
    current->usebitqueue=push_back(current->usebitqueue,current->usebit);
    current->usebit=0;
    current=current->next;
  }
}

void traverse(page* head, int NUMPAGES){
  page* current=head;
  int i;
  printf("%s\n","PAGE NUMBER     usebit         mbit             arrival_time              usebitqueue      Deximal_usebit" );
  for ( i = 0; i < NUMPAGES; i++) {
    printf("%lld\t\t",current->pageNum );
    printf("%d\t\t",current->usebit );
    printf("%d\t\t",current->mbit );
    printf("%ld\t\t",current->arrival_time );
    printqueue(current->usebitqueue);
    current->Deximal_usebit=calculation(current->usebitqueue);
    printf("%ld",current->Deximal_usebit );
    printf("\n");
    // print the Deximal_usebit and usebitqueue
    current=current->next;
  }
}
int EARB_helper(page* head,int NUMPAGES){
  page* current=head;
  int clean_page_counter=0;
  int modified_page_counter=0;
  int i;
  for (i = 0; i < NUMPAGES; i++) {
    if (current->mbit==0) {
      clean_page_counter++;
    }
    else{
      modified_page_counter++;
    }
    current=current->next;
  }
  // if the clean_page_counter is 0 which means that there is no dirty page or
  // if the modified_page_counter is 0 which means that there is no clean_page
  if (clean_page_counter==0 || modified_page_counter==0) {
    return 1;
  }
  return 0;
}
page* EARB_buffer(page* head,int NUMPAGES){
  page *min=head;
  page *current=head;
  current=current->next;
  // printf("%s\n", "current=current->next;");
  for(int i=0; i<NUMPAGES-1; i++)
  {
    if(min->mbit==0 && current->mbit==1) {
      bit* min_bitQueue=BitQueueCopy(min->usebitqueue); //clean page
      int min_weighted_value=calculation(min_bitQueue); //get the weighted value of the clean page
      current->Deximal_usebit=calculation(current->usebitqueue);
      if (min_weighted_value>current->Deximal_usebit) {
        min=current;
      }
      freeBitQueue(min_bitQueue);

    }
    else if(min->mbit==1 && current->mbit==0){
      bit* current_bitQueue=BitQueueCopy(current->usebitqueue); //clean page
      int current_weighted_value=calculation(current_bitQueue); //get the weighted value of the clean page
      min->Deximal_usebit=calculation(min->usebitqueue);
      if (current_weighted_value<=min->Deximal_usebit) {
        min=current;
      }
      freeBitQueue(current_bitQueue);
    }else{
      min->Deximal_usebit=calculation(min->usebitqueue);
      current->Deximal_usebit=calculation(current->usebitqueue);
      if(current->Deximal_usebit < min->Deximal_usebit)
      {
        min=current;
      }
      else if(current->Deximal_usebit == min->Deximal_usebit)
      {
        if(current->arrival_time < min->arrival_time)
        {
          min=current;
        }
      }
  }
    current=current->next;
  }

  return min;

}
