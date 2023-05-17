#include <stdio.h>
#include <omp.h>

struct node {
    int data;
    struct node *left, *right; 
} *root;

struct node* minValueNode(struct node* node){ 
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

void inorder_serial(struct node* root){ 
    if(root->left != NULL)
        inorder_serial(root->left);
    //printf("%d ", root->data); 
    if(root->right != NULL)
        inorder_serial(root->right); 
}

void inorder_parallel(struct node* root){ 
    if(root->left != NULL)
        #pragma omp task
        inorder_parallel(root->left);
    //#pragma omp taskwait
    //printf("%d ", root->data); 
    if(root->right != NULL)
        #pragma omp task
        inorder_parallel(root->right);
}

void preorder_serial(struct node* root){
    //printf("%d ", root->data); 
    if(root->left != NULL)
        preorder_serial(root->left);
    if(root->right != NULL)
        preorder_serial(root->right); 
}

void preorder_parallel(struct node* root){
    //#pragma omp taskwait
    //printf("%d ", root->data);
    if(root->left != NULL)
        #pragma omp task
        preorder_parallel(root->left); 
    if(root->right != NULL)
        #pragma omp task
        preorder_parallel(root->right);
}

void postorder_serial(struct node* root){ 
    if(root->left != NULL)
        postorder_serial(root->left); 
    if(root->right != NULL)
        postorder_serial(root->right);
    //printf("%d ", root->data);
}

void postorder_parallel(struct node* root){ 
    if(root->left != NULL)
        #pragma omp task
        postorder_parallel(root->left); 
    if(root->right != NULL)
        #pragma omp task
        postorder_parallel(root->right);
    //#pragma omp taskwait
    //printf("%d ", root->data);
}

struct node* insertNode(struct node* root, int y){ 
    if (root == NULL) {
        struct node* t = (struct node*) malloc(sizeof(struct node)); t->data = y;
        t->left = t->right = NULL;
        return t;
    }
    if (y < root->data)
        root->left = insertNode(root->left, y);
    else if (y > root->data)
        root->right = insertNode(root->right, y);
    return root;
}

int main(){
    printf("Binary Tree Traversal\n\n");
    double start, end;
    struct node* root = NULL;
    root = insertNode(root, 0);
    
    for (int i = 1; i < 100000; i++) {
        insertNode(root, i);
    }

    start = omp_get_wtime();
    inorder_serial(root);
    end = omp_get_wtime();
    printf("Time taken for serial inorder: %f\n", end - start);

    start = omp_get_wtime();
    #pragma omp parallel 
    {
        #pragma omp single
        inorder_parallel(root);
    }
    end = omp_get_wtime();
    printf("Time taken for parallel inorder: %f\n\n", end - start);

    start = omp_get_wtime();
    inorder_serial(root);
    end = omp_get_wtime();
    printf("Time taken for serial preorder: %f\n", end - start);

    start = omp_get_wtime();
    #pragma omp parallel 
    {
        #pragma omp single
        inorder_parallel(root);
    }
    end = omp_get_wtime();
    printf("Time taken for parallel preorder: %f\n\n", end - start);

    start = omp_get_wtime();
    inorder_serial(root);
    end = omp_get_wtime();
    printf("Time taken for serial postorder: %f\n", end - start);

    start = omp_get_wtime();
    #pragma omp parallel 
    {
        #pragma omp single
        inorder_parallel(root);
    }
    end = omp_get_wtime();
    printf("Time taken for parallel postorder: %f\n", end - start);
}