#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"
 
typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lt) (void* key1, void* key2)) {
  TreeMap * map = (TreeMap *) malloc(sizeof(TreeMap));
  map->root = NULL;
  map->lower_than = lt;
  return map;
}


void insertTreeMap(TreeMap* tree, void* key, void* value) {
    if (tree->root == NULL) {
    tree->root = createTreeNode(key, value);
      
    } else
    {
      tree->current = tree->root;
      while (tree->current) {
      if (is_equal(tree, tree->current->pair->key, key)) {
      return;
      }
        if (tree->lower_than(tree->current->pair->key, key)) {
        if (!tree->current->right) {
        tree->current->right = createTreeNode(key, value);
        tree->current->right->parent = tree->current;
        tree->current = tree->current->right;
        return;
        }
        tree->current = tree->current->right;
        } else {
            if (!tree->current->left) {
              tree->current->left = createTreeNode(key, value);
              tree->current->left->parent = tree->current;
              tree->current = tree->current->left;
               return;
              }
            tree->current = tree->current->left;
          }
      }
    }  
}

TreeNode * minimum(TreeNode * x){

  while (x->left != NULL) {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node->left == NULL && node->right == NULL) {
        if (node->parent == NULL) {
            tree->root = NULL;
        } else if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        free(node);
    }

    else if (node->left == NULL || node->right == NULL) {
        TreeNode* child = node->left != NULL ? node->left : node->right;
        child->parent = node->parent;
        if (node->parent == NULL) {
            tree->root = child;
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        free(node);
    }

   // else {
   // TreeNode* successor = minimum(node->right);
    //node->key = successor->key;
   // node->value = successor->value;
   // node->balance = successor->balance;
   // removeNode(tree, successor);
   // }

}


void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;
  if(tree->root == NULL)return NULL;
  
  while(tree->current != NULL)
    {
      if(is_equal(tree, tree->current->pair->key, key)){
        return(tree->current->pair);
      }
  if (tree -> lower_than(tree->current->pair->key, key))
  {
    tree->current = tree->current->right;
  }
      else{
        tree->current = tree->current->left;
      }
      
    }
  

return NULL;
  
}


Pair * upperBound(TreeMap * tree, void* key) {
    TreeNode* current = tree->root;
    TreeNode* ub_node = NULL;

    while (current != NULL) {
        if (tree->lower_than(key, current->pair->key) < 0) {
            ub_node = current;
            current = current->left;
        }
        else if (tree->lower_than(key, current->pair->key) > 0) {
            current = current->right;
        }
        else {
            return current->pair;
        }
    }

    if (ub_node != NULL) {
        return ub_node->pair;
    }
    else {
        return NULL;
    }
}


Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    TreeNode * current = tree->root;
    while (current->left != NULL) {
        current = current->left;
    }

    return current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
 if (tree == NULL || tree->root == NULL) {
        return NULL; 
    }

    TreeNode *current = tree->root;

    if (current->right != NULL) {
        current = current->right;
        while (current->left != NULL) {
            current = current->left;
        }
        return current->pair;
    } else {
        TreeNode *parent = current->parent;
        while (parent != NULL && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
        if (parent != NULL) {
            return parent->pair;
        } else {
            return NULL; 
        }
    }

}
