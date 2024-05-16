#include <stdio.h>
#include <stdlib.h>

// 假设树中空节点用 -1 表示
char buf[50] ={'A', 'B', 'C', 'D', 'E', 'F', NULL, 'G', 'H', NULL, NULL, NULL, NULL, 'I'};


// 定义树的结点
typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 创建二叉树
TreeNode* createBinaryTree(int index) {
    // 如果遇到空节点或者超出数组范围，则返回 NULL
    if (index >= 50 || buf[index] == -1)
        return NULL;
    
    // 创建当前节点
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = buf[index];
    node->left = NULL;
    node->right = NULL;

    // 递归创建左右子树
    node->left = createBinaryTree(2 * index + 1);
    node->right = createBinaryTree(2 * index + 2);

    return node;
}

// 层序遍历
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL)
        return;

    // 创建一个队列
    TreeNode* queue[50];
    int front = 0, rear = 0;
    
    // 根节点入队
    queue[rear++] = root;

    // 遍历队列中的节点
    while (front != rear) {
        // 出队一个节点
        TreeNode* current = queue[front++];
        printf("%c ", current->data);

        // 将当前节点的左右子节点入队
        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

int main() {
    // 创建二叉树
    TreeNode* root = createBinaryTree(0);
    
    // 层序遍历
    printf("层序遍历结果：");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}


/*
         A
       /   \
      B     C
     / \   / 
    D  E  F 
   / \     \
  G   H     I 
            
*/