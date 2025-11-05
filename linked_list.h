#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "structs.h"


User* createUser(int id, const char* username, const char* password); 
void addUser(User** head, User* user);
User* findUser(User* head, int id);
User* findUserByUsername(User* head, const char* username); 


void addToCart(User* user, Product* product, int quantity);
void displayCart(User* user);
CartItem* clearCart(CartItem* head); 

#endif
