#include "structs.h"
#include "bst.h"
#include "linked_list.h"
#include "stack.h"
#include "queue.h"

// --- Global Data Definitions ---
BSTNode* g_productRoot = NULL;
User* g_userListHead = NULL;
Queue* g_orderQueue = NULL;
int g_nextUserId = 2; // Start from 2, since 1 (alice) exists

// --- Helper Functions ---
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clear buffer
    getchar(); // Wait for Enter
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


// --- Initialization ---
void initializeData() {
    // Initialize Product BST - UPDATED with categories and ranges
    
    // --- MOBILES ---
    g_productRoot = insertProduct(g_productRoot, createProduct(101, "iPhone 17", 1499.00, 10, CAT_MOBILES, RANGE_HIGH));
    g_productRoot = insertProduct(g_productRoot, createProduct(102, "Samsung S24 Ultra", 1399.00, 15, CAT_MOBILES, RANGE_HIGH));
    g_productRoot = insertProduct(g_productRoot, createProduct(103, "iPhone 16 Pro", 1199.00, 20, CAT_MOBILES, RANGE_HIGH));
    
    g_productRoot = insertProduct(g_productRoot, createProduct(111, "Moto G64", 299.00, 30, CAT_MOBILES, RANGE_MID));
    g_productRoot = insertProduct(g_productRoot, createProduct(112, "Nothing Phone 2a", 349.00, 25, CAT_MOBILES, RANGE_MID));
    g_productRoot = insertProduct(g_productRoot, createProduct(113, "Nothing Phone 3a", 449.00, 20, CAT_MOBILES, RANGE_MID));
 
    g_productRoot = insertProduct(g_productRoot, createProduct(121, "Samsung A16 5G", 149.00, 50, CAT_MOBILES, RANGE_LOW));
    g_productRoot = insertProduct(g_productRoot, createProduct(122, "Moto G Power 5G", 129.00, 40, CAT_MOBILES, RANGE_LOW));
    g_productRoot = insertProduct(g_productRoot, createProduct(123, "POCO C71", 99.00, 60, CAT_MOBILES, RANGE_LOW));

    // --- LAPTOPS ---
    g_productRoot = insertProduct(g_productRoot, createProduct(201, "MacBook Pro 16", 2499.00, 10, CAT_LAPTOPS, RANGE_HIGH));
    g_productRoot = insertProduct(g_productRoot, createProduct(202, "Dell XPS 15", 2199.00, 12, CAT_LAPTOPS, RANGE_HIGH));
    g_productRoot = insertProduct(g_productRoot,createProduct(203,"LENOVO LEGION",10000,50,CAT_LAPTOPS,RANGE_HIGH));

    g_productRoot = insertProduct(g_productRoot,createProduct(204,"DELL INSPIRON 15",800,10,CAT_LAPTOPS, RANGE_MID));
    g_productRoot = insertProduct(g_productRoot, createProduct(205, "MacBook Air 13", 999.00, 20, CAT_LAPTOPS, RANGE_MID));
    g_productRoot = insertProduct(g_productRoot, createProduct(206,"LENOVO LOQ",850,20,CAT_LAPTOPS,RANGE_MID));

    g_productRoot=insertProduct(g_productRoot,createProduct(207,"HP 15S",399.00,30,CAT_LAPTOPS,RANGE_LOW));
    g_productRoot = insertProduct(g_productRoot,createProduct(208,"ASUS VIVOBOOK",450,30,CAT_LAPTOPS,RANGE_LOW));
    g_productRoot = insertProduct(g_productRoot, createProduct(221, "Lenovo IdeaPad", 499.00, 30, CAT_LAPTOPS, RANGE_LOW));

    // --- WATCHES ---
    g_productRoot = insertProduct(g_productRoot, createProduct(301, "Apple Watch Ultra", 799.00, 15, CAT_WATCHES, RANGE_HIGH));
    g_productRoot = insertProduct(g_productRoot,createProduct(302,"ROLEX",900.00,19,CAT_WATCHES,RANGE_HIGH));

    g_productRoot = insertProduct(g_productRoot,createProduct(303,"OLEVS",249.00,30,CAT_WATCHES,RANGE_MID));
    g_productRoot = insertProduct(g_productRoot, createProduct(311, "Samsung Galaxy Watch", 299.00, 25, CAT_WATCHES, RANGE_MID));

    g_productRoot= insertProduct(g_productRoot,createProduct(305,"TITAN",199.00,50,CAT_WATCHES,RANGE_LOW));
    g_productRoot = insertProduct(g_productRoot, createProduct(321, "Fitbit Charge 6", 159.00, 40, CAT_WATCHES, RANGE_LOW));

    // --- PENS ---
    g_productRoot = insertProduct(g_productRoot, createProduct(401, "Montblanc Pen", 450.00, 20, CAT_PENS, RANGE_HIGH));
    g_productRoot = insertProduct(g_productRoot,createProduct(402,"PILOT FOUNTAIN PEN",300.00,30,CAT_PENS,RANGE_HIGH));

    g_productRoot=insertProduct(g_productRoot,createProduct(403,"T-MAX",39.00,40,CAT_PENS,RANGE_MID));
    g_productRoot = insertProduct(g_productRoot, createProduct(411, "Lamy Safari Pen", 29.00, 50, CAT_PENS, RANGE_MID));

    g_productRoot= insertProduct(g_productRoot,createProduct(405,"PENTONIC",2.00,200,CAT_PENS,RANGE_LOW));
    g_productRoot = insertProduct(g_productRoot, createProduct(421, "Bic Crystal (10pk)", 5.00, 100, CAT_PENS, RANGE_LOW));

    // --- CLOTHES ---
    g_productRoot = insertProduct(g_productRoot, createProduct(501, "Designer Jacket", 800.00, 10, CAT_CLOTHES, RANGE_HIGH));
    g_productRoot = insertProduct(g_productRoot,createProduct(502,"ADIDAS SPORTS WEAR",900.00,10,CAT_CLOTHES,RANGE_HIGH));

    g_productRoot = insertProduct(g_productRoot,createProduct(503,"VERO MODA",79.00,30, CAT_CLOTHES, RANGE_MID));
    g_productRoot = insertProduct(g_productRoot, createProduct(504, "Levi's Jeans", 69.00, 40, CAT_CLOTHES, RANGE_MID));
    
    g_productRoot= insertProduct(g_productRoot,createProduct(505,"BASIC JEANS",10,100,CAT_CLOTHES,RANGE_LOW));
    g_productRoot = insertProduct(g_productRoot, createProduct(521, "Basic T-Shirt", 15.00, 80, CAT_CLOTHES, RANGE_LOW));

    // --- EARPHONES ---
    g_productRoot = insertProduct(g_productRoot, createProduct(601, "AirPods Max", 549.00, 15, CAT_EARPHONES, RANGE_HIGH));
    g_productRoot = insertProduct(g_productRoot,createProduct(602,"SONY WH SERIES",600,10,CAT_EARPHONES,RANGE_HIGH));

    g_productRoot= insertProduct(g_productRoot,createProduct(603,"BOAT",239.00,20,CAT_EARPHONES,RANGE_MID));
    g_productRoot = insertProduct(g_productRoot, createProduct(611, "AirPods Pro", 249.00, 30, CAT_EARPHONES, RANGE_MID));

    g_productRoot= insertProduct(g_productRoot,createProduct(605,"BOLD",55.00,10,CAT_EARPHONES,RANGE_LOW));
    g_productRoot = insertProduct(g_productRoot, createProduct(621, "JBL Tune Buds", 49.00, 50, CAT_EARPHONES, RANGE_LOW));

   
    addUser(&g_userListHead, createUser(1, "user_alice", "alice_pass"));
    
    User* alice = findUserByUsername(g_userListHead, "user_alice");
    if (alice) {
         strncpy(alice->address, "123 Tech Road, Bangalore", 199);
    }
    
    g_orderQueue = createQueue();
}

