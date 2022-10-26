#ifndef TEST_MEM_H
#define TEST_MEM_H
#include "../inc/memory.h"
#include <stdio.h>

void test(mem*my_mem){
    insert(my_mem,0x0001,15);
    insert(my_mem,0x0010,34);
    insert(my_mem,0x0009,23);
    insert(my_mem,0x00f1,21);
    insert(my_mem,0x0032,23);
    insert(my_mem,0x00fe,23);
    insert(my_mem,0x0340,32);
    insert(my_mem,0x0023,23);
    insert(my_mem,0x3400,234);
    insert(my_mem,0x002e,32);
    insert(my_mem,0x0453,23);
    insert(my_mem,0x00a3,12);
    insert(my_mem,0x00fa,45);
    insert(my_mem,0x0003,34);
    printf("\npreorder: \n");
    preorder(my_mem->root);
    printf("\ninorder: \n");
    inorder(my_mem->root);

   // delete(my_mem,0x3400);
    ///(my_mem,0x00a3);
    //delete(my_mem,0x0003);
    printf("\npreorder: \n");
    preorder(my_mem->root);
    printf("\ninorder: \n");
    inorder(my_mem->root);

    del_all(my_mem->root);
}
#endif