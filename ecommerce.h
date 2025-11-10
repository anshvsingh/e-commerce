#ifndef ECOMMERCE_H
#define ECOMMERCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



typedef enum Category {
    CAT_MOBILES,
    CAT_LAPTOPS,
    CAT_WATCHES,
    CAT_PENS,
    CAT_CLOTHES,
    CAT_EARPHONES
} Category;

typedef enum PriceRange {
    RANGE_HIGH,
    RANGE_MID,
    RANGE_LOW
} PriceRange;



typedef struct Product {
    int id;
    char name[100];
    double price;
    int stock;
    Category category;
    PriceRange range;
} Product;

typedef struct BSTNode {
    Product* product;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct CartItem {
    Product* product;
    int quantity;
    struct CartItem* next;
} CartItem;

typedef struct StackNode {
    int productId;
    struct StackNode* next;
} StackNode;

typedef struct User {
    int id;
    char username[50];
    char password[50];
    char address[200];
    CartItem* cartHead;
    StackNode* historyHead;
    struct User* next;
} User;

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


const char* getCategoryName(Category cat);
Product* createProduct(int id, const char* name, double price, int stock, Category category, PriceRange range);
BSTNode* insertProduct(BSTNode* node, Product* product);
BSTNode* findProduct(BSTNode* root, int id);
void displayProducts(BSTNode* root);
int displayProductsByCategory(BSTNode* root, Category cat);
int displaySuggestions(BSTNode* root, Category cat, PriceRange range, int currentProdId);


User* createUser(int id, const char* username, const char* password);
void addUser(User** head, User* user);
User* findUserByUsername(User* head, const char* username);
void addToCart(User* user, Product* product, int quantity);
void displayCart(User* user);
CartItem* clearCart(CartItem* head);


void pushHistory(User* user, int productId);
void displayHistory(User* user);


Queue* createQueue();
void enqueue(Queue* q, Order* order);
Order* dequeue(Queue* q);
void displayQueue(Queue* q);
CartItem* copyCart(CartItem* cartHead);

#endif 