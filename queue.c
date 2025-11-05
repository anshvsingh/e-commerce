#include "queue.h"

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}


CartItem *copyCart(CartItem *cartHead)
{
    if (cartHead == NULL)
        return NULL;

    CartItem *newHead = (CartItem *)malloc(sizeof(CartItem));
    newHead->product = cartHead->product;
    newHead->quantity = cartHead->quantity;

    CartItem *currentNew = newHead;
    CartItem *currentOld = cartHead->next;

    while (currentOld != NULL)
    {
        CartItem *newItem = (CartItem *)malloc(sizeof(CartItem));
        newItem->product = currentOld->product;
        newItem->quantity = currentOld->quantity;
        newItem->next = NULL;

        currentNew->next = newItem;
        currentNew = currentNew->next;
        currentOld = currentOld->next;
    }
    return newHead;
}

void enqueue(Queue *q, Order *order)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->order = order;
    newNode->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

Order *dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        return NULL;
    }
    QueueNode *temp = q->front;
    Order *order = temp->order;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(temp);
    return order;
}

void displayQueue(Queue *q)
{
    if (q->front == NULL)
    {
        printf("  Order queue is empty.\n");
        return;
    }
    printf("  --- Pending Orders ---\n");
    QueueNode *current = q->front;
    int count = 1;
    while (current != NULL)
    {
        printf("  %d. Order for User ID: %d (Total: $%.2f)\n",
               count++, current->order->userId, current->order->totalValue);
        current = current->next;
    }
}