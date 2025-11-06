#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef enum Category {
    CAT_ELECTRONICS,
    CAT_SPORTS,
    CAT_BOOKS,
    CAT_WATCHES,
    CAT_FASHION,
    CAT_HOME_DECOR
} Category;

//  Product & BST (Tree) 
typedef struct Product {
    int id;
    char name[100];
    double price;
    int stock;
    Category category; 
} Product;

typedef struct BSTNode {
    Product* product;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Cart (Linked List) 
typedef struct CartItem {
    Product* product;
    int quantity;
    struct CartItem* next;
} CartItem;

//  History (Stack) 
typedef struct StackNode {
    int productId;
    struct StackNode* next;
} StackNode;

// User (Linked List) 
typedef struct User {
    int id;
    char username[50];
    char password[50];
    char address[200];    
    CartItem* cartHead;
    StackNode* historyHead; 
    struct User* next;
} User;

// Order (Queue) 
typedef struct Order {
    int userId;
    CartItem* itemsHead; 
    double totalValue;

    char deliveryAddress[200]; 
} Order;

typedef struct QueueNode {
    Order* order;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;


extern BSTNode* g_productRoot;
extern User* g_userListHead;
extern Queue* g_orderQueue;

extern int g_nextUserId;


extern const char* getCategoryName(Category cat);


#endif