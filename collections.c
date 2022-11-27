#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define TO_NODE (LinkedListNode *)
#define TO_DL_NODE (DLinkedListNode *)
#define TO_SET_NODE (SetNode *)
#define TO_SET (SetTable *)
#define TO_DICT_NODE (DictionaryNode *)

typedef union data
{
    uint8_t byte;
    uint16_t bytes_2;
    uint32_t bytes_4;
    uint64_t bytes_8;
} Data;

//--------------- Linked List ---------------------

typedef struct linked_list_node
{
    struct linked_list_node *next;

} LinkedListNode;

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

int linkedList_get_len(LinkedListNode **head)
{
    LinkedListNode *current_node = *head;
    LinkedListNode *last_node = NULL;
    int count = 0;

    while (current_node)
    {
        count++;
        last_node = current_node;
        current_node = current_node->next;
    }

    return count;
}

LinkedListNode *linkedList_append(LinkedListNode **head, LinkedListNode *item)
{
    LinkedListNode *tail = linkedList_get_tail(head);
    if (!tail)
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
    if (!current)
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
// higher level exercise
LinkedListNode *linkedList_reverse(LinkedListNode **head)
{
    LinkedListNode *current = *head;
    LinkedListNode *prev = NULL;
    LinkedListNode *next = NULL;

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

LinkedListInt *linkedListInt_create_new(const int value)
{
    LinkedListInt *new_item = malloc(sizeof(LinkedListInt));
    if (!new_item)
    {
        return NULL;
    }
    new_item->data = value;
    new_item->node = NULL;
    return new_item;
}

// remove item exercise
int linkedListInt_remove_item(LinkedListInt **head, const int item)
{
    LinkedListNode *current = TO_NODE * head;
    LinkedListNode *prev = NULL;
    while (current)
    {
        if (((LinkedListInt *)current)->data == item)
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
    LinkedListNode *current = TO_NODE * head;
    printf("[");
    while (current)
    {
        printf("%d", ((LinkedListInt *)current)->data);
        if (current->next)
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

} DLinkedListNode;

DLinkedListNode *dLinkedList_get_tail(DLinkedListNode **head)
{
    return TO_DL_NODE linkedList_get_tail(TO_NODE head);
}

DLinkedListNode *dLinkedList_append(DLinkedListNode **head, DLinkedListNode *item)
{
    DLinkedListNode *tail = dLinkedList_get_tail(head);
    if (!tail)
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
// node with value
typedef struct d_linked_list_int
{
    DLinkedListNode node;
    int data;

} DLinkedListInt;

DLinkedListInt *dLinkedListInt_create_new(const int value)
{
    DLinkedListInt *new_item = malloc(sizeof(DLinkedListInt));
    if (!new_item)
    {
        return NULL;
    }
    new_item->data = value;
    (TO_DL_NODE new_item)->previous = NULL;
    (TO_DL_NODE new_item)->next = NULL;
    return new_item;
}

// remove item exercise
int dLinkedListInt_remove_item(DLinkedListNode **head, const int item)
{
    DLinkedListNode *current = TO_DL_NODE * head;
    while (current)
    {
        if (((DLinkedListInt *)current)->data == item)
        {
            DLinkedListNode *prev = current->previous;
            prev->next = current->next;
            if (current->next)
            {
                // if current is not the last element we need to set the "previous"
                // pointer in next node to prev
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
    DLinkedListNode *current = TO_NODE * head;
    printf("[");
    while (current)
    {
        printf("%d", ((DLinkedListInt *)current)->data);
        if (current->next)
        {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

// insert before exercise
int dLinkedListInt_insert_before(DLinkedListInt **head, DLinkedListInt *item, const int before_this)
{
    DLinkedListNode *current = TO_DL_NODE * head;
    while (current)
    {
        if (((DLinkedListInt *)current)->data == before_this)
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

// insert after exercise
int dLinkedListInt_insert_after(DLinkedListInt **head, DLinkedListInt *item, const int after_this)
{
    DLinkedListNode *current = TO_DL_NODE * head;
    while (current)
    {
        if (((DLinkedListInt *)current)->data == after_this)
        {
            (TO_DL_NODE item)->next = current->next;
            (TO_DL_NODE item)->previous = current;
            current->next = item;
            if (current->next)
            {
                (TO_DL_NODE item)->next->previous = item;
            }
            return 1;
        }

        current = current->next;
    }

    return 0;
}

int dLinkedList_shuffle(DLinkedListNode **head)
{
    const size_t len = linkedList_get_len(head);
    DLinkedListNode ** nodes = calloc(len, sizeof(DLinkedListNode *));
    if(!nodes)
    {
        return 0;
    }
    for (size_t i = 0; i < len; i++)
    {
        //granted that is len because already calculated, not possible to go off list
        nodes[i] = linkedList_pop(head);
    }
    //now shuffle this array using Fisher&Yates algorithm 
    for (size_t i = 0; i < len-1; i++)
    {
        //clamps the number between i and len
        const size_t new_index = (rand()% (len - i)) + i;
        //swap the two pointers
        DLinkedListNode * temp = nodes[new_index];
        nodes[new_index] = nodes[i];
        nodes[i] = temp;
    }
    //reinsert back the elements in new order
    for (size_t i = 0; i < len; i++)
    {
        dLinkedList_append(head, nodes[i]);
    }
    //free memory used in array
    free(nodes);
    return 1;
}

//------------------- SETS ---------------------

typedef struct set_node
{
    LinkedListNode *next;
    size_t key_len;
    const char *key;

} SetNode;

typedef struct set_table
{
    LinkedListNode **nodes;
    size_t hashmap_size;
    int _collisions;
} SetTable;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

int _rehash(SetTable *table, size_t size_of_element);

SetTable *set_table_new(const size_t hashmap_size)
{
    //2,4 crashes the rehashing
    SetTable *table = malloc(sizeof(SetTable));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(SetNode *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

SetNode *set_insert(SetTable *table, const char *key, const size_t key_len)
{
    //check on collisions and rehash if necessary
    if(table->hashmap_size * 0.75f <= table->_collisions)
    {
        printf("\"%s\" triggered rehashing!\n", key);
        //load factor is hardcoded and arbitrary
        _rehash(table, sizeof(SetNode *));
    }
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % table->hashmap_size;
    LinkedListNode *head = table->nodes[index];
    if (!head)
    {
        table->nodes[index] = malloc(sizeof(SetNode));
        if (!table->nodes[index])
        {
            return NULL;
        }
        (TO_SET_NODE table->nodes[index])->key = key;
        (TO_SET_NODE table->nodes[index])->key_len = key_len;
        table->nodes[index]->next = NULL;

        return table->nodes[index];
    }

    SetNode *new_item = malloc(sizeof(SetNode));
    if (!new_item)
    {
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;

    LinkedListNode *tail = head;

    while ((head))
    {
        if((TO_SET_NODE head)->key == key)//unique keys
        {
            return NULL;
        }
        tail = head;
        head = head->next;
    }
    table->_collisions++;
    tail->next = new_item;
}

SetNode *set_search(SetTable *table, const char *key, const size_t key_len)
{
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % table->hashmap_size;
    LinkedListNode *head = table->nodes[index];

    if (!head)
    {
        // no element with this hash
        return NULL;
    }

    while (head)
    {
        // check collision list
        if ((TO_SET_NODE head)->key == key)
        {
            return head;
        }
        head = head->next;
    }

    // key not found
    return NULL;
}

int set_remove_key(SetTable *table, const char *key, const size_t key_len)
{
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % table->hashmap_size;
    LinkedListNode *head = table->nodes[index];
    if (!head)
    {
        // no elements with this hash
        return 0;
    }
    if((TO_SET_NODE head)->key == key)
    {
        if(head->next)
        {
            table->_collisions--;
        }
        //first element in list
        head = head->next;
        free(table->nodes[index]);
        table->nodes[index] = head;
        return 1;
    }
    LinkedListNode *prev = table->nodes[index];
    while (head)
    {   
        if((TO_SET_NODE head)->key == key)
        {
            table->_collisions--;
            prev->next = head->next;
            free(head);
            return 1;
        }
        prev = head;
        head = head->next;
    }
    
    // key not found in collision list
    return 0;
}

int _rehash(SetTable *table, const size_t size_of_element)
{
    SetTable * new = realloc(table, (table->hashmap_size*2)*size_of_element);
    if(!new)
    {
        return 0;
    }
    *table = *new;
    table->_collisions = 0;
    //clear collisions counter
    for (size_t i = 0; i < table->hashmap_size; i++)
    {
        while (table->nodes[i])
        {
            //pop from list using list function
            LinkedListNode *current = linkedList_pop(table->nodes[i]);
            if(!current)
            {
                return 0;
            }
            //calculate new hash
            const size_t hash = djb33x_hash((TO_SET_NODE table->nodes[i])->key, (TO_SET_NODE table->nodes[i])->key_len);
            const size_t index = hash % table->hashmap_size;
            //set to the new list position
            if(!table->nodes[index])
            {
                //first element (hopefully!)
                *table->nodes[index] = *current;
                return 1;
            }
            LinkedListNode *head = table->nodes[index];
            LinkedListNode *tail = NULL;
            while ((head))
            {
                tail = head;
                head = head->next;
            }
            //track new collisions
            table->_collisions++;
            tail->next = current;
            return 1;
        }
    }
}

//-------------- DICTIONARY -----------------

typedef struct dic_node
{
    SetNode node;
    Data data;
    
}DictionaryNode;

typedef struct dic
{
    SetTable table;
}Dictionary;


Dictionary *dictionary_new(const size_t hashmap_size)
{
    Dictionary *table = malloc(sizeof(Dictionary));
    if (!table)
    {
        return NULL;
    }
    (TO_SET table)->hashmap_size = hashmap_size;
    (TO_SET table)->nodes = calloc((TO_SET table)->hashmap_size, sizeof(DictionaryNode *));
    (TO_SET table)->_collisions = 0;
    if (!(TO_SET table)->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

DictionaryNode *dictionary_insert(Dictionary *table, const char *key, const size_t key_len, const Data data)
{
    if((TO_SET table)->hashmap_size * 0.75f <=(TO_SET table)->_collisions)
    {
        printf("\"%s\" triggered rehashing!\n", key);
        //load factor is hardcoded and arbitrary
        _rehash(table, sizeof(DictionaryNode *));
    }
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (TO_SET table)->hashmap_size;
    LinkedListNode *head = (TO_SET table)->nodes[index];
    if (!head)
    {
        (TO_SET table)->nodes[index] = malloc(sizeof(DictionaryNode));
        if (!(TO_SET table)->nodes[index])
        {
            return NULL;
        }
        (TO_SET_NODE (TO_SET table)->nodes[index])->key = key;
        (TO_SET_NODE (TO_SET table)->nodes[index])->key_len = key_len;
        (TO_DICT_NODE (TO_SET table)->nodes[index])->data = data;
        (TO_SET table)->nodes[index]->next = NULL;

        return (TO_SET table)->nodes[index];
    }

    DictionaryNode *new_item = malloc(sizeof(DictionaryNode));
    if (!new_item)
    {
        return NULL;
    }

    (TO_SET_NODE new_item)->key = key;
    (TO_SET_NODE new_item)->key_len = key_len;
    new_item->data = data;
    (TO_NODE new_item)->next = NULL;

    LinkedListNode *tail = head;

    while ((head))
    {
        if((TO_SET_NODE head)->key == key)//unique keys
        {
            return NULL;
        }
        tail = head;
        head = head->next;
    }

    tail->next = new_item;
    (TO_SET table)->_collisions++;
}

DictionaryNode *dictionary_search(Dictionary *table, const char *key, const size_t key_len)
{
    return TO_DICT_NODE set_search(table, key, key_len);
}

int dictionary_remove_key(Dictionary *table, const char *key, const size_t key_len)
{
    return set_remove_key(table, key, key_len);
}