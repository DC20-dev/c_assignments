#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "collections.h"

//--------------- LINKED LIST ---------------------

linked_list_node_t *linked_list_get_tail(linked_list_node_t **head)
{
    linked_list_node_t *current_node = *head;
    linked_list_node_t *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}

size_t linked_list_get_len(linked_list_node_t **head)
{
    linked_list_node_t *current_node = *head;
    linked_list_node_t *last_node = NULL;
    size_t count = 0;

    while (current_node)
    {
        count++;
        last_node = current_node;
        current_node = current_node->next;
    }

    return count;
}

linked_list_node_t *linked_list_append(linked_list_node_t **head, linked_list_node_t *item)
{
    linked_list_node_t *tail = linked_list_get_tail(head);
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

linked_list_node_t *linked_list_pop(linked_list_node_t **head)
{
    linked_list_node_t *current = *head;
    if (!current)
    {
        return NULL;
    }
    *head = (*head)->next;
    current->next = NULL;

    return current;
}

linked_list_node_t *linked_list_dequeue(linked_list_node_t **head)
{
    linked_list_node_t *current_node = *head;
    linked_list_node_t *last_node = NULL;

    while (current_node->next)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    last_node->next = NULL;
    return current_node;
}
// higher level exercise
linked_list_node_t *linked_list_reverse(linked_list_node_t **head)
{
    linked_list_node_t *current = *head;
    linked_list_node_t *prev = NULL;
    linked_list_node_t *next = NULL;

    while (current)
    {
        next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    }
    return prev;
}

linked_list_t *linked_list_create_new(const void* data, size_t size)
{
    linked_list_t *new_item = malloc(sizeof(linked_list_t));
    if (!new_item)
    {
        return NULL;
    }
    new_item->data = malloc(size);
    if(!new_item->data)
    {
        free(new_item);
        return NULL;
    }
    memcpy(new_item->data, data, size);
    new_item->node = NULL;
    return new_item;
}

// remove item exercise
int linked_list_remove_item(linked_list_t **head, const void* data, const size_t size)
{
    linked_list_node_t *current = TO_NODE * head;
    linked_list_node_t *prev = NULL;
    while (current)
    {
        const int equal = memcmp(((linked_list_t *)current)->data, data, size);
        if (equal == 0)
        {
            prev->next = current->next;
            linked_list_delete_node(current);
            return 1;
        }

        prev = current;
        current = current->next;
    }

    return 0;
}


void linked_list_delete_node(linked_list_node_t *node_to_delete)
{
    free((TO_LIST node_to_delete)->data);
    free(node_to_delete);
}

void linked_list_delete(linked_list_node_t **head)
{
    linked_list_node_t *current;
    while ((current = linked_list_pop(head)))
    {
        linked_list_delete_node(current);
    }
}

//-------------- DOUBLY LINKED LIST --------------------

d_linked_list_node_t *d_linked_list_get_tail(d_linked_list_node_t **head)
{
    return TO_DL_NODE linked_list_get_tail(TO_NODE_ADDR head);
}

d_linked_list_node_t *d_linked_list_pop(d_linked_list_node_t **head)
{
    d_linked_list_node_t *current = *head;
    if (!current)
    {
        return NULL;
    }
    *head = (*head)->next;
    (*head)->previous = NULL;
    current->next = NULL;

    return current;
}

d_linked_list_node_t *d_linked_list_append(d_linked_list_node_t **head, d_linked_list_node_t *item)
{
    d_linked_list_node_t *tail = d_linked_list_get_tail(head);
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

d_linked_list_t *d_linked_list_create_new(const void *data, const size_t size)
{
    d_linked_list_t *new_item = malloc(sizeof(d_linked_list_t));
    if (!new_item)
    {
        return NULL;
    }
    new_item->data = malloc(size);
    if(!new_item->data)
    {
        free(new_item);
        return NULL;
    }
    memcpy(new_item->data, data, size);
    (TO_DL_NODE new_item)->previous = NULL;
    (TO_DL_NODE new_item)->next = NULL;
    return new_item;
}

// remove item exercise
int d_linked_list_remove_item(d_linked_list_node_t **head, const void *data, const size_t size)
{
    d_linked_list_node_t *current = TO_DL_NODE * head;
    while (current)
    {
        const int equal = memcmp(((d_linked_list_t *)current)->data, data, size);
        if (equal == 0)
        {
            d_linked_list_node_t *prev = current->previous;
            prev->next = current->next;
            if (current->next)
            {
                // if current is not the last element we need to set the "previous"
                // pointer in next node to prev
                current->next->previous = prev;
            }
            // use delete node
            free(current);
            return 1;
        }
        current = current->next;
    }

    return 0;
}

// insert before exercise
int d_linked_list_insert_before(d_linked_list_t **head, d_linked_list_t *item, const void *before_this, const size_t this_size)
{
    d_linked_list_node_t *current = TO_DL_NODE * head;
    while (current)
    {
        const int equal = memcmp(((d_linked_list_t *)current)->data, before_this, this_size);
        if (equal == 0)
        {
            d_linked_list_node_t *prev = current->previous;
            prev->next = TO_DL_NODE item;
            (TO_DL_NODE item)->previous = prev;
            (TO_DL_NODE item)->next = current;
            current->previous = TO_DL_NODE item;
            return 1;
        }

        current = current->next;
    }

    return 0;
}

// insert after exercise
int d_linked_list_insert_after(d_linked_list_t **head, d_linked_list_t *item, const void *after_this, const size_t this_size)
{
    d_linked_list_node_t *current = TO_DL_NODE * head;
    while (current)
    {
        const int equal = memcmp(((d_linked_list_t *)current)->data, after_this, this_size);
        if (equal == 0)
        {
            (TO_DL_NODE item)->next = current->next;
            (TO_DL_NODE item)->previous = current;
            current->next = TO_DL_NODE item;
            if (current->next)
            {
                (TO_DL_NODE item)->next->previous = TO_DL_NODE item;
            }
            return 1;
        }

        current = current->next;
    }

    return 0;
}

int d_linked_list_shuffle(d_linked_list_node_t **head)
{
    const size_t len = linked_list_get_len(TO_NODE_ADDR head);
    d_linked_list_node_t **nodes = calloc(len, sizeof(d_linked_list_node_t *));
    if (!nodes)
    {
        return 0;
    }
    for (size_t i = 0; i < len; i++)
    {
        // granted that is len because already calculated, not possible to go off list
        nodes[i] =TO_DL_NODE linked_list_pop(TO_NODE_ADDR head);
    }
    // now shuffle this array using Fisher&Yates algorithm
    for (size_t i = 0; i < len - 1; i++)
    {
        // clamps the number between i and len
        const size_t new_index = (rand() % (len - i)) + i;
        // swap the two pointers
        d_linked_list_node_t *temp = nodes[new_index];
        nodes[new_index] = nodes[i];
        nodes[i] = temp;
    }
    // reinsert back the elements in new order
    for (size_t i = 0; i < len; i++)
    {
        d_linked_list_append(head, nodes[i]);
    }
    // free memory used in array
    free(nodes);
    return 1;
}

void d_linked_list_delete_node(d_linked_list_node_t *node_to_delete)
{
    free((TO_DLIST node_to_delete)->data);
    free(node_to_delete);
}

void d_linked_list_delete(d_linked_list_node_t **head)
{
    linked_list_node_t *current;
    while ((current = linked_list_pop((TO_NODE_ADDR head))))
    {
        d_linked_list_delete_node(TO_DL_NODE current);
    }
}

//------------------- SETS ---------------------

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

set_table_t *set_table_new(const size_t hashmap_size)
{
    set_table_t *table = malloc(sizeof(set_table_t));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->_collisions = 0;
    table->nodes = calloc(table->hashmap_size, sizeof(set_node_t *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

set_node_t *set_insert(set_table_t **table, const char *key, const size_t key_len)
{
    // check on collisions and rehash if necessary
    if ((*table)->hashmap_size * 0.75f <= (*table)->_collisions)
    {
#ifdef C_DEBUG
        printf("\"%s\" triggered rehashing!\n", key);
#endif
        // load factor is hardcoded and arbitrary
        _rehash(table, sizeof(set_table_t), sizeof(set_node_t *));
    }
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (*table)->hashmap_size;
    linked_list_node_t *head = (*table)->nodes[index];
    if (!head)
    {
        (*table)->nodes[index] = malloc(sizeof(set_node_t));
        if (!(*table)->nodes[index])
        {
            return NULL;
        }
        (TO_SET_NODE (*table)->nodes[index])->key = key;
        (TO_SET_NODE (*table)->nodes[index])->key_len = key_len;
        (*table)->nodes[index]->next = NULL;

        return TO_SET_NODE (*table)->nodes[index];
    }

    set_node_t *new_item = malloc(sizeof(set_node_t));
    if (!new_item)
    {
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;

    linked_list_node_t *tail = head;

    while ((head))
    {
        if ((TO_SET_NODE head)->key == key) // unique keys
        {
            return NULL;
        }
        tail = head;
        head = head->next;
    }
    (*table)->_collisions++;
    tail->next = TO_NODE new_item;
    return new_item;
}

set_node_t *set_search(set_table_t *table, const char *key, const size_t key_len)
{
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % table->hashmap_size;
    linked_list_node_t *head = table->nodes[index];

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
            return TO_SET_NODE head;
        }
        head = head->next;
    }

    // key not found
    return NULL;
}

int set_remove_key(set_table_t **table, const char *key, const size_t key_len)
{
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (*table)->hashmap_size;
    linked_list_node_t *head = (*table)->nodes[index];
    if (!head)
    {
        // no elements with this hash
        return 0;
    }
    if ((TO_SET_NODE head)->key == key)
    {
        if (head->next)
        {
            (*table)->_collisions--;
        }
        // first element in list
        head = head->next;
        free((*table)->nodes[index]);
        (*table)->nodes[index] = head;
        return 1;
    }
    linked_list_node_t *prev = (*table)->nodes[index];
    while (head)
    {
        if ((TO_SET_NODE head)->key == key)
        {
            (*table)->_collisions--;
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

int _rehash(set_table_t **table, const size_t size_of_table, const size_t size_of_element)
{
    // allocate
    set_table_t *new_table = malloc(size_of_table);
    if (!new_table)
    {
        return 0;
    }
    new_table->_collisions = 0;
    new_table->hashmap_size = (*table)->hashmap_size * 2;
    new_table->nodes = calloc(new_table->hashmap_size, size_of_element);
    if (!(*table)->nodes)
    {
        free(new_table);
        return 0;
    }

    for (size_t i = 0; i < (*table)->hashmap_size; i++)
    {
        while ((*table)->nodes[i])
        {
            // pop from list using list function
            linked_list_node_t *current = linked_list_pop(&(*table)->nodes[i]);
#ifdef C_DEBUG
            printf("current = %s\n", (TO_SET_NODE current)->key);
#endif
            if (!current)
            {
                // shouldn't happen, but just in case...
                continue;
            }
            const size_t hash = djb33x_hash((TO_SET_NODE current)->key, (TO_SET_NODE current)->key_len);
            const size_t index = hash % new_table->hashmap_size;
            // insert in new table
            if (!new_table->nodes[index])
            {
                // first element
                new_table->nodes[index] = current;
            }
            else
            {
                //append in list
                linked_list_append(&new_table->nodes[index], current);
                new_table->_collisions++;
            }
#ifdef C_DEBUG
            printf("new_table->nodes[%zu] = %s\n", index, (TO_SET_NODE new_table->nodes[index])->key);
#endif
        }
    }
    free((*table)->nodes);
    free((*table));
    *table = new_table;
    return 1;
}

void set_delete(set_table_t **table)
{
    //empty collision lists
    for (size_t i = 0; i < (*table)->hashmap_size; i++)
    {
        linked_list_node_t *current;
        while ((current = linked_list_pop(&(*table)->nodes[i])))
        {
            free(current);
        }
    }
    free((*table)->nodes);//hashtable
    free(*table);//structure
}

//-------------- DICTIONARY -----------------

dictionary_t *dictionary_new(const size_t hashmap_size)
{
    dictionary_t *table = malloc(sizeof(dictionary_t));
    if (!table)
    {
        return NULL;
    }
    (TO_SET table)->hashmap_size = hashmap_size;
    (TO_SET table)->nodes = calloc((TO_SET table)->hashmap_size, sizeof(dictionary_node_t *));
    (TO_SET table)->_collisions = 0;
    if (!(TO_SET table)->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

dictionary_node_t *dictionary_insert(dictionary_t **table, const char *key, const size_t key_len, void *data, size_t datasize)
{
    if ((TO_SET (*table))->hashmap_size * 0.75f <= (TO_SET (*table))->_collisions)
    {
#ifdef C_DEBUG
        printf("\"%s\" triggered rehashing!\n", key);
#endif
        // load factor is hardcoded and arbitrary
        _rehash(TO_SET_ADDR table, sizeof(dictionary_t), sizeof(dictionary_node_t *));
    }
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (TO_SET (*table))->hashmap_size;
    linked_list_node_t *head = (TO_SET (*table))->nodes[index];
    if (!head)
    {
        (TO_SET (*table))->nodes[index] = malloc(sizeof(dictionary_node_t));
        if (!(TO_SET (*table))->nodes[index])
        {
            return NULL;
        }
        // sorry, it's a bit messed up, I still haven't figured out a good solution
        (TO_SET_NODE(TO_SET (*table))->nodes[index])->key = key;
        (TO_SET_NODE(TO_SET (*table))->nodes[index])->key_len = key_len;
        (TO_DICT_NODE(TO_SET (*table))->nodes[index])->data = malloc(datasize);
        memcpy((TO_DICT_NODE(TO_SET (*table))->nodes[index])->data,
        data, datasize);
        (TO_SET (*table))->nodes[index]->next = NULL;

        return TO_DICT_NODE (TO_SET (*table))->nodes[index];
    }

    dictionary_node_t *new_item = malloc(sizeof(dictionary_node_t));
    if (!new_item)
    {
        return NULL;
    }

    (TO_SET_NODE new_item)->key = key;
    (TO_SET_NODE new_item)->key_len = key_len;
    new_item->data = malloc(datasize);
    memcpy(new_item->data, data, datasize);
    (TO_NODE new_item)->next = NULL;

    linked_list_node_t *tail = head;

    while ((head))
    {
        if ((TO_SET_NODE head)->key == key) // unique keys
        {
            return NULL;
        }
        tail = head;
        head = head->next;
    }

    tail->next = TO_NODE new_item;
    (TO_SET (*table))->_collisions++;
    return new_item;
}

dictionary_node_t *dictionary_search(dictionary_t *table, const char *key, const size_t key_len)
{
    return TO_DICT_NODE set_search(TO_SET table, key, key_len);
}

int dictionary_remove_key(dictionary_t **table, const char *key, const size_t key_len)
{
    return set_remove_key(TO_SET_ADDR table, key, key_len);
}

void dictionary_delete(dictionary_t **table)
{
    //empty collision lists
    for (size_t i = 0; i < (TO_SET(*table))->hashmap_size; i++)
    {
        linked_list_node_t *current;
        while ((current = linked_list_pop(&(TO_SET(*table))->nodes[i])))
        {
            free((TO_DICT_NODE current)->data);
            free(current);
        }
    }
    free((TO_SET(*table))->nodes);//hashtable
    free(*table);//structure
}

// -------------------- DYNAMIC ARRAY -----------------------

list_t *list_new(size_t size)
{
    if(!size)
    {
        size = 10;        
    }
    list_t *list = malloc(sizeof(list_t));
    list->_allocated_size = size;
    list->_current_size = 0;
    list->data = calloc(size, sizeof(void*));
    return list;
}

static int _list_extend_size(list_t **list)
{
    void **new_data = realloc((*list)->data, sizeof(void*)* ((*list)->_allocated_size * 2));
    if(!new_data)
    {
        return 0;
    }
    (*list)->data = new_data;
    (*list)->_allocated_size*=2;
    return 1;
}

//pass a pointer to the data that you want to store (ex. int n -> &n);
//if you want to store an array just pass that (ex char* str -> str).
int list_append(list_t **list, void *value, size_t size)
{
    if((*list)->_current_size >= (*list)->_allocated_size)
    {
        if(!_list_extend_size(list))
        {
            return 0;
        }
    }
    (*list)->data[(*list)->_current_size] = malloc(size);
    memcpy((*list)->data[(*list)->_current_size], value, size);
    (*list)->_current_size++;
    return 1;
}

//use casting macro TO_(type) only if element is not a pointer
void *list_get(list_t **list, size_t index)
{
    if(index >= (*list)->_current_size)
    {
        return (void*)0;
    }
    return(*list)->data[index];
}

size_t list_len(list_t *list)
{
    return list->_current_size;
}

//pass a pointer to the data that you want to store (ex. int n -> &n);
//if you want to store an array just pass that (ex char* str -> str).
int list_insert(list_t **list, size_t index, void *value, size_t size)
{
    if((*list)->_current_size >= (*list)->_allocated_size)
    {
        if(!_list_extend_size(list))
        {
            return 0;
        }
    }
    //moves the following elements 1 cell ahead
    memmove((*list)->data + index + 1, (*list)->data + index, 
    sizeof(void*) * ((*list)->_current_size - index));
    (*list)->data[index] = malloc(size);
    memcpy((*list)->data[index], value, size);
    (*list)->_current_size++;
    return 1;
}

int list_remove(list_t** list, size_t index)
{
    if(index >= (*list)->_current_size)
    {
        return 0;
    }
    memmove((*list)->data + index, (*list)->data + index + 1, 
    sizeof(void*) * ((*list)->_current_size - index));
    (*list)->_current_size--;
    free((*list)->data[(*list)->_current_size]);
    return 1;
}

void *list_pop(list_t **list)
{
    void* data = list_get(list, 0);
    list_remove(list, 0);
    return data;
}

list_t *list_copy(list_t **list, size_t datasize)
{
    list_t *copy = list_new((*list)->_current_size);
    for (size_t i = 0; i < (*list)->_current_size; i++)
    {
        list_append(&copy, (*list)->data[i], datasize);
    }
    return copy;
}

void list_print(list_t *list)
{
    printf("[ ");
    for (size_t i = 0; i < list->_current_size; i++)
    {
        printf("%d ",TO_(int) list->data[i]);
        if (i != list->_current_size-1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

//deallocates the given list
void list_delete(list_t **list)
{
    for (size_t i = 0; i < (*list)->_current_size; i++)
    {
        free((*list)->data[i]);
    }
    free((*list)->data);
    free((*list));
}