#include "ecommerce.h"



User* createUser(int id, const char* username, const char* password) {
    User* newUser = (User*)malloc(sizeof(User));
    newUser->id = id;
    strncpy(newUser->username, username, 49);
    newUser->username[49] = '\0';
    strncpy(newUser->password, password, 49);
    newUser->password[49] = '\0';
    newUser->address[0] = '\0'; 
    newUser->cartHead = NULL;
    newUser->historyHead = NULL;
    newUser->next = NULL;
    return newUser;
}


void addUser(User** head, User* user) {
    user->next = *head;
    *head = user;
}


User* findUserByUsername(User* head, const char* username) {
    User* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}



void addToCart(User* user, Product* product, int quantity) {
   
    CartItem* current = user->cartHead;
    while (current != NULL) {
        if (current->product->id == product->id) {
            current->quantity += quantity;
            printf("  Updated quantity for %s in cart.\n", product->name);
            return;
        }
        current = current->next;
    }

 
    CartItem* newItem = (CartItem*)malloc(sizeof(CartItem));
    newItem->product = product;
    newItem->quantity = quantity;
    newItem->next = user->cartHead;
    user->cartHead = newItem;
    printf("  Added %s to cart.\n", product->name);
}

void displayCart(User* user) {
    if (user->cartHead == NULL) {
        printf("  Your cart is empty.\n");
        return;
    }
    printf("  --- %s's Cart ---\n", user->username);
    CartItem* current = user->cartHead;
    double total = 0;
    while (current != NULL) {
        printf("  * %s (%d) - $%.2f each\n",
               current->product->name, current->quantity, current->product->price);
        total += current->product->price * current->quantity;
        current = current->next;
    }
    printf("  ------------------------\n");
    printf("  Total: $%.2f\n", total);
}


CartItem* clearCart(CartItem* head) {
    CartItem* current = head;
    while (current != NULL) {
        CartItem* temp = current;
        current = current->next;
        free(temp);
    }
    return NULL;
}


void pushHistory(User* user, int productId) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->productId = productId;
    newNode->next = user->historyHead;
    user->historyHead = newNode;
}


void displayHistory(User* user) {
    if (user->historyHead == NULL) {
        printf("  No recently viewed items.\n");
        return;
    }
    printf("  --- Recently Viewed ---\n");
    StackNode* current = user->historyHead;
    while (current != NULL) {
      
        BSTNode* node = findProduct(g_productRoot, current->productId);
        if (node) {
            printf("  * ID: %d, Name: %s\n", node->product->id, node->product->name);
        }
        current = current->next;
    }
}