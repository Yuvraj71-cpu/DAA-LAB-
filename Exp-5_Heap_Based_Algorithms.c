
#include <stdio.h>
#include <string.h>

#define MAX 1000

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int a[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[smallest])
        smallest = left;

    if (right < n && a[right] > a[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&a[i], &a[smallest]);
        heapify(a, n, smallest);
    }
}

void heapSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}

void rearrangeString(char s[]) {
    int freq[256] = {0};
    int n = strlen(s);
    char result[MAX];

    for (int i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    int maxFreq = 0, maxChar = 0;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            maxChar = i;
        }
    }

    if (maxFreq > (n + 1) / 2) {
        printf("Rearrangement not possible.\n");
        return;
    }

    int pos = 0;

    while (freq[maxChar] > 0) {
        result[pos] = (char)maxChar;
        pos += 2;
        freq[maxChar]--;
    }

    for (int i = 0; i < 256; i++) {
        while (freq[i] > 0) {
            if (pos >= n)
                pos = 1;

            result[pos] = (char)i;
            pos += 2;
            freq[i]--;
        }
    }

    result[n] = '\0';
    printf("Rearranged string: %s\n", result);
}

void downHeap(int value[], int index[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && value[left] < value[smallest])
        smallest = left;

    if (right < n && value[right] < value[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&value[i], &value[smallest]);
        swap(&index[i], &index[smallest]);
        downHeap(value, index, n, smallest);
    }
}

void mergeKArrays(int a[][MAX], int sizes[], int k) {
    int value[MAX], index[MAX];
    int heapSize = 0;

    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            value[heapSize] = a[i][0];
            index[heapSize] = i;
            heapSize++;
        }
    }

    for (int i = heapSize / 2 - 1; i >= 0; i--)
        downHeap(value, index, heapSize, i);

    printf("Merged array: ");

    while (heapSize > 0) {
        int x = value[0];
        int row = index[0];
        printf("%d ", x);

        static int next[MAX] = {0};
        next[row]++;

        if (next[row] < sizes[row]) {
            value[0] = a[row][next[row]];
            index[0] = row;
        } else {
            value[0] = value[heapSize - 1];
            index[0] = index[heapSize - 1];
            heapSize--;
        }

        if (heapSize > 0)
            downHeap(value, index, heapSize, 0);
    }

    printf("\n");
}

int kthSmallest(int a[], int n, int k) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = 0; i < k - 1; i++) {
        swap(&a[0], &a[n - 1 - i]);
        heapify(a, n - 1 - i, 0);
    }

    return a[0];
}

int main() {
    int choice, n, k, a[MAX];

    do {
        printf("\n1. Heap Sort\n");
        printf("2. Rearrange String\n");
        printf("3. Merge K Sorted Arrays\n");
        printf("4. Kth Smallest Element\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter array size: ");
            scanf("%d", &n);

            if (n < 1 || n > MAX) {
                printf("Invalid size.\n");
                continue;
            }

            printf("Enter elements: ");
            for (int i = 0; i < n; i++)
                scanf("%d", &a[i]);

            heapSort(a, n);

            printf("Sorted array: ");
            for (int i = 0; i < n; i++)
                printf("%d ", a[i]);
            printf("\n");

        } else if (choice == 2) {
            char s[MAX];

            printf("Enter a string without spaces: ");
            scanf("%999s", s);

            rearrangeString(s);

        } else if (choice == 3) {
            int arrays[MAX][MAX], sizes[MAX];

            printf("Enter number of arrays: ");
            scanf("%d", &k);

            if (k < 1 || k > MAX) {
                printf("Invalid number of arrays.\n");
                continue;
            }

            for (int i = 0; i < k; i++) {
                printf("Enter size of array %d: ", i + 1);
                scanf("%d", &sizes[i]);

                if (sizes[i] < 0 || sizes[i] > MAX) {
                    printf("Invalid size.\n");
                    sizes[i] = 0;
                }

                printf("Enter sorted elements: ");
                for (int j = 0; j < sizes[i]; j++)
                    scanf("%d", &arrays[i][j]);
            }

            mergeKArrays(arrays, sizes, k);

        } else if (choice == 4) {
            printf("Enter array size: ");
            scanf("%d", &n);

            if (n < 1 || n > MAX) {
                printf("Invalid size.\n");
                continue;
            }

            printf("Enter elements: ");
            for (int i = 0; i < n; i++)
                scanf("%d", &a[i]);

            printf("Enter K: ");
            scanf("%d", &k);

            if (k < 1 || k > n) {
                printf("Invalid K.\n");
                continue;
            }

            printf("Kth smallest element: %d\n",
                   kthSmallest(a, n, k));

        } else if (choice != 0) {
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
