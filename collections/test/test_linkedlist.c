#define CLOVE_SUITE_NAME LinkedListTest
#include "clove-unit.h"
#include "collections.h"

CLOVE_SUITE_SETUP()
{

}

CLOVE_TEST(linked_list_creation)
{
    int n = 10;
    linked_list_t *list = linked_list_create_new(&n, sizeof(int));
    CLOVE_PTR_NE(list, NULL);
    CLOVE_PTR_EQ(list->node, NULL);
    CLOVE_INT_EQ(TO_(int)list->data, 10);
}