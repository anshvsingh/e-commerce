#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// --- UPDATED: Product Category Enum ---
typedef enum Category {
    CAT_MOBILES,
    CAT_LAPTOPS,
    CAT_WATCHES,
    CAT_PENS,
    CAT_CLOTHES,
    CAT_EARPHONES
} Category;

// --- NEW: Product Price Range Enum (Hidden) ---
typedef enum PriceRange {
    RANGE_HIGH,
    RANGE_MID,
    RANGE_LOW
} PriceRange;

// --- Product & BST (Tree) ---
typedef struct Product {
    int id;
    char name[100];
    double price;
    int stock;
    Category category; // <-- Visible category
    PriceRange range;  // <-- Hidden price range
} Product;

typedef struct BSTNode {
    Product* product;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// --- Cart (Linked List) ---
typedef struct CartItem {
    Product* product;
    int quantity;
    struct CartItem* next;
} CartItem;

// --- History (Stack) ---
typedef struct StackNode {
    int productId;
    struct StackNode* next;
} StackNode;

// --- User (Linked List) ---
typedef struct User {
    int id;
    char username[50];
    char password[50];
    char address[200];      // User's saved address
    CartItem* cartHead;
    StackNode* historyHead; // Top of the stack
    struct User* next;
} User;

// --- Order (Queue) ---
typedef struct Order {
    int userId;
    CartItem* itemsHead; // A copy of the cart at checkout
    double totalValue;
    char deliveryAddress[200]; // Copy of user's full address
} Order;

typedef struct QueueNode {
    Order* order;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// --- Global Data Declarations ---
extern BSTNode* g_productRoot;
extern User* g_userListHead;
extern Queue* g_orderQueue;
extern int g_nextUserId;

// --- Helper function to get category name ---
extern const char* getCategoryName(Category cat);
// (We don't need a prototype for getRangeName, it's only used in bst.c)

#endif