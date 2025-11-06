#include "structs.h"
#include "bst.h"
#include "linked_list.h"
#include "stack.h"
#include "queue.h"


BSTNode* g_productRoot = NULL;
User* g_userListHead = NULL;
Queue* g_orderQueue = NULL;
int g_nextUserId = 2; 


void clearScreen() {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); 
    getchar(); 
}

int getIntInput() {
    int value;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%d", &value) == 1) {
            return value;
        }
    }
    return -1; 
}


void getStringInput(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
    }
}



void initializeData() {    
    g_productRoot = insertProduct(g_productRoot, createProduct(101, "Laptop", 120000.00, 10, CAT_ELECTRONICS));
    g_productRoot = insertProduct(g_productRoot, createProduct(102, "Mouse", 450.50, 50, CAT_ELECTRONICS));
    g_productRoot = insertProduct(g_productRoot, createProduct(103, "Keyboard", 1500.00, 25, CAT_ELECTRONICS));
    g_productRoot = insertProduct(g_productRoot, createProduct(104,  "USB Hub", 220.00, 100, CAT_ELECTRONICS));
    g_productRoot = insertProduct(g_productRoot, createProduct(105, "Monitor", 30000.00, 15, CAT_ELECTRONICS));

    g_productRoot = insertProduct(g_productRoot, createProduct(200,"CRICKET BATS",30000.00,50,CAT_SPORTS));
    g_productRoot = insertProduct(g_productRoot, createProduct(201, "Football", 250.00, 30, CAT_SPORTS));
    g_productRoot = insertProduct(g_productRoot, createProduct(202, "Basketball", 3000.00, 20, CAT_SPORTS));
    g_productRoot = insertProduct(g_productRoot, createProduct(203, "SQUASH BALL",200.00,30,CAT_SPORTS));
    g_productRoot = insertProduct(g_productRoot, createProduct(204, "BADMINTON RACQUETS",2000.00,50,CAT_SPORTS));

    g_productRoot = insertProduct(g_productRoot, createProduct(501, "C Programming", 555.00, 40, CAT_BOOKS));
    g_productRoot = insertProduct(g_productRoot, createProduct(502, "Data Structures", 650.00, 30, CAT_BOOKS));
    g_productRoot = insertProduct(g_productRoot, createProduct(503, "5 WAYS",5000.00,50,CAT_BOOKS));
    g_productRoot = insertProduct(g_productRoot, createProduct(504, "HISTORY OF RCB",50.00,90,CAT_BOOKS));
    g_productRoot= insertProduct(g_productRoot,createProduct(505,"HAKAI",500.50,90,CAT_BOOKS));

    g_productRoot = insertProduct(g_productRoot, createProduct(601, "TITAN", 180.00, 25, CAT_WATCHES));
    g_productRoot = insertProduct(g_productRoot, createProduct(602, "OLEVS", 250.00, 15, CAT_WATCHES));
    g_productRoot = insertProduct(g_productRoot,createProduct(603,"G-SHOCK",5000000.00,60,CAT_WATCHES));
    g_productRoot= insertProduct(g_productRoot,createProduct(604,"ROLEX",60000,90,CAT_WATCHES));
    g_productRoot=insertProduct(g_productRoot,createProduct(605,"OMEGA",8000,60,CAT_WATCHES));

    g_productRoot = insertProduct(g_productRoot, createProduct(701, "CALVIN KLEIN-JEANS", 450.00, 5, CAT_FASHION));
    g_productRoot = insertProduct(g_productRoot, createProduct(702, "KILLER-TSHIRT", 550.00, 3, CAT_FASHION));
    g_productRoot = insertProduct(g_productRoot,createProduct(703,"LOUIS PHILLIPE-FORMALS",1000.00,6, CAT_FASHION));
    g_productRoot = insertProduct(g_productRoot,createProduct(704,"PUMA-SPORTS WEAR",1000.00,60,CAT_FASHION));
    g_productRoot = insertProduct(g_productRoot,createProduct(705,"COLUMBIA-WINTER WEAR",1000.00,60,CAT_FASHION));

    g_productRoot=insertProduct(g_productRoot,createProduct(801,"LAMP",500,50,CAT_HOME_DECOR));
    g_productRoot=insertProduct(g_productRoot,createProduct(802,"CHANDELIER",200.00,90,CAT_HOME_DECOR));
    g_productRoot=insertProduct(g_productRoot,createProduct(803,"VASE",300.00,20,CAT_HOME_DECOR));
    g_productRoot=insertProduct(g_productRoot,createProduct(804,"WALL STICKERS",100.00,50,CAT_HOME_DECOR));
    g_productRoot=insertProduct(g_productRoot,createProduct(805,"PHOTO FRAMES",30.00,60,CAT_HOME_DECOR));


    addUser(&g_userListHead, createUser(1, "user_alice", "alice_pass")); 
    

    User* alice = findUserByUsername(g_userListHead, "user_alice");
    if (alice) {
         strncpy(alice->address, "123 Tech Road, Bangalore", 199);
    }
    

    g_orderQueue = createQueue();

}


