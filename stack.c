#include "stack.h"
#include "bst.h"

void pushHistory(User *user, int productId)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->productId = productId;
    newNode->next = user->historyHead;
    user->historyHead = newNode;
}

void displayHistory(User *user)
{
    if (user->historyHead == NULL)
    {
        printf("  No recently viewed items.\n");
        return;
    }
    printf("  --- Recently Viewed ---\n");
    StackNode *current = user->historyHead;
    while (current != NULL)
    {
      
        BSTNode *node = findProduct(g_productRoot, current->productId);
        if (node)
        {
            printf("  * ID: %d, Name: %s\n", node->product->id, node->product->name);
        }
        current = current->next;
    }
}