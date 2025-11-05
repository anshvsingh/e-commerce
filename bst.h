#ifndef BST_H
#define BST_H

#include "structs.h" 

// Product & BST functions
Product* createProduct(int id, const char* name, double price, int stock, Category category);

BSTNode* insertProduct(BSTNode* node, Product* product);
BSTNode* findProduct(BSTNode* root, int id);
void displayProducts(BSTNode* root); // In-order traversal


int displayProductsByCategory(BSTNode* root, Category cat);


int displaySuggestions(BSTNode* root, Category cat, int currentProdId);


#endif