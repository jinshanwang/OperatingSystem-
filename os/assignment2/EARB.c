// a1710974 Jinshan Wang
// a1701108 Jiarong Fan
#include "page.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void EARB(FILE *fp,int PAGESIZE,int NUMPAGES,int INTERVAL){
  long long trace=0;
  int read=0;
  int write=0;
  int INTERVALcounter=0;
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
            // if there is the page fault
            // we need to increment the read
            printf("%s %lld\n", "MISS: PAGE",thisPageNum);
            read++;
            page* target;
            // this is function to check whether
            // f no pages are modified, or if only modified pages are resident,
            // the algorithm should perform thesame as ARB.and return 1
            // If both modified and unmodified pages are resident:EARB and return 0
            if ((EARB_helper(cir_queue,NUMPAGES))==1) {
              // printf("%s\n", "(EARB_helper(cir_queue,NUMPAGES)");
              // find the slot that are available for the new arrival page
               target=ARB_buffer(cir_queue, NUMPAGES);
            }
            else{
               target=EARB_buffer(cir_queue, NUMPAGES);
            }

            // if the previous page is used before
            if (target->pageNum!=-1) {
              printf("%s %lld ", "REPLACE: PAGE",target->pageNum);
            }

            if (target->mbit==1) {
              printf("%s", "(DIRTY)");
              write++;
              target->mbit=0;

            }
            printf("%s\n","" );
            // modify the pageNumber
            target->pageNum=thisPageNum;
            // recording the arrival_time
            target->arrival_time=trace;
            // reset the usebitqueue
            target->usebitqueue=reset(target->usebitqueue);
            // loading the operationType
            target->operationType=single_page_elements[0];
            // modify the mbit according to the operationType
            if(target->operationType[0]=='W')
            {
              target->mbit=1;
            }
         }
         // if this is a HIT
         else
         {   //go to the target slot
             page* targetHit = find(cir_queue,thisPageNum,NUMPAGES);
             targetHit->usebitqueue=modifyBitQueue(targetHit->usebitqueue,1);
             targetHit->operationType=single_page_elements[0];
             if (targetHit->operationType[0]=='W') {
                  targetHit->mbit=1;
            }
              printf("%s %lld\n", "HIT: PAGE",targetHit->pageNum);
         }
         // final step
         // INTERVAL check
         INTERVALcounter++;
         if(INTERVALcounter==INTERVAL)
         {
           Push_Usebit(cir_queue,NUMPAGES);
           INTERVALcounter=0;
         }
        trace++;
        // traverse(cir_queue,NUMPAGES);
        freelist(single_page_elements);
}

          printf("events in trace:    %lld\n", trace);
          printf("total disk reads:   %d\n", read);
          printf("total disk writes:  %d\n", write);
}