void userMenu(User* user) {
    int choice = -1;
    while (choice != 0) {
        clearScreen();
        printf("--- Welcome, %s ---\n", user->username);
        printf("My Address: %s\n", user->address[0] == '\0' ? "[Not Set]" : user->address);
        printf("----------------------------------\n");
        printf("1. Browse by Category\n");
        printf("2. Add Item to Cart\n");
        printf("3. View Cart\n");
        printf("4. View Recently Viewed\n");
        printf("5. Checkout\n");
        printf("6. Set/Update My Address\n"); 
        printf("7. View All Products\n"); 
        
        
        if (user->id == 1) { 
            printf("----------------------------------\n");
            printf("8. Process Next Order (Admin)\n");
            printf("9. View Pending Orders (Admin)\n");
        }
        printf("0. Logout\n");
        printf("Enter choice: ");
        choice = getIntInput();

     
        if (user->id == 1) {
            if (choice == 8) {
                Order* processedOrder = dequeue(g_orderQueue);
                if (processedOrder) {
                    printf("\nProcessing order for User ID %d...\n", processedOrder->userId);
                    printf("Total Value: $%.2f\n", processedOrder->totalValue);
                    printf("Final Address: %s\n", processedOrder->deliveryAddress); 
                    printf("Items:\n");
                    CartItem* item = processedOrder->itemsHead;
                    while(item) {
                        printf("  - %s (Qty: %d)\n", item->product->name, item->quantity);
                        item = item->next;
                    }
                    clearCart(processedOrder->itemsHead);
                    free(processedOrder);
                    printf("Order processed and removed from queue.\n");
                } else {
                    printf("\nNo orders to process.\n");
                }
                pressEnterToContinue();
                continue;
            } else if (choice == 9) {
              
                displayQueue(g_orderQueue);
                pressEnterToContinue();
                continue; 
            }
        }


   
        switch (choice) {
            case 1: 
                {
                    printf("\n--- Browse by Category ---\n");
                    printf("1. %s\n", getCategoryName(CAT_ELECTRONICS));
                    printf("2. %s\n", getCategoryName(CAT_SPORTS));
                    printf("3. %s\n", getCategoryName(CAT_BOOKS));
                    printf("4. %s\n", getCategoryName(CAT_WATCHES));
                    printf("5. %s\n", getCategoryName(CAT_FASHION));
                    printf("6. %s\n", getCategoryName(CAT_HOME_DECOR));
                    printf("Enter category choice: ");
                    
                    int catChoice = getIntInput();
                    Category selectedCat;
                    
                    switch (catChoice) {
                        case 1: selectedCat = CAT_ELECTRONICS; break;
                        case 2: selectedCat = CAT_SPORTS; break;
                        case 3: selectedCat = CAT_BOOKS; break;
                        case 4: selectedCat = CAT_WATCHES; break;
                        case 5: selectedCat = CAT_FASHION; break;
                        case 6: selectedCat = CAT_HOME_DECOR; break;
                        default:
                            printf("Invalid category.\n");
                            pressEnterToContinue();
                            continue; 
                    }

                    printf("\n--- Showing products in %s ---\n", getCategoryName(selectedCat));
                    int foundCount = displayProductsByCategory(g_productRoot, selectedCat);
                    if (foundCount == 0) {
                        printf("No products found in this category.\n");
                    }
                    pressEnterToContinue();
                }
                break;
            case 2: 
                {
                    printf("Enter Product ID to add: ");
                    int prodId = getIntInput();
                    BSTNode* node = findProduct(g_productRoot, prodId);
                    if (node) {
                        printf("Enter quantity: ");
                        int qty = getIntInput();
                        if (qty > 0 && qty <= node->product->stock) {
                            addToCart(user, node->product, qty);
                        
                            pushHistory(user, node->product->id);
                            
                            
                            printf("\n--- You might also like in %s ---\n", getCategoryName(node->product->category));
                            int suggestionsFound = displaySuggestions(g_productRoot, node->product->category, node->product->id);
                            if (suggestionsFound == 0) {
                                printf("No other items found in this category.\n");
                            }
                           

                        } else if (qty > node->product->stock) {
                            printf("Not enough stock! Available: %d\n", node->product->stock);
                        } else {
                            printf("Invalid quantity.\n");
                        }
                    } else {
                        printf("Product ID not found.\n");
                    }
                    pressEnterToContinue();
                }
                break;
            case 3: 
                displayCart(user);
                pressEnterToContinue();
                break;
            case 4: 
                displayHistory(user);
                pressEnterToContinue();
                break;
            case 5: 
                {
                    if (user->cartHead == NULL) {
                        printf("Your cart is empty. Nothing to check out.\n");
                    } else if (user->address[0] == '\0') {
                       
                        printf("You must set your address (Option 6) before checking out.\n");
                    } else {
                       
                        printf("Your items will be delivered to:\n%s\n", user->address);
                        printf("Confirm checkout? (1=Yes, 0=No): ");
                        int confirm = getIntInput();

                        if (confirm == 1) {
                            
                            Order* newOrder = (Order*)malloc(sizeof(Order));
                            newOrder->userId = user->id;
                            newOrder->itemsHead = copyCart(user->cartHead); 
                           
                            strncpy(newOrder->deliveryAddress, user->address, 199);
                            newOrder->deliveryAddress[199] = '\0';
                            
                            double total = 0;
                            CartItem* current = newOrder->itemsHead;
                            while (current) {
                                total += current->product->price * current->quantity;
                                current = current->next;
                            }
                            newOrder->totalValue = total;

                           
                            enqueue(g_orderQueue, newOrder);
                            
                          
                            user->cartHead = clearCart(user->cartHead);
                            
                            printf("\nCheckout successful! Your items will be delivered soon.\n");
                        } else {
                            printf("Checkout cancelled.\n");
                        }
                    }
                    pressEnterToContinue();
                }
                break;
            case 6: 
                {
                    printf("--- Update Address ---\n");
                    printf("Current Address: %s\n", user->address[0] == '\0' ? "[Not Set]" : user->address);
                    printf("Enter new full address (e.g., 123 Main St, City, State, ZIP): \n");
                    getStringInput(user->address, 200);
                    printf("Address updated successfully!\n");
                    pressEnterToContinue();
                }
                break;
            case 7: 
                {
                    printf("\n--- Product Catalog (All) ---\n");
                    displayProducts(g_productRoot);
                    pressEnterToContinue();
                }
                break;
            case 0:
                printf("Logging out...\n");
                break;
            default:
               
                if (choice == 8 || choice == 9) {
                     printf("That is an admin-only option.\n");
                } else {
                     printf("Invalid choice.\n");
                }
                pressEnterToContinue();
                break;
        }
    }
}



