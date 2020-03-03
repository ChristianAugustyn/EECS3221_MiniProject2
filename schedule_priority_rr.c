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
    
}

void schedule()
{
    
}