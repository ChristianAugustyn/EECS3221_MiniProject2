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

    if (head == NULL)//if the list has not been created
    {
        head = malloc(sizeof(struct node));//allocate size for the head node
        head->task = task; //assign task to the task attribute in head
    }
    else 
    {
        insert(&head, task);//insert the new node as the head and give a link to the previous head
    }
}

Task *pickNextTask() {
    Task *curr_task = head->task;
    struct node *next_task = head->next;

    while(next_task != NULL)
    {
        curr_task = next_task->task; //assigns the current task to be the next nodes task
        next_task = next_task->next; //makes the next task the pointer to the next node in the struct
    }

    return curr_task; //returns the last task in the linked list which is the first ordered item
}

void schedule()
{
    Task *current_task;

    while(head != NULL)
    {
        current_task = pickNextTask(); //find the first task in the linked list
        run(current_task, current_task->burst); //runs it
        delete(&head, current_task); //removes the tail from the linked list 
    }
}

