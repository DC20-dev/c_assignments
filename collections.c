#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define TO_NODE (LinkedListNode*)
#define TO_DL_NODE (DLinkedListNode*)
#define TO_SET

//--------------- Linked List ---------------------

typedef struct linked_list_node
{
    struct linked_list_node *next;

}LinkedListNode;

LinkedListNode *linkedList_get_tail(LinkedListNode **head)
{
    LinkedListNode *current_node = *head;
    LinkedListNode *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}

LinkedListNode *linkedList_append(LinkedListNode **head, LinkedListNode *item)
{
    LinkedListNode *tail = linkedList_get_tail(head);
    if(!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }

    item->next = NULL;
    return item;
}

LinkedListNode *linkedList_pop(LinkedListNode **head)
{
    LinkedListNode *current = *head;
    if(!current)
    {
        return NULL;
    }
    *head = (*head)->next;
    current->next = NULL;

    return current;
}

LinkedListNode *linkedList_dequeue(LinkedListNode **head)
{
    LinkedListNode *current_node = *head;
    LinkedListNode *last_node = NULL;

    while (current_node->next)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    last_node->next = NULL;
    return current_node;
}
//higher level exercise
LinkedListNode* linkedList_reverse(LinkedListNode **head)
{
    LinkedListNode* current = *head;
    LinkedListNode* prev = NULL;
    LinkedListNode* next = NULL;

    while (current)
    {
        next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    }
    return prev;
}

// node with value
typedef struct linked_list_int
{
    LinkedListNode *node;
    int data;

} LinkedListInt;

LinkedListInt *linkedListInt_create_new(int value)
{
    LinkedListInt* new_item = malloc(sizeof(LinkedListInt));
    if(!new_item)
    {
        return NULL;
    }
    new_item->data = value;
    new_item->node = NULL;
    return new_item;
}

// remove item exercise
int linkedListInt_remove_item(LinkedListInt **head, int item)
{
    LinkedListNode *current = TO_NODE *head;
    LinkedListNode *prev = NULL;
    while (current)
    {
        if(((LinkedListInt*)current)->data == item)
        {
            prev->next = current->next;
            free(current);
            return 1;
        }

        prev = current;
        current = current->next;
    }
    
    return 0;
}

void linkedListInt_print(LinkedListInt **head)
{
    LinkedListNode *current = TO_NODE *head;
    printf("[");
    while (current)
    {
       printf("%d", ((LinkedListInt*)current)->data);
       if(current->next)
       {
        printf(", ");
       }
       current = current->next;
    }
    printf("]\n");
}

//-------------- Doubly Linked List --------------------

typedef struct d_linked_list_node
{
    struct d_linked_list_node *next;
    struct d_linked_list_node *previous;
    
}DLinkedListNode;

DLinkedListNode *dLinkedList_get_tail(DLinkedListNode **head)
{
    return TO_DL_NODE linkedList_get_tail(TO_NODE head);
}

DLinkedListNode *dLinkedList_append(DLinkedListNode **head, DLinkedListNode *item)
{
    DLinkedListNode *tail = dLinkedList_get_tail(head);
    if(!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->previous = tail;
    item->next = NULL;
    
    return item;
}
//node with value
typedef struct d_linked_list_int
{
    DLinkedListNode node;
    int data;

}DLinkedListInt;

DLinkedListInt *dLinkedListInt_create_new(int value)
{
    DLinkedListInt* new_item = malloc(sizeof(DLinkedListInt));
    if(!new_item)
    {
        return NULL;
    }
    new_item->data = value;
    (TO_DL_NODE new_item)->previous = NULL;
    (TO_DL_NODE new_item)->next = NULL;
    return new_item;
}

// remove item exercise
int dLinkedListInt_remove_item(DLinkedListNode **head, int item)
{
    DLinkedListNode *current = TO_DL_NODE *head;
    while (current)
    {
        if(((DLinkedListInt*)current)->data == item)
        {
            DLinkedListNode *prev = current->previous;
            prev->next = current->next;
            if(current->next)
            {
                //if current is not the last element we need to set the "previous"
                //pointer in next node to prev
                current->next->previous = prev;
            }
            free(current);
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

void dLinkedListInt_print(DLinkedListInt **head)
{
    DLinkedListNode *current = TO_NODE *head;
    printf("[");
    while (current)
    {
       printf("%d", ((DLinkedListInt*)current)->data);
       if(current->next)
       {
        printf(", ");
       }
       current = current->next;
    }
    printf("]\n");
}

//insert before exercise
int dLinkedListInt_insert_before(DLinkedListInt **head, DLinkedListInt *item, int before_this)
{
    DLinkedListNode *current = TO_DL_NODE *head;
    while (current)
    {
        if(((DLinkedListInt*)current)->data == before_this)
        {
            DLinkedListNode *prev = current->previous;
            prev->next = item;
            (TO_DL_NODE item)->previous = prev;
            (TO_DL_NODE item)->next = current;
            current->previous = item;
            return 1;
        }

        current = current->next;
    }
    
    return 0;
}

//insert after exercise
int dLinkedListInt_insert_after(DLinkedListInt **head, DLinkedListInt *item, int after_this)
{
    DLinkedListNode *current = TO_DL_NODE *head;
    while (current)
    {
        if(((DLinkedListInt*)current)->data == after_this)
        {
            (TO_DL_NODE item)->next = current->next;
            (TO_DL_NODE item)->previous = current;
            current->next = item;
            if(current->next)
            {
                (TO_DL_NODE item)->next->previous = item;
            }
            return 1;
        }

        current = current->next;
    }
    
    return 0;
}
//TODO
void dLinkedListInt_shuffle(DLinkedListInt **head)
{}

//------------------- SETS ---------------------

typedef struct set_node
{
    struct set_node *next;
    const char *key;
    size_t key_len;

}SetNode;

typedef struct set_table
{
    SetNode **nodes;
    size_t hashmap_size;

}SetTable;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

SetTable *set_table_new(const size_t hashmap_size)
{
    SetTable *table = malloc(sizeof(SetTable));
    if(!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(SetNode*));
    if(!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

SetNode *set_insert(SetTable *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    SetNode *head = table->nodes[index];
    if(!head)
    {
        table->nodes[index] = malloc(sizeof(SetNode));
        if(!table->nodes[index])
        {
            return NULL;
        }
        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->next = NULL;

        return table->nodes[index];
    }

    SetNode *new_item = malloc(sizeof(SetNode));
    if(!new_item)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;

    SetNode *tail = head;

    while ((head))
    {
        tail = head;
        head = head->next;
    }

    tail->next = new_item;
}