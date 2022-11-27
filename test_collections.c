#include "collections.c"
#include "test_collections.h"
#include <string.h>

int main(int argc, char** argv)
{
    test_linkedList();
    test_dLinkedList();
    test_set();
    test_dictionary();
}

// --------------------- linked list ----------------------
void test_linkedList()
{
    printf("\n");
    puts("########## LINKED LIST ##########");
    printf("[test]\n");
    test_linkedList_print();
    printf("[test]\n");
    test_linkedList_get_tail();
    printf("[test]\n");
    test_linkedList_reverse();
    printf("[test]\n");
    test_linkedList_pop();
    printf("[test]\n");
    test_linkedList_dequeue();
    printf("[test]\n");
    test_linkedList_remove_item();
}

LinkedListNode *init_linked_list()
{
    LinkedListInt* list = linkedListInt_create_new(1);
    linkedList_append(TO_NODE &list, TO_NODE linkedListInt_create_new(2));
    linkedList_append(TO_NODE &list, TO_NODE linkedListInt_create_new(3));
    return list;
}

void test_linkedList_print()
{
    LinkedListInt* list = init_linked_list();
    printf("full list is: ");
    linkedListInt_print(TO_NODE &list);
}

void test_linkedList_reverse()
{
    LinkedListInt* list = init_linked_list();
    printf("reversed list is: ");
    list = linkedList_reverse(TO_NODE &list);
    linkedListInt_print(&list);
}

void test_linkedList_get_tail()
{
    LinkedListInt *list = init_linked_list();
    LinkedListInt *tail = linkedList_get_tail(TO_NODE &list);
    printf("tail is = %d\n", tail->data);
}

void test_linkedList_pop()
{
    LinkedListInt* list = init_linked_list();
    printf("before pop list is: ");
    linkedListInt_print(TO_NODE &list);
    linkedList_pop(TO_NODE &list);
    printf("after pop list is: ");
    linkedListInt_print(TO_NODE &list);
}

void test_linkedList_dequeue()
{
    LinkedListInt* list = init_linked_list();
    printf("before dequeue list is: ");
    linkedListInt_print(TO_NODE &list);
    linkedList_dequeue(TO_NODE &list);
    printf("after dequeue list is: ");
    linkedListInt_print(TO_NODE &list);
}

void test_linkedList_remove_item()
{
    int to_remove = 2;
    LinkedListInt* list = init_linked_list();
    printf("before %d removal list is: ", to_remove);
    linkedListInt_print(TO_NODE &list);
    linkedListInt_remove_item(TO_NODE &list, to_remove);
    printf("after %d removal list is: ", to_remove);
    linkedListInt_print(TO_NODE &list);
}
// -----------------doubly linked list ---------------------

DLinkedListNode *init_doubly_linked_list()
{
    DLinkedListNode* list = dLinkedListInt_create_new(9);
    dLinkedList_append(TO_DL_NODE &list, TO_DL_NODE dLinkedListInt_create_new(5));
    dLinkedList_append(TO_DL_NODE &list, TO_DL_NODE  dLinkedListInt_create_new(1));
    return list;
}

void test_dLinkedList()
{
    printf("\n");
    puts("########## DOUBLY LINKED LIST ##########");
    printf("[test]\n");
    test_dLinkedList_print();
    printf("[test]\n");
    test_dLinkedList_get_tail();
    printf("[test]\n");
    test_dLinkedList_remove_item();
    printf("[test]\n");
    test_dLinkedList_insert_before();
    printf("[test]\n");
    test_dLinkedList_insert_after();
    printf("[test]\n");
    test_dLinkedList_shuffle();
}

void test_dLinkedList_get_tail()
{
    DLinkedListInt *list = init_doubly_linked_list();
    DLinkedListInt *tail = dLinkedList_get_tail(&list);
    printf("tail is: %d\n", tail->data);
}

void test_dLinkedList_print()
{
    DLinkedListInt *list = init_doubly_linked_list();
    printf("full list is: ");
    dLinkedListInt_print(&list);
}

void test_dLinkedList_remove_item()
{
    int to_remove = 5;
    DLinkedListInt *list = init_doubly_linked_list();
    printf("before %d removal list is: ", to_remove);
    dLinkedListInt_print(&list);
    dLinkedListInt_remove_item(&list, to_remove);
    printf("after %d removal list is: ", to_remove);
    dLinkedListInt_print(&list);
}

void test_dLinkedList_insert_before()
{
    int to_insert = 10, before_this = 5;
    DLinkedListInt *list = init_doubly_linked_list();
    DLinkedListInt *item = dLinkedListInt_create_new(to_insert);
    printf("inserting %d before %d\n", to_insert, before_this);
    dLinkedListInt_insert_before(&list, item, before_this);
    printf("list after insertion is: ");
    dLinkedListInt_print(&list);
}

void test_dLinkedList_insert_after()
{
    int to_insert = 10, after_this = 5;
    DLinkedListInt *list = init_doubly_linked_list();
    DLinkedListInt *item = dLinkedListInt_create_new(to_insert);
    printf("inserting %d after %d\n", to_insert, after_this);
    dLinkedListInt_insert_after(&list, item, after_this);
    printf("list after insertion is: ");
    dLinkedListInt_print(&list);
}

void test_dLinkedList_shuffle()
{
    DLinkedListInt *list = init_doubly_linked_list();
}

//--------------------- SETS ------------------------

SetTable *init_set()
{
    SetTable *table = set_table_new(4);
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
    SetTable *table = init_set();
    char *string = "Milano";
    SetNode *found = set_search(table, string, strlen(string));

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
    SetTable *table = init_set();
    printf("set collisions = %d\n", table->_collisions);
    SetNode *found = set_search(table, "Milano", strlen("Milano"));
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

Dictionary *init_dictionary()
{
    //forcing collisions
    Dictionary *dict = dictionary_new(2);
    Data data;
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
    Dictionary *d = init_dictionary();
    char *string = "byte";
    DictionaryNode* node = dictionary_search(d, string, strlen(string));
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
    Dictionary *d = init_dictionary();
    printf("set collisions = %d\n", (TO_SET d)->_collisions);
    char *string = "2bytes";
    printf("removing \"%s\" key from dictionary...\n", string);
    int result = dictionary_remove_key(d, string, strlen(string));
    printf("removal ended with %d\n", result);
    DictionaryNode *node = dictionary_search(d, string, strlen(string));
    if(node)
    {
        printf("\"%s\" key found\n", (TO_SET_NODE node)->key);
    }
    else{
        printf("\"%s\" key removed successfully!\n", string);
    }
    printf("set collisions = %d\n", (TO_SET d)->_collisions);
}