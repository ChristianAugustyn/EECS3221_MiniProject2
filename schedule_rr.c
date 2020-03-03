/*
Author: Christian Augustyn
Date: March 2, 2020
File: schedule_rr.c
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
    processes++;

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

Task *pickNextTask()
{
    Task *curr_task = head->task;
    struct node *next_task = head->next;

    while (next_task != NULL)
    {
        curr_task = next_task->task;
        next_task = next_task->next;
    }
    return curr_task;
}

void schedule()
{
    Task *current_task;

    while (head != NULL)
    {
        current_task = pickNextTask();

        if (current_task->burst >= QUANTUM)
        {
            run(current_task, QUANTUM);
            time += QUANTUM;
        }
        else
        {
            run(current_task, current_task->burst);
            time += current_task->burst;
        }

        current_task->burst -= QUANTUM;
        if (current_task->burst <= 0)
        {
            completion_time += time;
            total_completion_time += completion_time;
            if (current_task->burst >= QUANTUM)
            {
                waittime += completion_time - QUANTUM;
            }
            else
            {
                waittime += completion_time - current_task->burst; //remiaing
            }
            delete (&head, current_task);
        }
        else
        {
            delete (&head, current_task);
            insert(&head, current_task);
        }

    }

    avg_turnaround = total_completion_time / processes;
    avg_wait = waittime / processes;
    avg_response = (QUANTUM * processes) / processes;

    printf("Average Turnaround Time: %.2f\nAverage Waiting Time: %.2f\nAverage Response Time: %.2f\n", avg_turnaround, avg_wait, avg_response);
}