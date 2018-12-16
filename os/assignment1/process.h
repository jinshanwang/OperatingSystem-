// a1710974 Jinshan Wang
// a1701108 Jiarong Fan

#ifndef process_h
#define process_h

#include <stdio.h>

typedef struct process
{
    char* Index;                // the name of the process
    int intIndex;
    int Priority;               //Priority
    int Arrival;                // the arrival time
    int age;                    // increase by one every 7 run
    int CPU_time;               // how many time units the process require
    int Completed;              // degree to completed
    int sub_completed;
    int End;                    // what time it finished
    int Ready;                  // what time it ready
    int runs;                   //the runs of one process
    int Waiting;
    int RR_switch;
    struct process* next;       //the pointer point to the next process
    struct process* previous;   //the pointer point to the previous process
}process;
// method
process* getNext(process* node);
process* getNode(process* HEAD,char* index);
process* Initialization();
process* push_back(process* HEAD,char** input);
void     traverse(process* HEAD);
int      getLength(process* HEAD);
process* RR(process* HEAD); //Round Robin Algorithm
process*    move(process * current, process *original_queue, process *target_queue);
process* pop(process* node, process* HEAD);
process* pop_back(process* node);
process* schedualer_push_back(process* target_queue,process* node);
int isEmpty(process* HEAD);
int getWaitingTime(process* node);
void Completed_increment_1(process* HEAD);
void aging(process *queue2, process *queue3, process *queue1_5, process *current,int timer);
void movePromoted(process *queue2, process *queue3, process *queue1_5);
#endif /* process_h */
