#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  p->root =  p->nil;  //root의 자식 어떻게 설정?
  p->root->color = RBTREE_BLACK;

  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

static void left_rotate(rbtree *t, node_t *x){
  // x->right != t.nil 가정, root부모 nil로 해야 함
  node_t *y = x->right;
  x->right = y->left;
  if(y->left != t->nil){
    y->left->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->nil){
    t->root = y;
  }
  else if (x == x->parent->left){
    x->parent->left = y;
  }
  else x->parent->right = y;
  y->left = x;
  x->parent = y;
}

static void right_rotate(rbtree *t, node_t *y){
  // y->left != t.nil 가정
  node_t *x = y->left;
  y->left = x->right;
  if(x->right != t->nil){
    x->right->parent = y;
  }
  x->parent = y->parent;
  if(y->parent == t->nil){
    t->root = x;
  }
  else if (y == y->parent->left){
    y->parent->left = x;
  }
  else y->parent->right = x;
  x->right = y;
  y->parent = x;
}

static void rbtree_insert_fixup(rbtree *t, node_t *z){ 
              //z = fixup position node
  node_t *y;  //y = search node
  while(z->parent->color == RBTREE_RED){
    if(z->parent == z->parent->parent->left){
      y = z->parent->parent->right;
      if(y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else{
        if (z == z->parent->right){
          z = z->parent;
          left_rotate(t,z);
        }
        z->parent->color == RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t,z->parent->parent);
      }
    }
    else{
      while(0); // right - left 교환하여 작성
    }
  }
  t->root->color == RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  //노드의 key값이 채워져있다고 가정
  node_t *y = t->nil;   //y   = parent node
  node_t *x = t->root;  //x   = search /insert position node
  node_t *z;            //z   = insert node
  z->key = key;         //key = insert key
  while(x != t->nil){
    y = x;
    if( z->key < x->key){
      x = x->left;
    }
    else x = x->right;
  }
  z->parent = y;
  if (y == t->nil){
    t->root = z;
  }
  else if (z->key < y->key){
    y->left = z;
  }
  else y->right = z;
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  rbtree_insert_fixup(t,z);
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
