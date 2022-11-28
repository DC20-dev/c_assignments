#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define TO_NODE (linked_list_node_t *)
#define TO_DL_NODE (d_linked_list_node_t *)
#define TO_SET_NODE (set_node_t *)
#define TO_SET (set_table_t *)
#define TO_DICT_NODE (dictionary_node_t *)

typedef union data
{
    uint8_t byte;
    uint16_t bytes_2;
    uint32_t bytes_4;
    uint64_t bytes_8;
} data_t;

//--------------- Linked List ---------------------

typedef struct linked_list_node
{
    struct linked_list_node *next;

} linked_list_node_t;

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

int linked_list_get_len(linked_list_node_t **head)
{
    linked_list_node_t *current_node = *head;
    linked_list_node_t *last_node = NULL;
    int count = 0;

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

// node with value
typedef struct linked_list_int
{
    linked_list_node_t *node;
    int data;

} linked_list_int_t;

linked_list_int_t *linked_list_int_create_new(const int value)
{
    linked_list_int_t *new_item = malloc(sizeof(linked_list_int_t));
    if (!new_item)
    {
        return NULL;
    }
    new_item->data = value;
    new_item->node = NULL;
    return new_item;
}

// remove item exercise
int linked_list_int_remove_item(linked_list_int_t **head, const int item)
{
    linked_list_node_t *current = TO_NODE * head;
    linked_list_node_t *prev = NULL;
    while (current)
    {
        if (((linked_list_int_t *)current)->data == item)
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

void linked_list_int_print(linked_list_int_t **head)
{
    linked_list_node_t *current = TO_NODE * head;
    printf("[");
    while (current)
    {
        printf("%d", ((linked_list_int_t *)current)->data);
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

} d_linked_list_node_t;

d_linked_list_node_t *d_linked_list_get_tail(d_linked_list_node_t **head)
{
    return TO_DL_NODE linked_list_get_tail(TO_NODE head);
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
// node with value
typedef struct d_linked_list_int
{
    d_linked_list_node_t node;
    int data;

} d_linked_list_int_t;

d_linked_list_int_t *d_linked_list_int_create_new(const int value)
{
    d_linked_list_int_t *new_item = malloc(sizeof(d_linked_list_int_t));
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
int d_linked_list_int_remove_item(d_linked_list_node_t **head, const int item)
{
    d_linked_list_node_t *current = TO_DL_NODE * head;
    while (current)
    {
        if (((d_linked_list_int_t *)current)->data == item)
        {
            d_linked_list_node_t *prev = current->previous;
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

void d_linked_list_int_print(d_linked_list_int_t **head)
{
    d_linked_list_node_t *current = TO_NODE * head;
    printf("[");
    while (current)
    {
        printf("%d", ((d_linked_list_int_t *)current)->data);
        if (current->next)
        {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

// insert before exercise
int d_linked_list_int_insert_before(d_linked_list_int_t **head, d_linked_list_int_t *item, const int before_this)
{
    d_linked_list_node_t *current = TO_DL_NODE * head;
    while (current)
    {
        if (((d_linked_list_int_t *)current)->data == before_this)
        {
            d_linked_list_node_t *prev = current->previous;
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
int d_linked_list_int_insert_after(d_linked_list_int_t **head, d_linked_list_int_t *item, const int after_this)
{
    d_linked_list_node_t *current = TO_DL_NODE * head;
    while (current)
    {
        if (((d_linked_list_int_t *)current)->data == after_this)
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

int d_linked_list_shuffle(d_linked_list_node_t **head)
{
    const size_t len = linked_list_get_len(head);
    d_linked_list_node_t **nodes = calloc(len, sizeof(d_linked_list_node_t *));
    if (!nodes)
    {
        return 0;
    }
    for (size_t i = 0; i < len; i++)
    {
        // granted that is len because already calculated, not possible to go off list
        nodes[i] = linked_list_pop(head);
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

//------------------- SETS ---------------------

typedef struct set_node
{
    linked_list_node_t *next;
    size_t key_len;
    const char *key;

} set_node_t;

typedef struct set_table
{
    linked_list_node_t **nodes;
    size_t hashmap_size;
    int _collisions;
} set_table_t;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

int _rehash(set_table_t *table, const size_t size_of_table, const size_t size_of_element);

set_table_t *set_table_new(const size_t hashmap_size)
{
    set_table_t *table = malloc(sizeof(set_table_t));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(set_node_t *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

set_node_t *set_insert(set_table_t *table, const char *key, const size_t key_len)
{
    // check on collisions and rehash if necessary
    if (table->hashmap_size * 0.75f <= table->_collisions)
    {
#ifdef C_DEBUG
        printf("\"%s\" triggered rehashing!\n", key);
#endif
        // load factor is hardcoded and arbitrary
        _rehash(table, sizeof(set_table_t), sizeof(set_node_t *));
    }
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % table->hashmap_size;
    linked_list_node_t *head = table->nodes[index];
    if (!head)
    {
        table->nodes[index] = malloc(sizeof(set_node_t));
        if (!table->nodes[index])
        {
            return NULL;
        }
        (TO_SET_NODE table->nodes[index])->key = key;
        (TO_SET_NODE table->nodes[index])->key_len = key_len;
        table->nodes[index]->next = NULL;

        return table->nodes[index];
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
    table->_collisions++;
    tail->next = new_item;
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
            return head;
        }
        head = head->next;
    }

    // key not found
    return NULL;
}

int set_remove_key(set_table_t *table, const char *key, const size_t key_len)
{
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % table->hashmap_size;
    linked_list_node_t *head = table->nodes[index];
    if (!head)
    {
        // no elements with this hash
        return 0;
    }
    if ((TO_SET_NODE head)->key == key)
    {
        if (head->next)
        {
            table->_collisions--;
        }
        // first element in list
        head = head->next;
        free(table->nodes[index]);
        table->nodes[index] = head;
        return 1;
    }
    linked_list_node_t *prev = table->nodes[index];
    while (head)
    {
        if ((TO_SET_NODE head)->key == key)
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

int _rehash(set_table_t *table, const size_t size_of_table, const size_t size_of_element)
{
    // allocate
    set_table_t *new_table = malloc(size_of_table);
    if (!new_table)
    {
        return 0;
    }
    new_table->_collisions = 0;
    new_table->hashmap_size = table->hashmap_size * 2;
    new_table->nodes = calloc(new_table->hashmap_size, size_of_element);
    if (!table->nodes)
    {
        free(new_table);
        return 0;
    }

    for (size_t i = 0; i < table->hashmap_size; i++)
    {
        while (table->nodes[i])
        {
            // pop from list using list function
            linked_list_node_t *current = linked_list_pop(&table->nodes[i]);
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
            printf("new_table->nodes[%d] = %s\n", index, (TO_SET_NODE new_table->nodes[index])->key);
#endif
        }
    }
    free(table);
    *table = *new_table;
    return 1;
}

//-------------- DICTIONARY -----------------

typedef struct dic_node
{
    set_node_t node;
    data_t data;

} dictionary_node_t;

typedef struct dic
{
    set_table_t table;
} dictionary_t;

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

dictionary_node_t *dictionary_insert(dictionary_t *table, const char *key, const size_t key_len, const data_t data)
{
    if ((TO_SET table)->hashmap_size * 0.75f <= (TO_SET table)->_collisions)
    {
#ifdef C_DEBUG
        printf("\"%s\" triggered rehashing!\n", key);
#endif
        // load factor is hardcoded and arbitrary
        _rehash(table, sizeof(dictionary_t), sizeof(dictionary_node_t *));
    }
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (TO_SET table)->hashmap_size;
    linked_list_node_t *head = (TO_SET table)->nodes[index];
    if (!head)
    {
        (TO_SET table)->nodes[index] = malloc(sizeof(dictionary_node_t));
        if (!(TO_SET table)->nodes[index])
        {
            return NULL;
        }
        (TO_SET_NODE(TO_SET table)->nodes[index])->key = key;
        (TO_SET_NODE(TO_SET table)->nodes[index])->key_len = key_len;
        (TO_DICT_NODE(TO_SET table)->nodes[index])->data = data;
        (TO_SET table)->nodes[index]->next = NULL;

        return (TO_SET table)->nodes[index];
    }

    dictionary_node_t *new_item = malloc(sizeof(dictionary_node_t));
    if (!new_item)
    {
        return NULL;
    }

    (TO_SET_NODE new_item)->key = key;
    (TO_SET_NODE new_item)->key_len = key_len;
    new_item->data = data;
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

    tail->next = new_item;
    (TO_SET table)->_collisions++;
}

dictionary_node_t *dictionary_search(dictionary_t *table, const char *key, const size_t key_len)
{
    return TO_DICT_NODE set_search(table, key, key_len);
}

int dictionary_remove_key(dictionary_t *table, const char *key, const size_t key_len)
{
    return set_remove_key(table, key, key_len);
}