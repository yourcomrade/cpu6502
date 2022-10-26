#ifndef MEMORY_H
#define MEMORY_H
/// @brief Implement Memory using AVL tree
#include<stdint.h>
#include "bus.h"
typedef struct node{
    uint8_t value;
    uint16_t address;

    struct node*left;
    struct node*right;
    int height;
}node;
typedef struct mem{
    node*root;
}mem;


node*new_node(uint16_t addr, uint8_t val);
int max(int a,int b);
int getHeight(node*cur);
node*left_rotate(node*cur);
node*right_rotate(node*cur);
int getBalance(node*cur);
void balance(node*cur);
node*find(mem*my_mem,uint16_t addr);
node* insert_node(node*cur,uint16_t addr, uint8_t val);
void insert(mem*,uint16_t,uint8_t);
node* del_node(node*cur,uint16_t addr);
void delete(mem*my_mem,uint16_t addr);
void preorder(node*root);
void inorder(node*root);
void postorder(node*root);
void del_all(node*root);
char get_val(mem*,uint16_t addr);
#endif