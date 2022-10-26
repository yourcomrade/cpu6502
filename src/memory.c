#ifndef MEM_C
#define MEM_C
#include "../inc/memory.h"
#include <stdlib.h>
#include<stdio.h>
/// @brief Create new block of memory
/// @pamem addr 
/// @pamem val 
/// @return new block
node*new_node(uint16_t addr,uint8_t val){
    node*new_one=(node*)(malloc(sizeof(node)));
    if(new_one==NULL){
        perror("\nError, cannot create new block of memory");
        return NULL;
    }
    else{
        new_one->address=addr;
        new_one->value=val;
        new_one->left=NULL;
        new_one->right=NULL;
        new_one->height=0;
        return new_one;
    }
}
int max(int a,int b){
    return (a>b)?a:b;
}
int getHeight(node*cur){
    if(cur==NULL){
        return 0;
    }
    else{
        return 1+max(getHeight(cur->left), getHeight(cur->right));
    }
}
node*left_rotate(node*cur){

    node*rig_child=cur->right;
    cur->right=rig_child->left;
    rig_child->left=cur;
    ///Update height
    cur->height= getHeight(cur);
    rig_child->height= getHeight(rig_child);
    return rig_child;
}
node*right_rotate(node*cur){
    node*left_child=cur->left;
    cur->left=left_child->right;
    left_child->right=cur;
    ///Update height
    cur->height= getHeight(cur);
    left_child->height= getHeight(left_child);
    return left_child;
}

int getBalance(node*cur){
    if(cur!=NULL){
        return getHeight(cur->left)- getHeight(cur->right);
    }
    else{
        return 0;
    }
}


node*find(mem*my_mem,uint16_t addr){
    node*cur=my_mem->root;
    while(cur!=NULL){
        if(cur->address==addr){
            return cur;
        }
        else if(cur->address>addr){
            cur=cur->left;
        }
        else{
            cur=cur->right;
        }
    }
    return cur;
}
node* insert_node(node*cur,uint16_t addr, uint8_t val){
    if(cur==NULL){
        return new_node(addr,val);
    }
    else if(cur->address>addr){
        cur->left= insert_node(cur->left,addr,val);
    }
    else{
        cur->right= insert_node(cur->right,addr,val);
    }
    ///Update height of parent node
    cur->height= getHeight(cur);
    int bal= getBalance(cur);///Get balance factor
    if(bal>1 && getBalance(cur->left)>=1){
        ///Right right case
        return right_rotate(cur);
    }
    else if(bal>1 && getBalance(cur->left)<=-1){
        ///Left right case
        cur->left= left_rotate(cur->left);
        return right_rotate(cur);
    }
    else if(bal<-1 && getBalance(cur->right)<=-1){
        ///Left left case
        return left_rotate(cur);
    }
    else if(bal<-1 && getBalance(cur->right)>=1){
        ///Right left case
        cur->right= right_rotate(cur->right);
        return left_rotate(cur);
    }
    else{
        return cur;
    }
}
void insert(mem*my_mem,uint16_t addr,uint8_t val){
    node*res= find(my_mem,addr);
    if(res==NULL)
    my_mem->root= insert_node(my_mem->root,addr,val);
    else{
        res->value=val;
    }
}
node* del_node(node*cur,uint16_t addr){
  if(cur==NULL){
      return NULL;
  }
  else if(cur->address>addr){
      cur->left= del_node(cur->left,addr);
  }
  else if(cur->address<addr){
      cur->right= del_node(cur->right,addr);
  }
  else {
      /// We found the node to delete

      ///no child
      if(cur->right==NULL&& cur->left==NULL) {
          free(cur);
          cur=NULL;
          return cur;
      }
      else if(cur->right==NULL && cur->left!=NULL){
          ///Only have left 1 child
          node*temp=cur->left;
          free(cur);
          cur=temp;
      }
      else if(cur->right!=NULL&&cur->left==NULL){
          ///Only have right child
          node*temp=cur->right;
          free(cur);
          cur=temp;
      }
      else{
          ///Having 2 children
          node*rep=cur->right;
          ///Find the subtitue node
          while(rep!=NULL){
              if(rep->left!=NULL){
                  rep=rep->left;
              }
              else{
                  break;
              }
          }
         cur->value=rep->value;
         cur->address=rep->address;
         ///Delete the replace node
         cur->right= del_node(cur->right,cur->address);
      }
  }
  cur->height= getHeight(cur);///Update height
    int bal= getBalance(cur);///Get balance factor
    if(bal>1 && getBalance(cur->left)>=1){
        ///Right right case
        return right_rotate(cur);
    }
    else if(bal>1 && getBalance(cur->left)<=-1){
        ///Left right case
        cur->left= left_rotate(cur->left);
        return right_rotate(cur);
    }
    else if(bal<-1 && getBalance(cur->right)<=-1){
        ///Left left case
        return left_rotate(cur);
    }
    else if(bal<-1 && getBalance(cur->right)>=1){
        ///Right left case
        cur->right= right_rotate(cur->right);
        return left_rotate(cur);
    }
    else{
        return cur;
    }
}

void delete(mem*my_mem,uint16_t addr){
    node*res= find(my_mem,addr);
    if(res!=NULL)
    my_mem->root= del_node(my_mem->root,addr);
    else
    {
        printf("\nError Segmentation Fault");
    }
}
void preorder(node*root){
    if(root!=NULL){
        printf("{addr: %d, val: %d}",root->address,root->value);
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(node*root){
    if(root!=NULL){
        inorder(root->left);
        printf(" {addr: %d, val: %d}",root->address,root->value);
        inorder(root->right);
    }
}
void postorder(node*root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf(" {addr: %d, val: %d}",root->address,root->value);       
    }
}
void del_all(node*root){
    if(root!=NULL){
        del_all(root->left);
        del_all(root->right);
        free(root);
    }
}
char get_val(mem*my_mem,uint16_t addr){
    node*res= find(my_mem,addr);
    if(res==NULL){
        return 0;
    }
    else{
        return res->value;
    }
}

#endif