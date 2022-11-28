#include "collections.c"
#include "test_collections.h"
#include <string.h>

int main(int argc, char** argv)
{
    srand(time(0));
    test_linked_list();
    test_d_linked_list();
    test_set();
    test_dictionary();
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
    linked_list_append(TO_NODE &list, TO_NODE linked_list_int_create_new(2));
    linked_list_append(TO_NODE &list, TO_NODE linked_list_int_create_new(3));
    return list;
}

void test_linked_list_print()
{
    linked_list_int_t* list = init_linked_list();
    printf("full list is: ");
    linked_list_int_print(TO_NODE &list);
}

void test_linked_list_reverse()
{
    linked_list_int_t* list = init_linked_list();
    printf("reversed list is: ");
    list = linked_list_reverse(TO_NODE &list);
    linked_list_int_print(&list);
}

void test_linked_list_get_tail()
{
    linked_list_int_t *list = init_linked_list();
    linked_list_int_t *tail = linked_list_get_tail(TO_NODE &list);
    printf("tail is = %d\n", tail->data);
}

void test_linked_list_pop()
{
    linked_list_int_t* list = init_linked_list();
    printf("before pop list is: ");
    linked_list_int_print(TO_NODE &list);
    linked_list_pop(TO_NODE &list);
    printf("after pop list is: ");
    linked_list_int_print(TO_NODE &list);
}

void test_linked_list_dequeue()
{
    linked_list_int_t* list = init_linked_list();
    printf("before dequeue list is: ");
    linked_list_int_print(TO_NODE &list);
    linked_list_dequeue(TO_NODE &list);
    printf("after dequeue list is: ");
    linked_list_int_print(TO_NODE &list);
}

void test_linked_list_remove_item()
{
    int to_remove = 2;
    linked_list_int_t* list = init_linked_list();
    printf("before %d removal list is: ", to_remove);
    linked_list_int_print(TO_NODE &list);
    linked_list_int_remove_item(TO_NODE &list, to_remove);
    printf("after %d removal list is: ", to_remove);
    linked_list_int_print(TO_NODE &list);
}
// -----------------doubly linked list ---------------------

d_linked_list_node *init_doubly_linked_list()
{
    d_linked_list_node* list = d_linked_list_int_create_new(9);
    d_linked_list_append(TO_DL_NODE &list, TO_DL_NODE d_linked_list_int_create_new(5));
    d_linked_list_append(TO_DL_NODE &list, TO_DL_NODE  d_linked_list_int_create_new(2));
    d_linked_list_append(TO_DL_NODE &list, TO_DL_NODE  d_linked_list_int_create_new(1));
    d_linked_list_append(TO_DL_NODE &list, TO_DL_NODE  d_linked_list_int_create_new(4));
    return list;
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
    d_linked_list_int_t *tail = d_linked_list_get_tail(&list);
    printf("tail is: %d\n", tail->data);
}

void test_d_linked_list_print()
{
    d_linked_list_int_t *list = init_doubly_linked_list();
    printf("full list is: ");
    d_linked_list_int_print(&list);
}

void test_d_linked_list_remove_item()
{
    int to_remove = 5;
    d_linked_list_int_t *list = init_doubly_linked_list();
    printf("before %d removal list is: ", to_remove);
    d_linked_list_int_print(&list);
    d_linked_list_int_remove_item(&list, to_remove);
    printf("after %d removal list is: ", to_remove);
    d_linked_list_int_print(&list);
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
}

void test_d_linked_list_shuffle()
{
    d_linked_list_int_t *list = init_doubly_linked_list();
    printf("List before shuffling: ");
    d_linked_list_int_print(&list);
    d_linked_list_shuffle(&list);
    printf("List after shuffling: ");
    d_linked_list_int_print(&list);
}

//--------------------- SETS ------------------------

set_table_t *init_set()
{
    set_table_t *table = set_table_new(4);
    set_insert(table, "Parma", strlen("Parma"));
    set_insert(table, "Milano", strlen("Milano"));
    set_insert(table, "Firenze", strlen("Firenze"));
    set_insert(table, "Lucca", strlen("Lucca"));
    set_insert(table, "Vicenza", strlen("Vicenza"));
    set_insert(table, "Padova", strlen("Padova"));
    set_insert(table, "Palermo", strlen("Palermo"));
    set_insert(table, "Pisa", strlen("Pisa"));
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

}

void test_set_removal()
{
    set_table_t *table = init_set();
    printf("set collisions = %d\n", table->_collisions);
    set_node_t *found = set_search(table, "Milano", strlen("Milano"));
    int removed = set_remove_key(table, "Milano", strlen("Milano"));
    found = set_search(table, "Milano", strlen("Milano"));
    if(!found)
        printf("Milano key removed\n");
    removed = set_remove_key(table, "Vicenza", strlen("Vicenza"));
    found = set_search(table, "Vicenza", strlen("Vicenza"));
    if(!found)
        printf("Vicenza key removed\n");
    printf("set collisions = %d\n", table->_collisions);
}
//--------------------- DICTIONARY ------------------------

dictionary_t *init_dictionary()
{
    //forcing collisions
    dictionary_t *dict = dictionary_new(2);
    data_t data;
    data.bytes_4 = 8;
    char *string = "byte";
    dictionary_insert(dict, string, strlen(string), data);
    string = "2bytes";
    data.bytes_4 = 16;
    dictionary_insert(dict, string, strlen(string), data);
    string = "4bytes";
    data.bytes_4 = 32;
    dictionary_insert(dict, string, strlen(string), data);
    string = "8bytes";
    data.bytes_4 = 64;
    dictionary_insert(dict, string, strlen(string), data);
    string = "16bytes";
    data.bytes_4 = 128;
    dictionary_insert(dict, string, strlen(string), data);

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
        printf("key = %s, data = %d\n", string, node->data);
    }
    string = "2bytes";
    node = dictionary_search(d, string, strlen(string));
    if(node)
    {
        printf("key = %s, data = %d\n", string, node->data);
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
        printf("key = %s, data = %d\n", string, node->data);
    }
}

void test_dictionary_removal()
{
    dictionary_t *d = init_dictionary();
    printf("set collisions = %d\n", (TO_SET d)->_collisions);
    char *string = "2bytes";
    printf("removing \"%s\" key from dictionary...\n", string);
    int result = dictionary_remove_key(d, string, strlen(string));
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
}