#ifndef QUEUE_H
#define QUEUE_H

#include "structs.h"

Queue *createQueue();
void enqueue(Queue *q, Order *order);
Order *dequeue(Queue *q);
void displayQueue(Queue *q);
CartItem *copyCart(CartItem *cartHead); 

#endif