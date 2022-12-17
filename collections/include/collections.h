
#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#define COLL_VER 1.0

#define TO_NODE (linked_list_node_t *)
#define TO_NODE_ADDR (linked_list_node_t **)
#define TO_LIST (linked_list_t *)
#define TO_LIST_ADDR (linked_list_t **)
#define TO_DL_NODE (d_linked_list_node_t *)
#define TO_DL_NODE_ADDR (d_linked_list_node_t **)
#define TO_DLIST (d_linked_list_t *)
#define TO_DLIST_ADDR (d_linked_list_t **)
#define TO_SET_NODE (set_node_t *)
#define TO_SET (set_table_t *)
#define TO_SET_ADDR (set_table_t **)
#define TO_DICT_NODE (dictionary_node_t *)

#define TO_(type) *(type*)
//--------------- LINKED LIST ---------------------

typedef struct linked_list_node
{
    struct linked_list_node *next;

} linked_list_node_t;

// node with value
typedef struct linked_list
{
    linked_list_node_t *node;
    void* data;

} linked_list_t;

linked_list_node_t *linked_list_get_tail(linked_list_node_t **head);
size_t linked_list_get_len(linked_list_node_t **head);
linked_list_node_t *linked_list_append(linked_list_node_t **head, linked_list_node_t *item);
linked_list_node_t *linked_list_pop(linked_list_node_t **head);
linked_list_node_t *linked_list_dequeue(linked_list_node_t **head);
linked_list_node_t *linked_list_reverse(linked_list_node_t **head);
linked_list_t *linked_list_create_new(const void* data, const size_t size);
int linked_list_remove_item(linked_list_t **head, const void* data, const size_t size);
void linked_list_delete_node(linked_list_node_t *node_to_delete);
void linked_list_delete(linked_list_node_t **head);

//-------------- DOUBLY LINKED LIST --------------------

typedef struct d_linked_list_node
{
    struct d_linked_list_node *next;
    struct d_linked_list_node *previous;

} d_linked_list_node_t;

// node with value
typedef struct d_linked_list
{
    d_linked_list_node_t node;
    void *data;

} d_linked_list_t;

d_linked_list_node_t *d_linked_list_get_tail(d_linked_list_node_t **head);
d_linked_list_node_t *d_linked_list_append(d_linked_list_node_t **head, d_linked_list_node_t *item);
d_linked_list_t *d_linked_list_create_new(const void *data, const size_t size);
int d_linked_list_remove_item(d_linked_list_node_t **head, const void *data, const size_t size);
int d_linked_list_insert_before(d_linked_list_t **head, d_linked_list_t *item, const void *before_this, const size_t this_size);
int d_linked_list_insert_after(d_linked_list_t **head, d_linked_list_t *item, const void *after_this, const size_t this_size);
int d_linked_list_shuffle(d_linked_list_node_t **head);
void d_linked_list_delete_node(d_linked_list_node_t *node_to_delete);
void d_linked_list_delete(d_linked_list_node_t **head);

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

size_t djb33x_hash(const char *key, const size_t keylen);
int _rehash(set_table_t **table, const size_t size_of_table, const size_t size_of_element);
set_table_t *set_table_new(const size_t hashmap_size);
set_node_t *set_insert(set_table_t **table, const char *key, const size_t key_len);
set_node_t *set_search(set_table_t *table, const char *key, const size_t key_len);
int set_remove_key(set_table_t **table, const char *key, const size_t key_len);
void set_delete(set_table_t **table);

//-------------- DICTIONARY -----------------

typedef struct dic_node
{
    set_node_t node;
    void *data;

} dictionary_node_t;

typedef struct dic
{
    set_table_t table;
} dictionary_t;

dictionary_t *dictionary_new(const size_t hashmap_size);
dictionary_node_t *dictionary_insert(dictionary_t **table, const char *key, const size_t key_len, void *data, size_t datasize);
dictionary_node_t *dictionary_search(dictionary_t *table, const char *key, const size_t key_len);
int dictionary_remove_key(dictionary_t **table, const char *key, const size_t key_len);
void dictionary_delete(dictionary_t **table);

// -------------------- DYNAMIC ARRAY -----------------------

typedef struct list
{
    size_t _current_size;
    size_t _allocated_size;
    void **data;

}list_t;

list_t *list_new(size_t size);
static int _list_extend_size(list_t **list);
int list_append(list_t **list, void *value, size_t size);
void *list_get(list_t **list, size_t index);
size_t list_len(list_t *list);
int list_insert(list_t **list, size_t index, void *value, size_t size);
int list_remove(list_t** list, size_t index);
void *list_pop(list_t **list);
list_t *list_copy(list_t **list, size_t datasize);
void list_print(list_t *list);
void list_delete(list_t **list);
#endif