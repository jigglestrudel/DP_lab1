#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"

// hash_t f_hash(data_t *);			funkcja hashująca
// int{-1, 0, 1} f_comp(hash_t *, hash_t *)	funckja porównująca
// void f_print()				funkcja wyświetlająca

/*
typedef struct my_text
{
    const char* string;
}my_text_t;


void list_testing(list_t* test_list)
{
    node_t* node = test_list->head;
    for (int i = 0; i < test_list->size; i++)
    {
        printf("%p: %s\n", node, ((my_text_t*)(node->content))->string);
        node = node->next;
    }
}
*/

hash_t f_digit_sum(key_t key)
{
    hash_t hash = 0;
    while (key != 0)
    {
        hash += key % 10;
        key /= 10;
    }
    return hash;
}

int f_integer_comparison(hash_t left, hash_t right)
{
    if (left < right) return -1;
    if (left == right) return 0;
    return 1;
}

int main()
{
    /*
    printf("Hello, World!\n");
    printf("Creating a new list\n");
    list_t* test_list = f_list_constructor();
    printf("List: size:%d\n", test_list->size);

    printf("Creating some elements\n");
    my_text_t* s1 = (my_text_t*)malloc(sizeof(my_text_t));
    s1->string = "Hello";
    my_text_t* s2 = (my_text_t*)malloc(sizeof(my_text_t));
    s2->string = "World";
    my_text_t* s3 = (my_text_t*)malloc(sizeof(my_text_t));
    s3->string = "!!!";
    printf("insert front\n");
    f_list_insert_front(test_list, s1);
    printf("List: size:%d\n", test_list->size);
    printf("testing...\n");
    list_testing(test_list);
    printf("insert_back\n");
    f_list_insert_back(test_list, s3);
    printf("List: size:%d\n", test_list->size);
    printf("testing...\n");
    list_testing(test_list);
    printf("insert after head\n");
    f_list_insert_after(test_list, s2, test_list->head);
    printf("List: size:%d\n", test_list->size);
    printf("testing...\n");
    list_testing(test_list);

    printf("removing middle element\n");
    f_list_remove(test_list, test_list->head->next);
    printf("List: size:%d\n", test_list->size);
    printf("testing...\n");
    list_testing(test_list);

    printf("Deconstruction\n");
    f_list_destructor(test_list);

    */

    const char* text = "HELLO";

    hashmap_t* test_hashmap = f_hashmap_constructor(f_digit_sum, f_integer_comparison);

    f_hashmap_print(test_hashmap);
    printf("================ADDING AN ELEMTN=================\n");
    f_hashmap_add(test_hashmap, 1, text);
    f_hashmap_print(test_hashmap);

    printf("VALUE AT KEY 1: %s\n", (char*)(f_hashmap_find(test_hashmap, 1)));

    printf("================REMOVING THE ELEMENT=================\n");
    f_hashmap_remove(test_hashmap, 1);
    f_hashmap_print(test_hashmap);

    printf("================ADDING AN ELEMTN=================\n");
    f_hashmap_add(test_hashmap, 1, text);
    f_hashmap_print(test_hashmap);

    printf("================ADDING AN ELEMTN=================\n");
    f_hashmap_add(test_hashmap, 11, text);
    f_hashmap_print(test_hashmap);

    printf("================ADDING AN ELEMTN=================\n");
    f_hashmap_add(test_hashmap, 2, text);
    f_hashmap_print(test_hashmap);


    f_hashmap_destructor(test_hashmap);
    return 0;
}
