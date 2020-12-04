#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

typedef struct Queue
{
    int front;
    int rear;
    int size;
    struct Node** arrayofnode;
} Queue;

Queue* create_queue(int size);
int is_queue_size_one(Queue* queue);
int is_queue_empty(Queue* queue);
int is_queue_full(Queue* queue);
void enQueue(Queue* queue, Node* node);
Node* de_queue(Queue* queue);
Node* get_front_queue(Queue* queue);
Node* find_min_two_queues(Queue* Queue1, Queue* Queue2);


#endif // !QUEUE_H