// --- User Menu ---
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

        // Handle admin-only choices
        if (user->id == 1) {
            if (choice == 8) {
                // --- PROCESS ORDER ---
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
                // --- VIEW PENDING ORDERS ---
                displayQueue(g_orderQueue);
                pressEnterToContinue();
                continue; 
            }
        }


        // Handle standard user choices
        switch (choice) {
            case 1: // --- BROWSE BY CATEGORY (UPDATED) ---
                {
                    printf("\n--- Browse by Category ---\n");
                    printf("1. %s\n", getCategoryName(CAT_MOBILES));
                    printf("2. %s\n", getCategoryName(CAT_LAPTOPS));
                    printf("3. %s\n", getCategoryName(CAT_WATCHES));
                    printf("4. %s\n", getCategoryName(CAT_PENS));
                    printf("5. %s\n", getCategoryName(CAT_CLOTHES));
                    printf("6. %s\n", getCategoryName(CAT_EARPHONES));
                    printf("Enter category choice: ");
                    
                    int catChoice = getIntInput();
                    Category selectedCat;
                    
                    switch (catChoice) {
                        case 1: selectedCat = CAT_MOBILES; break;
                        case 2: selectedCat = CAT_LAPTOPS; break;
                        case 3: selectedCat = CAT_WATCHES; break;
                        case 4: selectedCat = CAT_PENS; break;
                        case 5: selectedCat = CAT_CLOTHES; break;
                        case 6: selectedCat = CAT_EARPHONES; break;
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
            case 2: // --- ADD TO CART (UPDATED) ---
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
                            
                            // --- UPDATED SUGGESTION LOGIC ---
                            printf("\n--- Similar Items You Might Like ---\n");
                            // Pass the category AND the hidden range to the suggestion function
                            int suggestionsFound = displaySuggestions(g_productRoot, 
                                                                    node->product->category, 
                                                                    node->product->range, 
                                                                    node->product->id);
                            if (suggestionsFound == 0) {
                                printf("No other similar items found.\n");
                            }
                            // --- END OF UPDATED LOGIC ---

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
            case 3: // View Cart
                displayCart(user);
                pressEnterToContinue();
                break;
            case 4: // View History
                displayHistory(user);
                pressEnterToContinue();
                break;
            case 5: // --- CHECKOUT (SIMPLIFIED) ---
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
            case 6: // --- SET ADDRESS ---
                {
                    printf("--- Update Address ---\n");
                    printf("Current Address: %s\n", user->address[0] == '\0' ? "[Not Set]" : user->address);
                    printf("Enter new full address : \n");
                    getStringInput(user->address, 200);
                    printf("Address updated successfully!\n");
                    pressEnterToContinue();
                }
                break;
            case 7: // --- VIEW ALL PRODUCTS ---
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


// --- Main Function ---
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

        if (choice == 1) { // --- LOGIN ---
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

        } else if (choice == 2) { // --- SIGN UP ---
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

    // ... cleanup would go here ...
    return 0;
}