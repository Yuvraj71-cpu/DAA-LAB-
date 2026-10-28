
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX 100

void primMST(int graph[MAX][MAX], int n) {
    int parent[MAX], key[MAX], visited[MAX] = {0};
    int total = 0;

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int min = INT_MAX, u = -1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        if (u == -1) {
            printf("Graph is disconnected. MST does not exist.\n");
            return;
        }

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 && !visited[v] &&
                graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Edges in Minimum Spanning Tree:\n");

    for (int i = 1; i < n; i++) {
        printf("%d - %d : %d\n", parent[i] + 1, i + 1, key[i]);
        total += key[i];
    }

    printf("Total MST weight: %d\n", total);
}

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data) {
    struct Node *node = malloc(sizeof(struct Node));

    if (node == NULL)
        exit(1);

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct Node* insertLevelOrder(struct Node *root, int data) {
    struct Node *newNode = createNode(data);

    if (root == NULL)
        return newNode;

    struct Node *queue[MAX];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node *current = queue[front++];

        if (current->left == NULL) {
            current->left = newNode;
            return root;
        } else {
            queue[rear++] = current->left;
        }

        if (current->right == NULL) {
            current->right = newNode;
            return root;
        } else {
            queue[rear++] = current->right;
        }
    }

    return root;
}

int countNodes(struct Node *root) {
    if (root == NULL)
        return 0;

    int leftHeight = 0, rightHeight = 0;
    struct Node *left = root, *right = root;

    while (left != NULL) {
        leftHeight++;
        left = left->left;
    }

    while (right != NULL) {
        rightHeight++;
        right = right->right;
    }

    if (leftHeight == rightHeight)
        return (1 << leftHeight) - 1;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int longestPalindromicSubsequence(char s[]) {
    int n = strlen(s);
    int dp[MAX][MAX];

    if (n == 0)
        return 0;

    for (int i = 0; i < n; i++)
        dp[i][i] = 1;

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;

            if (s[i] == s[j]) {
                dp[i][j] = 2 + (length == 2 ? 0 : dp[i + 1][j - 1]);
            } else {
                dp[i][j] = dp[i + 1][j] > dp[i][j - 1]
                           ? dp[i + 1][j] : dp[i][j - 1];
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    int choice;

    do {
        printf("\n1. Prim's Minimum Spanning Tree\n");
        printf("2. Count Nodes in Complete Binary Tree\n");
        printf("3. Longest Palindromic Subsequence\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int graph[MAX][MAX] = {0};
            int n;

            printf("Enter number of vertices: ");
            scanf("%d", &n);

            if (n < 1 || n > MAX) {
                printf("Invalid number of vertices.\n");
                continue;
            }

            printf("Enter adjacency matrix (0 for no edge):\n");

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    scanf("%d", &graph[i][j]);
            }

            primMST(graph, n);

        } else if (choice == 2) {
            struct Node *root = NULL;
            int n, value;

            printf("Enter number of nodes: ");
            scanf("%d", &n);

            if (n < 0 || n > MAX) {
                printf("Invalid number of nodes.\n");
                continue;
            }

            printf("Enter node values in level order: ");

            for (int i = 0; i < n; i++) {
                scanf("%d", &value);
                root = insertLevelOrder(root, value);
            }

            printf("Total nodes: %d\n", countNodes(root));
            freeTree(root);

        } else if (choice == 3) {
            char s[MAX];

            printf("Enter a string: ");
            scanf("%99s", s);

            printf("Length of Longest Palindromic Subsequence: %d\n",
                   longestPalindromicSubsequence(s));

        } else if (choice != 0) {
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
