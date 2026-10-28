
#include <stdio.h>
#include <string.h>

#define SIZE 100
#define MAX 1000

int table[SIZE];
int used[SIZE];

struct Node {
    int data;
    struct Node *next;
};

struct Node *hashTable[SIZE];

int hashFunction(int key) {
    if (key < 0)
        key = -key;
    return key % SIZE;
}

void chainingInsert(int key) {
    int index = hashFunction(key);
    struct Node *temp = malloc(sizeof(struct Node));

    if (temp == NULL)
        return;

    temp->data = key;
    temp->next = hashTable[index];
    hashTable[index] = temp;
}

void displayChaining() {
    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i] != NULL) {
            printf("%d: ", i);
            struct Node *temp = hashTable[i];

            while (temp != NULL) {
                printf("%d -> ", temp->data);
                temp = temp->next;
            }

            printf("NULL\n");
        }
    }
}

void linearInsert(int key) {
    int index = hashFunction(key);
    int start = index;

    while (used[index]) {
        index = (index + 1) % SIZE;

        if (index == start) {
            printf("Hash table is full.\n");
            return;
        }
    }

    table[index] = key;
    used[index] = 1;
}

void displayLinear() {
    for (int i = 0; i < SIZE; i++) {
        if (used[i])
            printf("%d: %d\n", i, table[i]);
    }
}

void relativeSort(int a[], int n, int b[], int m) {
    int freq[1001] = {0};

    for (int i = 0; i < n; i++) {
        if (a[i] >= 0 && a[i] <= 1000)
            freq[a[i]]++;
    }

    for (int i = 0; i < m; i++) {
        if (b[i] < 0 || b[i] > 1000)
            continue;

        while (freq[b[i]] > 0) {
            printf("%d ", b[i]);
            freq[b[i]]--;
        }
    }

    for (int i = 0; i <= 1000; i++) {
        while (freq[i] > 0) {
            printf("%d ", i);
            freq[i]--;
        }
    }

    printf("\n");
}

void minWindow(char s[], char t[]) {
    int need[256] = {0};
    int window[256] = {0};
    int m = strlen(s), n = strlen(t);

    if (n == 0 || m < n) {
        printf("No window found.\n");
        return;
    }

    for (int i = 0; i < n; i++)
        need[(unsigned char)t[i]]++;

    int left = 0, count = 0;
    int minLen = MAX + 1, start = 0;

    for (int right = 0; right < m; right++) {
        unsigned char c = (unsigned char)s[right];
        window[c]++;

        if (need[c] > 0 && window[c] <= need[c])
            count++;

        while (count == n) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                start = left;
            }

            unsigned char ch = (unsigned char)s[left];
            window[ch]--;

            if (need[ch] > 0 && window[ch] < need[ch])
                count--;

            left++;
        }
    }

    if (minLen == MAX + 1) {
        printf("No window found.\n");
    } else {
        printf("Minimum window: ");
        for (int i = start; i < start + minLen; i++)
            printf("%c", s[i]);
        printf("\n");
    }
}

int main() {
    int choice, n, m, a[MAX], b[MAX];

    do {
        printf("\n1. Hash Table Using Chaining\n");
        printf("2. Hash Table Using Linear Probing\n");
        printf("3. Sort Array by Another Array's Order\n");
        printf("4. Minimum Window Substring\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int k;

            printf("Enter number of elements: ");
            scanf("%d", &n);

            if (n < 1 || n > MAX)
                continue;

            for (int i = 0; i < SIZE; i++)
                hashTable[i] = NULL;

            printf("Enter elements: ");
            for (int i = 0; i < n; i++) {
                scanf("%d", &k);
                chainingInsert(k);
            }

            displayChaining();

        } else if (choice == 2) {
            int k;

            for (int i = 0; i < SIZE; i++)
                used[i] = 0;

            printf("Enter number of elements (1 to 100): ");
            scanf("%d", &n);

            if (n < 1 || n > SIZE)
                continue;

            printf("Enter elements: ");
            for (int i = 0; i < n; i++) {
                scanf("%d", &k);
                linearInsert(k);
            }

            displayLinear();

        } else if (choice == 3) {
            printf("Enter size of first array: ");
            scanf("%d", &n);

            if (n < 1 || n > MAX)
                continue;

            printf("Enter first array (0 to 1000): ");
            for (int i = 0; i < n; i++)
                scanf("%d", &a[i]);

            printf("Enter size of second array: ");
            scanf("%d", &m);

            if (m < 1 || m > MAX)
                continue;

            printf("Enter second array: ");
            for (int i = 0; i < m; i++)
                scanf("%d", &b[i]);

            relativeSort(a, n, b, m);

        } else if (choice == 4) {
            char s[MAX], t[MAX];

            printf("Enter main string: ");
            scanf("%999s", s);

            printf("Enter target string: ");
            scanf("%999s", t);

            minWindow(s, t);

        } else if (choice != 0) {
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
