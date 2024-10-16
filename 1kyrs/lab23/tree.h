#ifndef TREE
#define TREE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct node node;

struct node
{
    double val;
    node* left;
    node* right;
};

typedef node* tree;

tree create_tree(){
    return NULL;
}

void destroy_tree(tree t){
    free(t);
}

tree build_tree(tree left, tree right, double val){
    tree t = (tree) malloc(sizeof(node));
    t->left = left;
    t->right = right;
    t->val = val;
    return t;
}

bool tree_is_empty(tree t){
    return t == NULL;
}

double get_val(tree t){
    return t->val;
}

tree get_left(tree t){
    return t->left;
}

tree get_right(tree t){
    return t->right;
}

tree insert(node** t, double val){
    if(*t == NULL){
        *t = build_tree(NULL, NULL, val);
        return *t;
    }
    if(get_val(*t) > val){
        insert(&((*t)->right), val);
    }
    if(get_val(*t) < val){
        insert(&((*t)->left), val);
    }
}

void print_tree(tree t, int h){
    if(t != NULL){
        print_tree(t->right, h+1);
        for (int i = 0; i<h; i++){
            printf("\t");
        }
        printf("%lf\n", t->val);
        print_tree(t->left, h+1);
    }
}

tree node_remove(tree t, double val){
    if(t == NULL){
        printf("can`t find the value %lf\n", val);
        return t;
    }
    else if(val < t->val){
        t->right = node_remove(t->right, val);
    }
    else if(val > t->val){
        t->left = node_remove(t->left, val);
    }
    else{
        tree tmp;
        if(t->left == NULL){
            tmp = t->right;
            free(t);
            return tmp;
        }else if(t->right == NULL){
            tmp = t->left;
            free(t);
            return tmp;
        }
        tmp = t->left;
        while(tmp->right != NULL){
            tmp = tmp->right;
        }
        t->val = tmp->val;
        t->left = node_remove(t->left, tmp->val);
    }
    return t;
}

int count_task(tree t){
    if(t == NULL){
        return 0;
    }
    else if(t->left != NULL || t->right != NULL){
        return (1 + count_task(t->left) + count_task(t->right));
    }
    else{return 0;}
}

void clear_tree(tree t){
    if(t == NULL){
        return;
    }
    clear_tree(t->left);
    clear_tree(t->right);
    free(t);
}

tree find_and_destroy(tree t, double val){
    if(val < t->val){
        if(t->right == NULL){
            printf("NOTFOUND");
            return t;
        }
        if(val == t->right->val){
            clear_tree(t->right);
            t->right = NULL;
            return t;
        }else{
            t->right = find_and_destroy(t->right, val);
        }
    }
    else if(val > t->val){
        if(t->left == NULL){
            printf("NOTFOUND");
            return t;
        }
        if(val == t->left->val){
            clear_tree(t->left);
            t->left = NULL;
            return t;
        }else{
            t->left = find_and_destroy(t->left, val);
        }
    }else{
        clear_tree(t);
        return NULL;
    }
}

#endif