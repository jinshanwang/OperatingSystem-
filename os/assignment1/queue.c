// a1710974 Jinshan Wang
// a1701108 Jiarong Fan
#include "process.h"
process* Initialization(){
    process *HEAD;
    HEAD = (process*)malloc(sizeof(process));
    HEAD->Index="fdsf";
    HEAD->previous = NULL;
    HEAD->next     = NULL;
    return HEAD;
}

process* push_back(process* HEAD,char** input){
    process *newProcess;
    newProcess = (process*)malloc(sizeof(process));
    // input the value of the struct member
    newProcess->Index    =input[0];
    newProcess->Arrival  =atoi(input[1]);
    newProcess->Priority =atoi(input[2]);
    newProcess->age      =atoi(input[3]);
    newProcess->CPU_time =atoi(input[4]);
    newProcess->End      =0;
    newProcess->Completed=0;
    newProcess->Ready    =0;
    newProcess->Waiting  =0;
    newProcess->runs     =0;
    newProcess->next     =NULL;
    newProcess->sub_completed=0;
  // get the tail of the List
    if (HEAD->next==NULL) {
      HEAD->next=newProcess;
      newProcess->previous=HEAD;
    }else{
      process *temp=HEAD->next;
      while (temp->next!=NULL) {
        temp=temp->next;
      }
      temp->next= newProcess;
      newProcess->previous= temp;
    }
    return HEAD;
}

//traverse the queue
void traverse(process* HEAD) {
  process* temp=HEAD->next;
    while (temp!=NULL) {
      printf("%s\t", temp->Index);
      printf("%d\t", temp->Priority);
      printf("%d\t", temp->Arrival);
      printf("%d\t", temp->End);
      printf("%d\t", temp->Ready );
      printf("%d\t", temp->CPU_time);
      printf("%d\n", temp->Waiting );
      temp=temp->next;
    }
}

//get the length of the queue
int getLength(process* HEAD){
    int length=0;
    process *temp=HEAD->next;
    while (temp!=NULL) {
      length++;
      temp=temp->next;
    }
    return length;
}

//Round Robin Algorithm
process* RR(process* HEAD)
{
  process* current=HEAD->next;
  if (current->next==NULL) {
    return HEAD;
  }
    // get the lasrt process in queue
    process* TAIL;
    process* temp=HEAD->next;
    while (temp->next!=NULL) {
      temp=temp->next;
    }
    TAIL=temp;
    // get the first process and connect the HEAD to the process
    // that follow by the first process
    process* RR_process;
    RR_process          = HEAD->next;
    HEAD->next          = RR_process->next;
    HEAD->previous      = NULL;
    RR_process->next    = NULL;
    TAIL->next          = RR_process;
    RR_process->previous= TAIL;
    return HEAD;
}

process* getNext(process* node){
    return node->next;
}

process* getNode(process* HEAD,char* index){
    process* current=HEAD->next;
    while (current!=NULL) {
      if (strcmp(current->Index,index)==0) {
          break;
      }
      current=current->next;
    }
    return current;
}

process* move(process * current, process *original_queue, process *target_queue)
{
  process* target_process;
  // when the node is tail
  if (current->next==NULL) {

    target_process=pop_back(current);

  }
  // when the node is within the list
  else{
    target_process=pop(current,original_queue);
  }

   target_queue=schedualer_push_back(target_queue,target_process);
   return target_queue;
}

// this is a default situation when the node we want to pop is within the head and the TAIL
  process* pop(process* node,process* HEAD){
    if (HEAD->next==node) {
      HEAD->next=node->next;
      node->next->previous=HEAD;
    }
    else{
      process* nodeNext=node->next;
      process* nodePrev=node->previous;
      nodePrev->next=nodeNext;
      nodeNext->previous=nodePrev;
    }
    return node;
  }

  process* pop_back(process* node){
    process* temp;
    temp = node;
    process* previousItem=node->previous;
    previousItem->next=NULL;
    return temp;

  }


  // this is the schedualer
  // we only need to consider one circumstance
  process* schedualer_push_back(process* target_queue,process* node){
    if (target_queue->next==NULL) {
      target_queue->next=node;
      node->previous=target_queue;
      node->next=NULL;
    }else{
      process *temp=target_queue->next;
      while (temp->next!=NULL) {
        temp=temp->next;
      }
      temp->next= node;
      node->previous= temp;
      node->next=NULL;
    }
    return target_queue;
  }

