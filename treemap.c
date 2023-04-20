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


void insertTreeMap(TreeMap * tree, void* key, void * value) {
}

TreeNode * minimum(TreeNode * x){

  while (x->left != NULL) {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
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
    return NULL;
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
        if (tree == NULL || current == NULL) {
        return NULL;
    }

    if (current->right != NULL) {
     
        current = current->right;
        while (current->left != NULL) {
            current = current->left;
        }
        return current->pair;
    } else {
   
        TreeNode * parent = current->parent;
        while (parent != NULL && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
        return (parent == NULL) ? NULL : parent->pair;
    }    if (tree == NULL || current == NULL) {
        return NULL;
    }

    if (current->right != NULL) {
    
        current = current->right;
        while (current->left != NULL) {
            current = current->left;
        }
        return current->pair;
    } else {
    
        TreeNode * parent = current->parent;
        while (parent != NULL && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
        return (parent == NULL) ? NULL : parent->pair;
    }
}
