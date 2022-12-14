#include "collections.c"
#include "test_collections.h"
#include <time.h>

int main(int argc, char** argv)
{
    srand(time(0));
    test_linked_list();
    test_d_linked_list();
    test_set();
    test_dictionary();
    test_list();
    return 0;
}

// --------------------- linked list ----------------------
void test_linked_list()
{
    printf("\n");
    puts("########## LINKED LIST ##########");
    printf("[test]\n");
    test_linked_list_print();
    printf("[test]\n");
    test_linked_list_get_tail();
    printf("[test]\n");
    test_linked_list_reverse();
    printf("[test]\n");
    test_linked_list_pop();
    printf("[test]\n");
    test_linked_list_dequeue();
    printf("[test]\n");
    test_linked_list_remove_item();
}

linked_list_int_t *init_linked_list()
{
    linked_list_int_t* list = linked_list_int_create_new(1);
    linked_list_append(TO_NODE_ADDR &list, TO_NODE linked_list_int_create_new(2));
    linked_list_append(TO_NODE_ADDR &list, TO_NODE linked_list_int_create_new(3));
    return list;
}

void test_linked_list_print()
{
    linked_list_int_t* list = init_linked_list();
    printf("full list is: ");
    linked_list_int_print(TO_NODE_INT_ADDR &list);
    linked_list_delete(TO_NODE_ADDR &list);
}

void test_linked_list_reverse()
{
    linked_list_int_t* list = init_linked_list();
    printf("reversed list is: ");
    list = TO_NODE_INT linked_list_reverse(TO_NODE_ADDR &list);
    linked_list_int_print(&list);
    linked_list_delete(TO_NODE_ADDR&list);
}

void test_linked_list_get_tail()
{
    linked_list_int_t *list = init_linked_list();
    linked_list_int_t *tail = TO_NODE_INT linked_list_get_tail(TO_NODE_ADDR &list);
    printf("tail is = %d\n", tail->data);
    linked_list_delete(TO_NODE_ADDR&list);
}

void test_linked_list_pop()
{
    linked_list_int_t* list = init_linked_list();
    printf("before pop list is: ");
    linked_list_int_print(TO_NODE_INT_ADDR &list);
    linked_list_pop(TO_NODE_ADDR &list);
    printf("after pop list is: ");
    linked_list_int_print(TO_NODE_INT_ADDR &list);
    linked_list_delete(TO_NODE_ADDR&list);
}

void test_linked_list_dequeue()
{
    linked_list_int_t* list = init_linked_list();
    printf("before dequeue list is: ");
    linked_list_int_print(TO_NODE_INT_ADDR &list);
    linked_list_dequeue(TO_NODE_ADDR &list);
    printf("after dequeue list is: ");
    linked_list_int_print(TO_NODE_INT_ADDR &list);
    linked_list_delete(TO_NODE_ADDR&list);
}

void test_linked_list_remove_item()
{
    int to_remove = 2;
    linked_list_int_t* list = init_linked_list();
    printf("before %d removal list is: ", to_remove);
    linked_list_int_print(TO_NODE_INT_ADDR &list);
    linked_list_int_remove_item(TO_NODE_INT_ADDR &list, to_remove);
    printf("after %d removal list is: ", to_remove);
    linked_list_int_print(TO_NODE_INT_ADDR &list);
    linked_list_delete(TO_NODE_ADDR&list);
}
// -----------------doubly linked list ---------------------

d_linked_list_int_t *init_doubly_linked_list()
{
    d_linked_list_node_t* list = TO_DL_NODE d_linked_list_int_create_new(9);
    d_linked_list_append(TO_DL_NODE_ADDR &list, TO_DL_NODE d_linked_list_int_create_new(5));
    d_linked_list_append(TO_DL_NODE_ADDR &list, TO_DL_NODE d_linked_list_int_create_new(2));
    d_linked_list_append(TO_DL_NODE_ADDR &list, TO_DL_NODE d_linked_list_int_create_new(1));
    d_linked_list_append(TO_DL_NODE_ADDR &list, TO_DL_NODE d_linked_list_int_create_new(4));
    return TO_DL_NODE_INT list;
}

void test_d_linked_list()
{
    printf("\n");
    puts("########## DOUBLY LINKED LIST ##########");
    printf("[test]\n");
    test_d_linked_list_print();
    printf("[test]\n");
    test_d_linked_list_get_tail();
    printf("[test]\n");
    test_d_linked_list_remove_item();
    printf("[test]\n");
    test_d_linked_list_insert_before();
    printf("[test]\n");
    test_d_linked_list_insert_after();
    printf("[test]\n");
    test_d_linked_list_shuffle();
}

