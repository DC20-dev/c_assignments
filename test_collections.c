#include "collections.c"
#include "test_collections.h"

int main(int argc, char** argv)
{
    test_linkedList();
    test_dLinkedList();
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
    test_dLinkedList_shuffling();
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