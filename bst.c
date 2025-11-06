#include "bst.h"
#include <string.h> 
#include <stdlib.h> 
#include <stdio.h>  


const char* getCategoryName(Category cat) {
    switch (cat) {
        case CAT_ELECTRONICS: return "Electronics";
        case CAT_SPORTS:      return "Sports";
        case CAT_BOOKS:       return "Books";
        case CAT_WATCHES:     return "Watches";
        case CAT_FASHION:       return "Fashion";
        case CAT_HOME_DECOR:     return "Home_Decor";
    }
}


Product* createProduct(int id, const char* name, double price, int stock, Category category) {
    Product* p = (Product*)malloc(sizeof(Product));
    p->id = id;
    strncpy(p->name, name, 99);
    p->name[99] = '\0';
    p->price = price;
    p->stock = stock;
    p->category = category; 
    return p;
}

BSTNode* insertProduct(BSTNode* node, Product* product) {
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


BSTNode* findProduct(BSTNode* root, int id) {
    if (root == NULL || root->product->id == id) {
        return root;
    }
    if (id < root->product->id) {
        return findProduct(root->left, id);
    }
    return findProduct(root->right, id);
}


void displayProducts(BSTNode* root) {
    if (root != NULL) {
        displayProducts(root->left);
   
        printf("  ID: %-3d | Name: %-20s | Price: ₹%.2f | Stock: %-3d | Category: %s\n",
               root->product->id, root->product->name,
               root->product->price, root->product->stock,
               getCategoryName(root->product->category)); 
        displayProducts(root->right);
    }
}

int displayProductsByCategory(BSTNode* root, Category cat) {
    if (root == NULL) {
        return 0;
    }


    int countLeft = displayProductsByCategory(root->left, cat);
    int countRight = displayProductsByCategory(root->right, cat);

    int countCurrent = 0;

    if (root->product->category == cat) {
        printf("  ID: %-3d | Name: %-20s | Price: ₹%.2f | Stock: %d\n",
               root->product->id, root->product->name,
               root->product->price, root->product->stock);
        countCurrent = 1;
    }

  
    return countLeft + countRight + countCurrent;
}


int displaySuggestions(BSTNode* root, Category cat, int currentProdId) {
    if (root == NULL) {
        return 0; 
    }

   
    int countLeft = displaySuggestions(root->left, cat, currentProdId);
    int countRight = displaySuggestions(root->right, cat, currentProdId);

    int countCurrent = 0;

    if (root->product->category == cat && root->product->id != currentProdId) {
        printf("  ID: %-3d | Name: %-20s | Price: ₹%.2f | Stock: %d\n",
               root->product->id, root->product->name,
               root->product->price, root->product->stock);
        countCurrent = 1;
    }
    
  
    return countLeft + countRight + countCurrent;
}