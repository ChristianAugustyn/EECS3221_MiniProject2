/*
Author: Christian Augustyn
Date: March 2, 2020
File: schedule_priority_rr.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"

struct node *head = NULL;
struct node *node = NULL;
// struct node *tail = NULL;
float avg_turnaround;
float avg_wait;
float avg_response;
float total_completion_time;

int processes;
int time;
float completion_time;
int waittime;

void add(char *name, int priority, int burst) //adds a new task to the list
{
    Task *task = malloc(sizeof(struct node)); //creates a new task struct
    //assigns all the attributes
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    if (head == NULL) //if the list has not been created
    {
        head = malloc(sizeof(struct node)); //allocate size for the head node
        head->task = task;                  //assign task to the task attribute in head
    }
    else
    {
        insert(&head, task); //insert the new node as the head and give a link to the previous head
    }
}

Task *pickNextTask(int priority)
{
    Task *curr_task = head->task;
    Task *priority_task = curr_task;
    struct node *next_task = head->next;

    while (next_task != NULL)
    {
        if (next_task->task->priority == priority)
        {
            priority_task = next_task->task;
        }
        curr_task = next_task->task; //assigns the current task to be the next nodes task
        next_task = next_task->next; //makes the next task the pointer to the next node in the struct
    }

    return priority_task;
}

void schedule()
{
    Task *current_task;
    int pri = 10;

    while(head != NULL)
    {
        while(pri >= 1 && head != NULL)
        {
            current_task = pickNextTask(pri);
            if (current_task->priority == pri)
            {
                if (current_task->burst >= QUANTUM)
                {
                    run(current_task, QUANTUM);

                }
                else
                {
                    run(current_task, current_task->burst);
                }

                current_task->burst -= QUANTUM;
                if (current_task->burst <= 0)
                {
                    delete (&head, current_task);
                }
                else
                {
                    delete (&head, current_task);
                    insert(&head, current_task);
                }
            }
            else
            {
                pri--;
            }
        }
        pri--;
    }
}