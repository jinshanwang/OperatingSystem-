// a1710974 Jinshan Wang
// a1701108 Jiarong Fan
#include "page.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>


void ESC(FILE*fp,int PAGESIZE,int NUMPAGES){
  long long trace=0;
  int read=0;
  int write=0;

  char* single_page;
  char** single_page_elements;
  page* cir_queue = initialize(NUMPAGES);
  page* VicPointer= cir_queue;
  while ((single_page=next_cmd(fp))!=NULL) {

        if (single_page[0]=='#') {
          continue;
        }
        single_page_elements=splitline(single_page);
        long long thisPageNum=getPageNum(single_page_elements[1],PAGESIZE);
        if (find(cir_queue,thisPageNum,NUMPAGES)==NULL) {
          // printf("%s %ld\n", "MISS: PAGE",thisPageNum);
          read++;
          // version 2
          VicPointer=find_buffer(VicPointer,NUMPAGES);

          if (VicPointer->pageNum==-1) {  //if the frame is empty
            VicPointer->usebit=1;
            VicPointer->pageNum=thisPageNum;
            VicPointer->operationType=single_page_elements[0];
            if (VicPointer->operationType[0]=='W') {
              VicPointer->mbit=1;
            }
          }
          else{
            //printf("%s %ld ", "REPLACE: PAGE",VicPointer->pageNum);
                              //replace ocurred
            if (VicPointer->mbit==1) {
              write++;
              //printf("%s", "(DIRTY)");
            }
            //printf("%s\n","" );
            VicPointer->usebit=1;
            VicPointer->pageNum=thisPageNum;
            VicPointer->operationType=single_page_elements[0];
            if (VicPointer->operationType[0]=='R') {
              VicPointer->mbit=0;
            }
            else if (VicPointer->operationType[0]=='W') {
              VicPointer->mbit=1;
            }
          }
          VicPointer=VicPointer->next;
        }
        // hit
        else{
          page* target = find(cir_queue,thisPageNum,NUMPAGES);
          target->operationType=single_page_elements[0];
          if (target->operationType[0]=='W') {
            target->mbit=1;
          }
          target->usebit=1;
          //printf("%s %ld\n", "HIT: PAGE",target->pageNum);
        }



        trace++;
        freelist(single_page_elements);
        // printf("操作类型: %s 逻辑地址: %s\n",single_page_elements[0],single_page_elements[1] );

  }
          // printf("%d %d %d \n", trace, read, write);
          printf("events in trace:    %lld\n", trace);
          printf("total disk reads:   %d\n", read);
          printf("total disk writes:  %d\n", write);
}