int isEmpty(process* HEAD){
  // if it is empty
  if (HEAD->next==NULL) {
    // HEAD->next=NULL;

    return 1;
  }
  // if it is not empty
  return 0;
}

int getWaitingTime(process* node){
  return node->End-node->Ready-node->CPU_time;
}

void Completed_increment_1(process* HEAD){
  process* Completing_node=HEAD->next;
  if (Completing_node!=NULL) {
    Completing_node->Completed++;
    Completing_node->sub_completed++;
    Completing_node->runs++;
  }
}

//aging
void aging(process *queue2, process *queue3, process *queue1_5, process *current,int timer)
{
  process* Head2=queue2;
  process* Head3=queue3;
  //when current process in queue2
  if(Head2->next!=NULL&&current==Head2->next)
  {
    if(current->sub_completed==2)
    {
      current->age=0;
    }

    Head2=Head2->next;                          //from head to first element
    while(Head2->next!=NULL)
    {
      Head2=Head2->next;                          //this node from second
      if (Head2->Arrival!=timer) {
        Head2->age++;
      }
      if(Head2->age>7)
      {
        Head2->age=0;
        Head2->Priority++;

      }
    }
    while (Head3->next!=NULL) {
      Head3=Head3->next;
      if (Head3->Arrival!=timer) {
        Head3->age++;
      }
      if(Head3->age>7)
      {
        Head3->age=0;
        Head3->Priority++;
      }
    }
  }
  //when current process in queue3
  else if(Head3->next!=NULL&&current==Head3->next)
  {
    if(current->sub_completed==2)
    {
      current->age=0;
    }
    Head3=Head3->next;                          //from head to first element
    while(Head2->next!=NULL)
    {
      Head2=Head2->next;                          //this node from second
      if (Head2->Arrival!=timer) {
        Head2->age++;
      }

      if(Head2->age>7)
      {
        Head2->age=0;
        Head2->Priority++;

      }
    }
    while (Head3->next!=NULL) {
      Head3=Head3->next;                       //this node from second
      if (Head3->Arrival!=timer) {
        Head3->age++;
      }

      if(Head3->age>7)
      {
        Head3->age=0;
        Head3->Priority++;
      }
    }

  }
  //when current process in queue 1
  else
  {
    Head2=Head2->next;
    Head3=Head3->next;
    while(Head2!=NULL)
    {
      if (Head2->Arrival!=timer) {
        Head2->age++;
      }
      if(Head2->age>7)
      {
        Head2->age=0;
        Head2->Priority++;
      }
      Head2=Head2->next;
    }
    while (Head3!=NULL) {

      if (Head3->Arrival!=timer) {
        Head3->age++;
      }
      if(Head3->age>7)
      {
        Head3->age=0;
        Head3->Priority++;
      }
        Head3=Head3->next;

    }
  }
}

void movePromoted(process *queue2, process *queue3, process *queue1_5)
{
  process* Head2=queue2;
  process* Head3=queue3;
  Head2=Head2->next;
  Head3=Head3->next;
  while (Head2!=NULL) {
    if(Head2->Priority>4)
    {
      queue1_5=move(Head2,queue2,queue1_5);
      Head2=queue2->next;
      continue;
    }
    Head2=Head2->next;
  }
  while (Head3!=NULL) {
    if(Head3->Priority>2)
    {
      queue2=move(Head3,queue3,queue2);
      Head3=queue3->next;
      continue;
    }
    Head3=Head3->next;
  }
}
