#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// --- Product & BST (Tree) ---
typedef struct Product
{
    int id;
    char name[100];
    double price;
    int stock;
} Product;

typedef struct BSTNode
{
    Product *product;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// --- Cart (Linked List) ---
typedef struct CartItem
{
    Product *product;
    int quantity;
    struct CartItem *next;
} CartItem;

// --- History (Stack) ---
typedef struct StackNode
{
    int productId;
    struct StackNode *next;
} StackNode;

// --- User (Linked List) ---
typedef struct User
{
    int id;
    char username[50];
    CartItem *cartHead;
    StackNode *historyHead; // Top of the stack
    struct User *next;
} User;

// --- Order (Queue) ---
typedef struct Order
{
    int userId;
    CartItem *itemsHead; // A copy of the cart at checkout
    double totalValue;
    int deliveryCity;
} Order;

typedef struct QueueNode
{
    Order *order;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

// --- Delivery (Graph) ---
typedef struct GraphNode
{
    int dest;
    int weight;
    struct GraphNode *next;
} GraphNode;

typedef struct Graph
{
    int numVertices;
    GraphNode **adjLists; // Array of linked lists
} Graph;

// --- Priority Queue for Dijkstra (Min-Heap / Array-Tree) ---
typedef struct MinHeapNode
{
    int v;    // Vertex number
    int dist; // Distance from source
} MinHeapNode;

typedef struct MinHeap
{
    int size;     // Number of heap nodes present
    int capacity; // Capacity of min heap
    int *pos;     // For decreaseKey
    MinHeapNode **array;
} MinHeap;

// --- Global Data Declarations ---
extern BSTNode *g_productRoot;
extern User *g_userListHead;
extern Queue *g_orderQueue;
extern Graph *g_deliveryGraph;

#endif