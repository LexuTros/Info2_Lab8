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
        if (val == root->val) {return root;}
        else if (val < root->val){
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

int inOrderTwArrayBuild(struct TreeNode* root, int A[], int n){
    if (root != NULL)
    {
        n = inOrderTwArrayBuild(root->left, A, n);
        A[n] = root->val;
        n++;
        n = inOrderTwArrayBuild(root->right, A, n);
    }
    return n;
}


struct TreeNode* buildBalancedTree(struct TreeNode* root, int A[], int first, int last){
    if (first > last) {return root;}
    else {
        int m = first + (last - first)/2;
        root = insert(root, A[m]);
        root = buildBalancedTree(root, A, first, m-1);
        root = buildBalancedTree(root, A, m+1, last);
    }
    return root;
}

struct TreeNode* TrimBST(struct TreeNode* root, int low, int high){
    if (root == NULL)
    {
        return NULL;
    }
    if (root->val < low)
    {
        return TrimBST(root->right, low, high);
    }
    if (root->val > high)
    {
        return TrimBST(root->left, low, high);
    }
    root->left = TrimBST(root->left, low, high);
    root->right = TrimBST(root->right, low, high);
    return root;
    
}

int main(){
    struct TreeNode* balanced = NULL;
    int A[9999];
    int n = 0;

    root = insert(root, 4);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 2);
    root = insert(root, 8);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 12);
    root = insert(root, 34);
    root = insert(root, 9);
    root = insert(root, 1);

    printTree(root);
    printf("\n");

    n = inOrderTwArrayBuild(root, A, n);
    balanced = buildBalancedTree(balanced, A, 0, n-1);

    printTree(balanced);
    printf("\n");
    
    balanced = TrimBST(balanced, 3, 9);
    printTree(balanced);
    printf("\n");


    return 0;
}