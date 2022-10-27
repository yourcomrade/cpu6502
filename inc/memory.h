#ifndef MEMORY_H
#define MEMORY_H
/// @brief Implement Memory using AVL tree
#include<stdint.h>

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


extern node*new_node(uint16_t addr, uint8_t val);
extern int max(int a,int b);
extern int getHeight(node*cur);
extern node*left_rotate(node*cur);
extern node*right_rotate(node*cur);
extern int getBalance(node*cur);
extern void balance(node*cur);
extern node*find(mem*my_mem,uint16_t addr);
extern node* insert_node(node*cur,uint16_t addr, uint8_t val);
extern void insert(mem*,uint16_t,uint8_t);
extern node* del_node(node*cur,uint16_t addr);
extern void delete(mem*my_mem,uint16_t addr);
extern void preorder(node*root);
extern void inorder(node*root);
extern void postorder(node*root);
extern void del_all(node*root);
extern char get_val(mem*,uint16_t addr);
#endif