#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"

struct node *head = NULL;
struct node *node = NULL;
// struct node *tail = NULL;

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

Task *pickNextTask()
{
    Task *curr_task = head->task;
    Task *priority_task = curr_task;
    struct node *next_task = head->next;

    while (next_task != NULL)
    {
        if (next_task->task->priority <= priority_task->priority)
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

    while (head != NULL)
    {
        current_task = pickNextTask();
        run(current_task, current_task->burst);
        delete (&head, current_task);
    }
}