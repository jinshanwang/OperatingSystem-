
// a1710974 Jinshan Wang
// a1701108 Jiarong Fan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OnlineService.h"
#include "function.c"
#include "process.h"
#include "queue.c"

int main(int argc, char const *argv[]) {

process* queue;
process* queue1_6;
process* queue1_5;
process* queue2;
process* queue3;
process* finish;
queue   = Initialization();
queue1_6= Initialization();
queue1_5= Initialization();
queue2  = Initialization();
queue3  = Initialization();
finish= Initialization();
int timer=0;
int premmption_factor=0;
FILE *fp;
if ((fp = fopen(argv[1],"r"))==NULL) {
  printf("cannot open file\n");
  exit(0);
}
char *process_String;
char **element_of_process;
int i=0;

while ((process_String=next_cmd(fp))!=NULL) {

      element_of_process=splitline(process_String);
      queue=push_back(queue,element_of_process);
      i++;

}

while (1) {

if (queue->next!=NULL) {
  process* currentProcess=queue->next;
  while (currentProcess!=NULL) {

    if(currentProcess->Arrival==timer)
    {

      if(currentProcess->Priority==6)
      {

        queue1_6=move(currentProcess,queue,queue1_6);
        currentProcess=queue->next;
        continue;

      }
      else if(currentProcess->Priority==5)
      {

        queue1_5=move(currentProcess,queue,queue1_5);
        currentProcess=queue->next;
        continue;
      }
      else if((currentProcess->Priority==3 || currentProcess->Priority==4))
      {

        queue2=move(currentProcess,queue,queue2);
        currentProcess=queue->next;
        continue;
      }
      else if(currentProcess->Priority==1 || currentProcess->Priority==2)
      {

        queue3=move(currentProcess,queue,queue3);
        currentProcess=queue->next;
        continue;
      }

    }
    currentProcess=currentProcess->next;
  }
}

// we finished the check here from the very begining
//this is a mechanism of the priority
// Queue 1 has absolute priority over Queue 2 and Queue 3,
// and Queue 2 has absolute priority over Queue 3.
// In other words, customer requests in Queue 2 will be
// processed only if there is no customer in Queue 1,
// and customer requests in Queue 3 will be processed only if
// no customer is in Queue 1 and Queue 2.

// SITUATION 1 :
//if queue1_6 is not empty
if (isEmpty(queue1_6)==0) {
  process *current_Queue1_6=queue1_6->next;
  if (queue2->next!=NULL && queue2->next->runs!=0) {
    // we need to use premmption here
    aging(queue2,queue3,queue1_5,queue2->next,timer);
    if (queue2->next->runs<10) {
      queue2->next->runs=9;
      if (queue2->next->sub_completed<10) {
        queue2->next->sub_completed=9;
      }
      else{
        queue2->next->sub_completed=19;
      }
    }
    queue2=RR(queue2);
  }
  if (queue3->next!=NULL && queue3->next->runs!=0) {
    // we need to use premmption here
    aging(queue2,queue3,queue1_5,queue3->next,timer);
    queue3->next->runs=0;
    queue3=RR(queue3);
  }

  if(current_Queue1_6->Completed == current_Queue1_6->CPU_time){

    aging(queue2,queue3,queue1_5,queue1_6,timer);
    current_Queue1_6->End=timer;
    current_Queue1_6->Waiting=getWaitingTime(current_Queue1_6);
    finish=move(queue1_6->next,queue1_6,finish);
    movePromoted(queue2, queue3, queue1_5);
    }
  else if (current_Queue1_6->runs==5) {

    aging(queue2,queue3,queue1_5,queue1_6,timer);
    if (current_Queue1_6->sub_completed==25) {
      current_Queue1_6->Priority--;                 //decrease the priority of the customers
      current_Queue1_6->sub_completed=0;            //reset the sub-Completed(5 runs) to 0
      current_Queue1_6->runs=0;                     //reset the runs to 0
      queue1_5=move(queue1_6->next,queue1_6,queue1_5);
      }else{
        current_Queue1_6->runs=0;
        queue1_6=RR(queue1_6);
      }
      movePromoted(queue2, queue3, queue1_5);
  }
   if (queue1_6->next!=NULL&&queue1_6->next->Completed==0) {
      queue1_6->next->Ready=timer;
      if (queue1_5->next!=NULL && queue1_5->next->runs==5) {

      aging(queue2,queue3,queue1_5,queue1_6,timer);
      if (queue1_5->next->sub_completed==25) {
          queue1_5->next->Priority--;                 //decrease the priority of the customers
          queue1_5->next->sub_completed=0;            //reset the sub-Completed(5 runs) to 0
          queue1_5->next->runs=0;

        queue2=move(queue1_5->next,queue1_5,queue2);

      }else{
        queue1_5->next->runs=0;
        queue1_5=RR(queue1_5);
      }
      movePromoted(queue2, queue3, queue1_5);
      }
    }
    Completed_increment_1(queue1_6);

}
  // situation 2
  // if queue1_6 is empty and queue1_5 is not empty
  // we can do the Operation in queue1_5
if (isEmpty(queue1_6)==1 && isEmpty(queue1_5)==0) {
    process *current_Queue1_5=queue1_5->next;
    if (queue2->next!=NULL && queue2->next->runs!=0) {
      // we need to use premmption here
      aging(queue2,queue3,queue1_5,queue2->next,timer);
      if (queue2->next->runs<10) {
        queue2->next->runs=9;
        if (queue2->next->sub_completed<10) {
          queue2->next->sub_completed=9;
        }
        else{
          queue2->next->sub_completed=19;
        }
      }
      queue2=RR(queue2);
    }
    if (queue3->next!=NULL && queue3->next->runs!=0) {
      // we need to use premmption here
      aging(queue2,queue3,queue1_5,queue3->next,timer);
      queue3->next->runs=0;
      queue3=RR(queue3);
    }
    if(current_Queue1_5->Completed == current_Queue1_5->CPU_time){
      aging(queue2,queue3,queue1_5,queue1_6,timer);
      current_Queue1_5->End=timer;
      current_Queue1_5->Waiting=getWaitingTime(current_Queue1_5);
      finish=move(current_Queue1_5,queue1_5,finish);
      movePromoted(queue2, queue3, queue1_5);
    }

    else if (current_Queue1_5->runs==5) {
      aging(queue2,queue3,queue1_5,queue1_6,timer);
      if (current_Queue1_5->sub_completed==25) {
        current_Queue1_5->Priority--;                 //decrease the priority of the customers
        current_Queue1_5->sub_completed=0;            //reset the sub-Completed(5 runs) to 0
        current_Queue1_5->runs=0;
        //reset the runs to 0
        queue2=move(current_Queue1_5,queue1_5,queue2);
      }else{
        current_Queue1_5->runs=0;
        queue1_5=RR(queue1_5);
      }
      movePromoted(queue2, queue3, queue1_5);
    }
    if (queue1_5->next!=NULL&&queue1_5->next->Completed==0) {
       queue1_5->next->Ready=timer;
     }
    Completed_increment_1(queue1_5);
}
// aging :
// when queue1_6 and queue1_5 are not empty
  //situation 3
  // if there is no queue1_6 and queue1_5 but the queue2 is not empty
 if (isEmpty(queue1_6)==1 && isEmpty(queue1_5)==1 && isEmpty(queue2)==0) {
  process *current_Queue2=queue2->next;
  if(current_Queue2->Completed==current_Queue2->CPU_time)
  {
    aging(queue2,queue3,queue1_5,current_Queue2,timer);
    current_Queue2->End=timer;
    current_Queue2->Waiting=getWaitingTime(current_Queue2);
    finish=move(current_Queue2,queue2,finish);
    movePromoted(queue2, queue3, queue1_5);
  }
  else if(current_Queue2->runs==10)
  {
    aging(queue2,queue3,queue1_5,current_Queue2,timer);
    if (current_Queue2->sub_completed==20) {
      current_Queue2->Priority--;                 //decrease the priority of the customers
      current_Queue2->sub_completed=0;            //reset the sub-Completed(5 runs) to 0
      current_Queue2->runs=0;
      //reset the runs to 0
      if(current_Queue2->Priority<3)
      {
        queue3=move(current_Queue2,queue2,queue3);
      }

    }else{
      current_Queue2->runs=0;
      queue2=RR(queue2);
    }
    movePromoted(queue2, queue3, queue1_5);
  }
  if (queue2->next!=NULL&&queue2->next->Completed==0) {
     queue2->next->Ready=timer;
   }
   if ( queue2->next!=NULL&&queue2->next->sub_completed==1 ) {
     queue2->next->age=0;
   }
  Completed_increment_1(queue2);
}
// situation 4
 if (isEmpty(queue1_6)==1 && isEmpty(queue1_5)==1 && isEmpty(queue2)==1 && isEmpty(queue3)==0) {
   process* current_Queue3=queue3->next;

   if(current_Queue3->Completed==current_Queue3->CPU_time)
   {
     aging(queue2,queue3,queue1_5,current_Queue3,timer);
     current_Queue3->End=timer;
     current_Queue3->Waiting=getWaitingTime(current_Queue3);
     finish=move(current_Queue3,queue3,finish);
     movePromoted(queue2, queue3, queue1_5);
   }
   else if(current_Queue3->runs==20)
   {
     aging(queue2,queue3,queue1_5,current_Queue3,timer);
       current_Queue3->runs=0;
       queue3=RR(queue3);
     movePromoted(queue2, queue3, queue1_5);
   }
   if (queue3->next!=NULL&&queue3->next->Completed==0) {
      queue3->next->Ready=timer;
    }
   Completed_increment_1(queue3);

}
    if (isEmpty(queue)==1 && isEmpty(queue1_6)==1 && isEmpty(queue1_5)==1 && isEmpty(queue2)==1 && isEmpty(queue3)==1) {

      break;
    }
  timer++;

}
  printf("%s\n", "Index	Priority	Arrival	End	Ready	CPU_Time	Waiting");
  traverse(finish);
  fclose(fp);
  return 0;
}
