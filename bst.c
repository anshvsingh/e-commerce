#include "bst.h"
#include <string.h> // for strncpy
#include <stdlib.h> // for malloc
#include <stdio.h>  // for printf

// UPDATED: Helper function to get a string name for a category
const char* getCategoryName(Category cat) {
    switch (cat) {
        case CAT_MOBILES:   return "Mobiles";
        case CAT_LAPTOPS:   return "Laptops";
        case CAT_WATCHES:   return "Watches";
        case CAT_PENS:      return "Pens";
        case CAT_CLOTHES:   return "Clothes";
        case CAT_EARPHONES: return "Earphones";
        default:            return "Unknown";
    }
}

// NEW: Helper for range (mostly for debugging, not shown to user)
const char* getRangeName(PriceRange range) {
    switch(range) {
        case RANGE_HIGH: return "High End";
        case RANGE_MID:  return "Mid Range";
        case RANGE_LOW:  return "Low Range";
        default:         return "Unknown";
    }
}

// Creates a new Product - UPDATED
Product* createProduct(int id, const char* name, double price, int stock, Category category, PriceRange range) {
    Product* p = (Product*)malloc(sizeof(Product));
    p->id = id;
    strncpy(p->name, name, 99);
    p->name[99] = '\0';
    p->price = price;
    p->stock = stock;
    p->category = category;
    p->range = range; // <-- SETS THE HIDDEN RANGE
    return p;
}

// Inserts a new product into the BST
BSTNode* insertProduct(BSTNode* node, Product* product) {
    // ... (This function is unchanged) ...
    if (node == NULL) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->product = product;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (product->id < node->product->id) {
        node->left = insertProduct(node->left, product);
    } else if (product->id > node->product->id) {
        node->right = insertProduct(node->right, product);
    }

    return node;
}

// Finds a product in the BST by ID
BSTNode* findProduct(BSTNode* root, int id) {
    // ... (This function is unchanged) ...
    if (root == NULL || root->product->id == id) {
        return root;
    }
    if (id < root->product->id) {
        return findProduct(root->left, id);
    }
    return findProduct(root->right, id);
}

// Displays all products (in-order traversal) - UPDATED
void displayProducts(BSTNode* root) {
    if (root != NULL) {
        displayProducts(root->left);
        // Only shows category, NOT range
        printf("  ID: %-3d | Name: %-20s | Price: $%.2f | Stock: %-3d | Category: %s\n",
               root->product->id, root->product->name,
               root->product->price, root->product->stock,
               getCategoryName(root->product->category)); 
        displayProducts(root->right);
    }
}

// Displays products by category (in-order traversal)
int displayProductsByCategory(BSTNode* root, Category cat) {
    // ... (This function is unchanged, it shows all ranges) ...
    if (root == NULL) {
        return 0; // No products found in this branch
    }
    int countLeft = displayProductsByCategory(root->left, cat);
    int countRight = displayProductsByCategory(root->right, cat);
    int countCurrent = 0;
    if (root->product->category == cat) {
        printf("  ID: %-3d | Name: %-20s | Price: $%.2f | Stock: %d\n",
               root->product->id, root->product->name,
               root->product->price, root->product->stock);
        countCurrent = 1;
    }
    return countLeft + countRight + countCurrent;
}

// UPDATED: Displays suggestions (same category AND range, different item)
int displaySuggestions(BSTNode* root, Category cat, PriceRange range, int currentProdId) {
    if (root == NULL) {
        return 0; // No suggestions in this branch
    }

    // Recursively search
    int countLeft = displaySuggestions(root->left, cat, range, currentProdId);
    int countRight = displaySuggestions(root->right, cat, range, currentProdId);

    int countCurrent = 0;
    
    // UPDATED: Now checks category, range, and ID
    if (root->product->category == cat && 
        root->product->range == range && 
        root->product->id != currentProdId) {
        
        printf("  ID: %-3d | Name: %-20s | Price: $%.2f | Stock: %d\n",
               root->product->id, root->product->name,
               root->product->price, root->product->stock);
        countCurrent = 1;
    }
    
    // Return total suggestions found
    return countLeft + countRight + countCurrent;
}