void test_d_linked_list_get_tail()
{
    d_linked_list_int_t *list = init_doubly_linked_list();
    d_linked_list_int_t *tail = TO_DL_NODE_INT d_linked_list_get_tail( TO_DL_NODE_ADDR &list);
    printf("tail is: %d\n", tail->data);
    d_linked_list_delete(TO_DL_NODE_ADDR &list);
}

void test_d_linked_list_print()
{
    d_linked_list_int_t *list = init_doubly_linked_list();
    printf("full list is: ");
    d_linked_list_int_print(&list);
    d_linked_list_delete(TO_DL_NODE_ADDR &list);
}

void test_d_linked_list_remove_item()
{
    int to_remove = 5;
    d_linked_list_int_t *list = init_doubly_linked_list();
    printf("before %d removal list is: ", to_remove);
    d_linked_list_int_print(&list);
    d_linked_list_int_remove_item(TO_DL_NODE_ADDR &list, to_remove);
    printf("after %d removal list is: ", to_remove);
    d_linked_list_int_print(&list);
    d_linked_list_delete(TO_DL_NODE_ADDR &list);
}

void test_d_linked_list_insert_before()
{
    int to_insert = 10, before_this = 5;
    d_linked_list_int_t *list = init_doubly_linked_list();
    d_linked_list_int_t *item = d_linked_list_int_create_new(to_insert);
    printf("inserting %d before %d\n", to_insert, before_this);
    d_linked_list_int_insert_before(&list, item, before_this);
    printf("list after insertion is: ");
    d_linked_list_int_print(&list);
    d_linked_list_delete(TO_DL_NODE_ADDR &list);
}

void test_d_linked_list_insert_after()
{
    int to_insert = 10, after_this = 5;
    d_linked_list_int_t *list = init_doubly_linked_list();
    d_linked_list_int_t *item = d_linked_list_int_create_new(to_insert);
    printf("inserting %d after %d\n", to_insert, after_this);
    d_linked_list_int_insert_after(&list, item, after_this);
    printf("list after insertion is: ");
    d_linked_list_int_print(&list);
    d_linked_list_delete(TO_DL_NODE_ADDR &list);
}

void test_d_linked_list_shuffle()
{
    d_linked_list_int_t *list = init_doubly_linked_list();
    printf("List before shuffling: ");
    d_linked_list_int_print(&list);
    d_linked_list_shuffle(TO_DL_NODE_ADDR &list);
    printf("List after shuffling: ");
    d_linked_list_int_print(&list);
    d_linked_list_delete(TO_DL_NODE_ADDR &list);
}

//--------------------- SETS ------------------------

set_table_t *init_set()
{
    set_table_t *table = set_table_new(3);
    set_insert(&table, "Parma", strlen("Parma"));
    set_insert(&table, "Milano", strlen("Milano"));
    set_insert(&table, "Firenze", strlen("Firenze"));
    set_insert(&table, "Lucca", strlen("Lucca"));
    set_insert(&table, "Vicenza", strlen("Vicenza"));
    set_insert(&table, "Padova", strlen("Padova"));
    set_insert(&table, "Palermo", strlen("Palermo"));
    set_insert(&table, "Pisa", strlen("Pisa"));
    return table;
}

void test_set()
{
    printf("\n");
    puts("########## SETS ##########");
    printf("[test]\n");
    test_set_search();
    printf("[test]\n");
    test_set_removal();
}

void test_set_search()
{
    set_table_t *table = init_set();
    char *string = "Milano";
    set_node_t *found = set_search(table, string, strlen(string));

    if(found)
        printf("%s key found!\n", found->key);
    else
        printf("%s key not found...\n", string);

    string = "Modena";
    found = set_search(table, string, strlen(string));

    if(found)
        printf("%s key found!\n", found->key);
    else
        printf("%s key not found...\n", string);


    string = "Pisa";
    found = set_search(table, string, strlen(string));

    if(found)
        printf("%s key found!\n", found->key);
    else
        printf("%s key not found...\n", string);

    string = "Lucca";
    found = set_search(table, string, strlen(string));

    if(found)
        printf("%s key found!\n", found->key);
    else
        printf("%s key not found...\n", string);

    set_delete(&table);
}

void test_set_removal()
{
    set_table_t *table = init_set();
    printf("set hashmap size: %d\n",(int)table->hashmap_size);
    printf("set collisions = %d\n", table->_collisions);
    set_node_t *found = set_search(table, "Milano", strlen("Milano"));
    int removed = set_remove_key(&table, "Milano", strlen("Milano"));
    found = set_search(table, "Milano", strlen("Milano"));
    if(!found)
        printf("Milano key removed\n");
    removed = set_remove_key(&table, "Vicenza", strlen("Vicenza"));
    found = set_search(table, "Vicenza", strlen("Vicenza"));
    if(!found)
        printf("Vicenza key removed\n");
    printf("set collisions = %d\n", table->_collisions);

    set_delete(&table);
}
//--------------------- DICTIONARY ------------------------

