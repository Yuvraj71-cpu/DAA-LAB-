
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL)
        exit(1);

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node* insert(struct Node *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

struct Node* search(struct Node *root, int key) {
    while (root != NULL) {
        if (root->data == key)
            return root;

        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
}

struct Node* LCA(struct Node *root, int n1, int n2) {
    while (root != NULL) {
        if (n1 < root->data && n2 < root->data)
            root = root->left;
        else if (n1 > root->data && n2 > root->data)
            root = root->right;
        else
            return root;
    }

    return NULL;
}

struct Info {
    int isBST;
    int size;
    int min;
    int max;
    int largest;
};

struct Info largestBST(struct Node *root) {
    struct Info info;

    if (root == NULL) {
        info.isBST = 1;
        info.size = 0;
        info.min = INT_MAX;
        info.max = INT_MIN;
        info.largest = 0;
        return info;
    }

    struct Info left = largestBST(root->left);
    struct Info right = largestBST(root->right);

    info.size = left.size + right.size + 1;

    if (left.isBST && right.isBST &&
        root->data > left.max && root->data < right.min) {
        info.isBST = 1;
        info.min = root->left ? left.min : root->data;
        info.max = root->right ? right.max : root->data;
        info.largest = info.size;
    } else {
        info.isBST = 0;
        info.min = INT_MIN;
        info.max = INT_MAX;
        info.largest = left.largest > right.largest
                       ? left.largest : right.largest;
    }

    return info;
}

void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node *root = NULL;
    int choice, n, value, n1, n2;

    do {
        printf("\n1. Construct BST\n");
        printf("2. Display BST Inorder\n");
        printf("3. Find Lowest Common Ancestor\n");
        printf("4. Find Largest BST Size\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter number of nodes: ");
            scanf("%d", &n);

            if (n < 0 || n > 1000) {
                printf("Invalid size.\n");
                continue;
            }

            freeTree(root);
            root = NULL;

            printf("Enter values: ");
            for (int i = 0; i < n; i++) {
                scanf("%d", &value);
                root = insert(root, value);
            }

            printf("BST created successfully.\n");

        } else if (choice == 2) {
            printf("Inorder traversal: ");
            inorder(root);
            printf("\n");

        } else if (choice == 3) {
            printf("Enter two node values: ");
            scanf("%d %d", &n1, &n2);

            if (search(root, n1) == NULL ||
                search(root, n2) == NULL) {
                printf("One or both nodes not found.\n");
            } else {
                struct Node *ans = LCA(root, n1, n2);

                if (ans != NULL)
                    printf("Lowest Common Ancestor: %d\n", ans->data);
            }

        } else if (choice == 4) {
            struct Info ans = largestBST(root);
            printf("Size of largest BST: %d\n", ans.largest);

        } else if (choice != 0) {
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    freeTree(root);
    return 0;
}
