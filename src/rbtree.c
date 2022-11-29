#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  // nil 만들기( 메모리, 색상부여 )
  nil->color = RBTREE_BLACK;
  // TODO: initialize struct if needed
  p->nil = nil;
  p->root = nil;  // root의 자식 어떻게 설정?
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

static void left_rotate(rbtree *t, node_t *x) {
  // x->right != t.nil 가정, root부모 nil로 해야 함
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

static void right_rotate(rbtree *t, node_t *y) {
  // y->left != t.nil 가정
  node_t *x = y->left;
  y->left = x->right;
  if (x->right != t->nil) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == t->nil) {
    t->root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else
    y->parent->right = x;
  x->right = y;
  y->parent = x;
}

static void rbtree_insert_fixup(rbtree *t, node_t *z) {
  // z = fixup position node
  node_t *y;  // y = uncle node
  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->parent->left) {
      // z의 parent가 왼쪽트리일 경우
      y = z->parent->parent->right;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    } else {
      // z의 parent가 오른쪽트리일 경우
      y = z->parent->parent->left;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  //노드의 key값이 채워져있다고 가정
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  node_t *y = t->nil;   // y   = parent node
  node_t *x = t->root;  // x   = search /insert position node
  z->key = key;         // key = insert key
  while (x != t->nil) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else
      x = x->right;
  }
  z->parent = y;
  if (y == t->nil) {
    t->root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else
    y->right = z;
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  rbtree_insert_fixup(t, z);
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *x;  // search node
  node_t *y;  //   node
  x = t->root;
  y = x;
  while (x != t->nil) {
      y = x;
      if (x->key > key) {
        x = x->right;
      } else if (x->key < key) {
        x = x->left;
      } else
        break;
  }
  return y;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *x;
  x = t->root;
  if (x == t->nil)
  {
    return NULL;
  }
  while (x->left != t->nil){
    x = x->left;
  }
  return x;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *x;
  x = t->root;
  if (x == t->nil)
  {
    return NULL;
  }
  while (x->right != t->nil){
    x = x->right;
  }
  return x;
}

node_t *subtree_min(node_t *x, const rbtree *t) {
  // TODO: implement find
  // x노드 찾고나서, 최소/최댓값(find 활용?)
  // node_t *x; = search node
  node_t *y;  //find node
  x = rbtree_find(t, x->key);
  y = x;
  while(x != t->nil){
    y = x;
    x = x->left; // 이거 맞어?
  }
  return y;
}

node_t *subtree_max(node_t *x, const rbtree *t) {
  // TODO: implement find
  // x노드 찾고나서, 최소/최댓값(find 활용?)
  // node_t *x; = search node
  node_t *y;  //find node
  x = rbtree_find(t, x->key);
  y = x;
  while(x != t->nil){
    y = x;
    x = x->right; // 이거 맞어?
  }
  return y;
}

static void rbtree_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil) {
    t->root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else
    u->parent->right = v;
  v->parent = u->parent;
}

static void rbtree_erase_fixup(rbtree *t, node_t *x) {
  node_t *w;
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t,x->parent);
        w = x->parent->right;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{
        if (w->right->color == RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t,w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t,x->parent);
        x = t->root;
      }
    }
    else{
      w = x->parent->left;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t,x->parent);
        w = x->parent->left;
      }
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{
        if (w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t,w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t,x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  node_t *y = z;
  node_t *x;
  color_t y_ori_color = y->color;
  if (z->left == t->nil) {
    x = z->right;
    rbtree_transplant(t, z, z->right);
  } else if (z->right == t->nil) {
    x = z->left;
    rbtree_transplant(t, z, z->left);
  } else {
    y = subtree_min(z->right, t);
    y_ori_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      rbtree_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rbtree_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (y_ori_color == RBTREE_BLACK) rbtree_erase_fixup(t, x);
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
