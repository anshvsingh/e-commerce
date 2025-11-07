#ifndef BST_H
#define BST_H

#include "structs.h"

// Product & BST functions
// Updated to include category and range
Product* createProduct(int id, const char* name, double price, int stock, Category category, PriceRange range);

BSTNode* insertProduct(BSTNode* node, Product* product);
BSTNode* findProduct(BSTNode* root, int id);
void displayProducts(BSTNode* root); // In-order traversal

// Displays only products in a specific category
int displayProductsByCategory(BSTNode* root, Category cat);

// UPDATED: Displays suggestions (same category AND range, excludes current item)
int displaySuggestions(BSTNode* root, Category cat, PriceRange range, int currentProdId);


#endif