dictionary_t *init_dictionary()
{
    //forcing collisions
    dictionary_t *dict = dictionary_new(2);
    int n = 8;
    char *string = "byte";
    dictionary_insert(&dict, string, strlen(string), &n, sizeof(int));
    n = 16;
    string = "2bytes";
    dictionary_insert(&dict, string, strlen(string), &n, sizeof(int));
    n = 32;
    string = "4bytes";
    dictionary_insert(&dict, string, strlen(string), &n, sizeof(int));
    n = 64;
    string = "8bytes";
    dictionary_insert(&dict, string, strlen(string), &n, sizeof(int));
    n = 128;
    string = "16bytes";
    dictionary_insert(&dict, string, strlen(string), &n, sizeof(int));

    return dict;
}

void test_dictionary()
{
    printf("\n");
    puts("########## DICTIONARY ##########");
    printf("[test]\n");
    test_dictionary_search();
    printf("[test]\n");
    test_dictionary_removal();
}

void test_dictionary_search()
{
    dictionary_t *d = init_dictionary();
    char *string = "byte";
    dictionary_node_t* node = dictionary_search(d, string, strlen(string));
    if(node)
    {
        printf("key = %s, data = %d\n", string, TO_INT node->data);
    }
    string = "2bytes";
    node = dictionary_search(d, string, strlen(string));
    if(node)
    {
        printf("key = %s, data = %d\n", string, TO_INT node->data);
    }
    string = "3bytes";
    node = dictionary_search(d, string, strlen(string));
    if(!node)
    {
        printf("key %s not found\n", string);
    }
    string = "16bytes";
    node = dictionary_search(d, string, strlen(string));
    if(node)
    {
        printf("key = %s, data = %d\n", string, TO_INT node->data);
    }

    dictionary_delete(&d);
}

void test_dictionary_removal()
{
    dictionary_t *d = init_dictionary();
    printf("set collisions = %d\n", (TO_SET d)->_collisions);
    char *string = "4bytes";
    printf("removing \"%s\" key from dictionary...\n", string);
    int result = dictionary_remove_key(&d, string, strlen(string));
    printf("removal ended with %d\n", result);
    dictionary_node_t *node = dictionary_search(d, string, strlen(string));
    if(node)
    {
        printf("\"%s\" key found\n", (TO_SET_NODE node)->key);
    }
    else{
        printf("\"%s\" key removed successfully!\n", string);
    }
    printf("set collisions = %d\n", (TO_SET d)->_collisions);

    dictionary_delete(&d);
}
// ---------------------- LIST -------------------------

void test_list()
{
    printf("\n");
    puts("########## LIST ##########");
    printf("[test]\n");
    test_list_get();
    printf("[test]\n");
    test_list_remove();
    printf("[test]\n");
    test_list_pop();
    printf("[test]\n");
    test_list_copy();
    printf("[test]\n");
    test_list_insert();    
}

list_t *init_list()
{
    list_t *list = list_new(10);
    for (int i = 0; i < 10; i++)
    {
        list_append(&list, &i, sizeof(int));
    }
    return list; 
} 
void test_list_get()
{
    list_t *list = init_list();
    int data = TO_INT list_get(&list, 8);
    printf("data at index = 8: %d\n", data);
    list_delete(&list);
}
void test_list_insert()
{
    list_t *list = init_list();
    int n = 69;
    list_insert(&list, 1, &n, sizeof(int));
    printf("inserted value at index 1 is: \"%d\"\n", TO_INT list_get(&list, 1));
    printf("new size is: %zu\n", list->_allocated_size);
    printf("last value is: %d at index: %zu\n", TO_INT list_get(&list, list->_current_size-1), list->_current_size-1);
    list_print(list);
    list_delete(&list);
}

void test_list_remove()
{
    list_t *list = init_list();
    printf("list before removal at index 4: ");
    list_print(list);
    list_remove(&list, 4);
    printf("list after removal at index 4: ");
    list_print(list);
    list_remove(&list, 8);
    printf("list after removal of last element: ");
    list_print(list);
    list_delete(&list);
}

void test_list_pop()
{
    list_t *list = init_list();
    printf("list before pop: ");
    list_print(list);
    int data = TO_INT list_pop(&list);
    printf("popped item: %d\n", data);
    printf("list after pop: ");
    list_print(list);
    list_delete(&list);
}
void test_list_copy()
{
    list_t *list = init_list();
    list_t *copy = list_copy(&list, sizeof(int));
    printf("this is a copy of list: ");
    list_print(copy);
    list_delete(&list);
    list_delete(&copy);
}