#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"


Queue* create_queue(int size)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue != NULL) {
        queue->front = -1;
        queue->rear = -1;
        queue->size = size;
        queue->arrayofnode = (Node**)malloc(queue->size * sizeof(Node*));
    }
    return queue;
}

int is_queue_size_one(Queue* queue)
{
    if ((queue->front == queue->rear) && (queue->front != -1)) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_queue_empty(Queue* queue)
{
    if (queue->front == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_queue_full(Queue* queue)
{
    if (queue->rear == queue->size - 1) {
        return 1;
    }
    else {
        return 0;
    }
}

void en_queue(Queue* queue, Node* node)
{
    if (!is_queue_full(queue) && node != NULL) {
        queue->arrayofnode[++queue->rear] = node;
        if (queue->front == -1) {
            ++queue->front;
        }
    }
}

Node* de_queue(Queue* queue)
{
    if (!is_queue_empty(queue)) {
        Node* temp = queue->arrayofnode[queue->front];
        if (queue->front == queue->rear) { // There is only one item in the array
            queue->front = -1;
            queue->rear = -1;
        }
        else {
            ++queue->front;
        }
        return temp;
    }
}

Node* get_front_queue(Queue* queue)
{
    if (is_queue_empty(queue)) {
        return NULL;
    }
    return queue->arrayofnode[queue->front];
}

Node* find_min_two_queues(Queue* Queue1, Queue* Queue2)
{
    if (Queue1 != NULL && Queue2 != NULL) {
        // If queue 1 is empty, dequeue from queue 2
        if (is_queue_empty(Queue1)) {
            return de_queue(Queue2);
        }

        // If queue 2 is empty, dequeue from queue 1
        if (is_queue_empty(Queue2)) {
            return de_queue(Queue1);
        }

        // Else compare the front of the two queues and dequeue min
        if (get_front_queue(Queue1)->occ < get_front_queue(Queue2)->occ) {
            return de_queue(Queue1);
        }
        //Last possibility
        return de_queue(Queue2);
    }
}



