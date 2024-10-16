#include <stdbool.h>
#include <stdio.h>



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
    tree t = malloc(sizeof(node));
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
        return t;
    }
    if(get_val(*t) > val){
        insert(&((*t)->right), val);
        return;
    }
    if(get_val(*t) < val){
        insert(&((*t)->left), val);
        return;
    }
}
void print_tree(tree t, int h){
    if(t != NULL){
        print_tree(t->right, h+1);
        for (int i = 0; i<h; i++){
            printf('\t');
        }
        printf("%lf\n", t->val);
        print_tree(t->left, h+1);
    }
}

int count_task(tree t){
    if(t == NULL){
        return 0;
    }
    else if(t->left != NULL || t->right != NULL){
        return 1 + count_task(t->left) + count_task(t->right);
    }
    else{return 0;}
}

void clear_tree(tree t){
    if(t->left == NULL){
        free(t->left);
    }else{
        clear_tree(t->left);
    }

    if(t->right == NULL){
        free(t->right);
    }else{
        clear_tree(t->right);
    }

    free(t);
}
