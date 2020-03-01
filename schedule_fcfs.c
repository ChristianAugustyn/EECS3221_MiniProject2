#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"

struct node *head = NULL;
struct node *node = NULL;
// struct node *tail = NULL;

void add(char *name, int priority, int burst)
{
    Task *task = malloc(sizeof(struct node));

    task->name = name;
    task->priority = priority;
    task->burst = burst;

    if (head == NULL)
    {
        head = malloc(sizeof(struct node));
        head->task = task;
    }
    else 
    {
        insert(&head, task);
    }
}



void schedule()
{
    traverse(head);
    printf("yeet\n");
}

