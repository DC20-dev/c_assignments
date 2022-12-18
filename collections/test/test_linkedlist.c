#define CLOVE_SUITE_NAME LinkedListTest
#include "clove-unit.h"
#include "collections.h"

linked_list_t *list = NULL;

CLOVE_SUITE_SETUP()
{
    int n = -1;
    list = linked_list_create_new(&n, sizeof(int));
    for (int i = 0; i < 20; i++)
    {
        linked_list_t *node = linked_list_create_new(&i, sizeof(int));
        linked_list_append(TO_L_NODE_ADDR &list, TO_L_NODE node);
    }
    
}

CLOVE_SUITE_TEARDOWN()
{
    linked_list_delete(TO_L_NODE_ADDR &list);
}

CLOVE_TEST(linked_list_creation_success)
{
    int n = 10;
    linked_list_t *created_list = linked_list_create_new(&n, sizeof(int));
    CLOVE_PTR_NE(created_list, NULL);
    CLOVE_PTR_EQ(created_list->node, NULL);
    CLOVE_INT_EQ(TO_(int)created_list->data, 10);
    linked_list_delete(TO_L_NODE_ADDR &created_list);
}

CLOVE_TEST(linked_list_get_tail_empty_list)
{
    linked_list_t *empty = NULL;
    linked_list_t *tail = TO_LIST linked_list_get_tail(TO_L_NODE_ADDR &empty);
    CLOVE_PTR_EQ(tail, NULL);
}

CLOVE_TEST(linked_list_get_tail_success)
{
    linked_list_t *tail = TO_LIST linked_list_get_tail(TO_L_NODE_ADDR &list);
    CLOVE_INT_EQ(TO_(int)tail->data, 19);
}

CLOVE_TEST(linked_list_append_success)
{
    int new = 100;
    linked_list_t *last_item = TO_LIST linked_list_append(TO_L_NODE_ADDR &list, TO_L_NODE linked_list_create_new(&new, sizeof(int)));
    CLOVE_PTR_NE(last_item, NULL);
    CLOVE_INT_EQ(TO_(int)last_item->data, 100);
}

CLOVE_TEST(linked_list_get_len_not_empty)
{
    size_t len = linked_list_get_len(TO_L_NODE_ADDR &list);
    CLOVE_LLONG_EQ(len, 21);
}

CLOVE_TEST(linked_list_get_len_empty)
{
    linked_list_t *empty = NULL;
    size_t len = linked_list_get_len(TO_L_NODE_ADDR &empty);
    CLOVE_LLONG_EQ(len, 0);
}

CLOVE_TEST(linked_list_pop_success)
{
    linked_list_t *popped = TO_LIST linked_list_pop(TO_L_NODE_ADDR &list);
    CLOVE_INT_EQ(TO_(int)popped->data, -1);
    linked_list_delete_node(TO_L_NODE popped);
}

CLOVE_TEST(linked_list_pop_empty)
{
    linked_list_t *empty = NULL;
    linked_list_t *popped = TO_LIST linked_list_pop(TO_L_NODE_ADDR &empty);
    CLOVE_PTR_EQ(popped, NULL);
}

CLOVE_TEST(linked_list_dequeue_success)
{
    linked_list_t *dequeued = TO_LIST linked_list_dequeue(TO_L_NODE_ADDR &list);
    CLOVE_INT_EQ(TO_(int)dequeued->data, 19);
    linked_list_delete_node(TO_L_NODE dequeued);
}

CLOVE_TEST(linked_list_dequeue_empty)
{
    linked_list_t *empty = NULL;
    linked_list_t *dequeued = TO_LIST linked_list_dequeue(TO_L_NODE_ADDR &empty);
    CLOVE_PTR_EQ(dequeued, NULL);
}

CLOVE_TEST(linked_list_reverse_success)
{
    linked_list_t *reversed = TO_LIST linked_list_reverse(TO_L_NODE_ADDR &list);
    size_t len = linked_list_get_len(TO_L_NODE_ADDR &list);

    linked_list_t *popped = TO_LIST linked_list_pop(TO_L_NODE_ADDR &reversed);
    CLOVE_INT_EQ(TO_(int)popped->data, 19);
    popped = TO_LIST linked_list_pop(TO_L_NODE_ADDR &reversed);
    CLOVE_INT_EQ(TO_(int)popped->data, 18);
    popped = TO_LIST linked_list_pop(TO_L_NODE_ADDR &reversed);
    CLOVE_INT_EQ(TO_(int)popped->data, 17);
    linked_list_t *dequeued = TO_LIST linked_list_dequeue(TO_L_NODE_ADDR &reversed);
    CLOVE_INT_EQ(TO_(int)dequeued->data, -1);
}

CLOVE_TEST(linked_list_reverse_empty)
{
    linked_list_t *empty = NULL;
    linked_list_t *reversed = TO_LIST linked_list_reverse(TO_L_NODE_ADDR &empty);
    CLOVE_PTR_EQ(reversed, NULL);
}

CLOVE_TEST(linked_list_reverse_one_element)
{
    int new = 69;
    linked_list_t *one_el = linked_list_create_new(&new, sizeof(int));
    linked_list_t *reversed = TO_LIST linked_list_reverse(TO_L_NODE_ADDR &one_el);

    linked_list_t *tail = TO_LIST linked_list_get_tail(TO_L_NODE_ADDR &one_el);
    linked_list_t *head = TO_LIST linked_list_pop(TO_L_NODE_ADDR &one_el);

    CLOVE_PTR_EQ(tail, head);
}

CLOVE_TEST(linked_list_remove_item_success)
{
    int to_remove = 1;
    int removed = linked_list_remove_item(&list, &to_remove, sizeof(int));
    CLOVE_INT_EQ(1, removed);
    linked_list_t *el = TO_LIST linked_list_pop(TO_L_NODE_ADDR &list);
    linked_list_delete_node(TO_L_NODE el);
    el = TO_LIST linked_list_pop(TO_L_NODE_ADDR &list);
    CLOVE_INT_EQ(0,TO_(int) el->data);
    linked_list_delete_node(TO_L_NODE el);
    el = TO_LIST linked_list_pop(TO_L_NODE_ADDR &list);
    CLOVE_INT_EQ(2,TO_(int) el->data);
    linked_list_delete_node(TO_L_NODE el);
}

CLOVE_TEST(linked_list_remove_item_empty_list)
{
    linked_list_t *empty = NULL;
    int to_remove = 1;
    int removed = linked_list_remove_item(&empty, &to_remove, sizeof(int));
    CLOVE_INT_EQ(0, removed);
}

CLOVE_TEST(linked_list_remove_item_not_in_list)
{
    int to_remove = 999;
    int removed = linked_list_remove_item(&list, &to_remove, sizeof(int));
    CLOVE_INT_EQ(0, removed);
}