int main() {
    initializeData();
    
    int choice = -1;
    while (choice != 0) {
        clearScreen();
        printf("====== C Mini E-Commerce ======\n");
        printf("1. Login\n");
        printf("2. Sign Up\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        choice = getIntInput();

        if (choice == 1) { 
            char username[50];
            char password[50];
            printf("Enter username: ");
            getStringInput(username, 50);
            printf("Enter password: ");
            getStringInput(password, 50);

            User* user = findUserByUsername(g_userListHead, username);
            
            if (user == NULL) {
                printf("User not found.\n");
            } else if (strcmp(user->password, password) != 0) {
                printf("Invalid password.\n");
            } else {
                printf("Login successful! Welcome, %s.\n", user->username);
                pressEnterToContinue();
                
                userMenu(user);
            }
            if (user == NULL || strcmp(user->password, password) != 0) {
                 pressEnterToContinue();
            }

        } else if (choice == 2) { 
            char username[50];
            char password[50];
            char address[200]; 
            
            printf("--- New User Registration ---\n");
            printf("Enter new username: ");
            getStringInput(username, 50);
            
           
            if (findUserByUsername(g_userListHead, username) != NULL) {
                printf("Username already taken. Please try another.\n");
            } else {
                printf("Enter new password: ");
                getStringInput(password, 50);
                
               
                User* newUser = createUser(g_nextUserId, username, password);
                
            
                printf("Enter your full delivery address: ");
                getStringInput(address, 200);
                strncpy(newUser->address, address, 199); 
                newUser->address[199] = '\0';
                
              
                addUser(&g_userListHead, newUser);
                g_nextUserId++; 
                
                printf("Registration successful! You can now log in as '%s'.\n", username);
            }
            pressEnterToContinue();

        } else if (choice == 0) {
             printf("Exiting. Goodbye!\n");
        } else {
            printf("Invalid choice.\n");
            pressEnterToContinue();
        }
    }


    return 0;
}