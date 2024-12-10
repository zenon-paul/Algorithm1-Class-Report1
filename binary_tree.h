#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_
#include<stdio.h>
#include<stdlib.h>
#include"list.h"

struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    void* pointer;
};

typedef struct Node* Tree;

typedef struct tree_list{
	Tree* list;
	int size;
	int len;
}TreeList;

struct Node* create_tree(int key);
void delete_tree(struct Node* node);
void insert_node(Tree* root,Tree node);
Tree extract_max(Tree root);
void delete_node(Tree* root,int key);
void search_pre(Tree root);
void search_pre_with_depth(Tree root,int depth);
void search_middle(Tree root);
void search_post(Tree root);
void print_tree(Tree root);

TreeList* create_treelist(int lim);
void delete_treelist(TreeList* list);
int push_back_treelist(TreeList* list,Tree tree);
void get_key_record(Tree root,List* list);
Tree* get_different_trees(int n);

#endif