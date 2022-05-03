# include <stdio.h>
# include <stdlib.h>

struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode *root, *test;


struct TreeNode* insert(struct TreeNode* root, int val){
    if (root == NULL)
    {
        root = malloc(sizeof(struct TreeNode));
        root->val = val;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        if (val <= root->val){
            root->left = insert(root->left, val);}
        else{
            root->right = insert(root->right, val);}
    }
    return root;
}

struct TreeNode* search(struct TreeNode* root, int val){
    while (root != NULL && root->val != val)
    {   
        if (val < root->val) {root = root->left;}
        else {root = root->right;}
    }
    return root;
}

struct TreeNode* delete(struct TreeNode* root, int val){
    // Node doesn't exist
    struct TreeNode* x = search(root, val);
    if (x == NULL) {return root;}

    // find Node that is to be deleted and its parent:
    struct TreeNode* del_node = root;
    struct TreeNode* parent = NULL;
    while (del_node != x)
    {
        parent = del_node;
        if (x->val < del_node->val) {del_node = del_node->left;}
        else {del_node = del_node->right;}
    }
    
    // replace del_node with its single child
    if (del_node->right == NULL)
    {   // del_node has only left child
        if (parent == NULL) {root = del_node->left;} // del_node is root
        else if (parent->left == del_node) {parent->left = del_node->left;} // del_node is left child
        else {parent->right = del_node->left;} // dell node is right child
    }
    else if (del_node->left == NULL)
    {   // del_node has only right child
        if (parent == NULL) {root = del_node->right;} // del_node is root
        else if (parent->left == del_node) {parent->left = del_node->right;} // del_node is left child
        else {parent->right = del_node->right;} // del_node is right child
    }
    
    // del_node has two children
    else
    {
        struct TreeNode* largest_left = x->left; // largest element of left subtree of del_node
        struct TreeNode* pre_largest_left = largest_left; // one element before that element

        // find largest element from left subtree of deleted Node
        while (largest_left->right != NULL)
        {
            pre_largest_left = largest_left;
            largest_left = largest_left->right;
        }
        
        // replace del_node with largest ele from left subtree
        if (parent == NULL) {root = largest_left;} // del_node is root
        else if (parent->left == del_node) {parent->left = largest_left;} // del_node is left child
        else {parent->right = largest_left;} // del_node is right child

        largest_left->right = del_node->right; // connect right subtree of del_node to replacement node
        if (largest_left != pre_largest_left) 
        {
            pre_largest_left->right = largest_left->left; // only child of replacement node gets connected to its parent
            largest_left->left = del_node->left; // connect left subtree of del_node to replacement node
        }
    }
    free(del_node);
    return root;
}

void printTree(struct TreeNode* root){
    if (root == NULL) {return;}
    if (root->left != NULL)
    {
        printf("%d -- %d\n", root->val, root->left->val);
        printTree(root->left);
    }
    if (root->right != NULL)
    {
        printf("%d -- %d\n", root->val, root->right->val);
        printTree(root->right);
    }
}



int main(){

    printf("%d", 9/2);
    return 0;
}