#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void inputArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// LAB 1 - EXPERIMENT 1a: INSERTION SORT (ITERATIVE)
void insertionSortIterative(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// LAB 1 - EXPERIMENT 1b: INSERTION SORT (RECURSIVE)
void insertionSortRecursive(int arr[], int n) {
    if (n <= 1)
        return;

    insertionSortRecursive(arr, n - 1);

    int last = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = last;
}

// LAB 1 - EXPERIMENT 2: DUTCH NATIONAL FLAG PROBLEM (0-1-2 SORTING)
void dutchNationalFlag(int arr[], int n) {
    int low = 0, mid = 0, high = n - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            swap(&arr[low], &arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            mid++;
        } else {
            swap(&arr[mid], &arr[high]);
            high--;
        }
    }
}

// LAB 1 - EXPERIMENT 3: MAJORITY ELEMENT (MOORE'S VOTING ALGORITHM)
int majorityElement(int arr[], int n) {
    int candidate = arr[0], count = 1;

    for (int i = 1; i < n; i++) {
        if (count == 0) {
            candidate = arr[i];
            count = 1;
        } else if (arr[i] == candidate) {
            count++;
        } else {
            count--;
        }
    }

    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate)
            count++;
    }

    if (count > n / 2)
        return candidate;
    return -1;
}

// LAB 2 - EXPERIMENT 1a: UNION OF TWO SORTED ARRAYS
void unionOfSortedArrays(int arr1[], int n1, int arr2[], int n2) {
    int i = 0, j = 0;
    printf("Union: ");

    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            if (i == 0 || arr1[i] != arr1[i - 1])
                printf("%d ", arr1[i]);
            i++;
        } else if (arr2[j] < arr1[i]) {
            if (j == 0 || arr2[j] != arr2[j - 1])
                printf("%d ", arr2[j]);
            j++;
        } else {
            if (i == 0 || arr1[i] != arr1[i - 1])
                printf("%d ", arr1[i]);
            i++;
            j++;
        }
    }

    while (i < n1) {
        if (i == 0 || arr1[i] != arr1[i - 1])
            printf("%d ", arr1[i]);
        i++;
    }

    while (j < n2) {
        if (j == 0 || arr2[j] != arr2[j - 1])
            printf("%d ", arr2[j]);
        j++;
    }
    printf("\n");
}

// LAB 2 - EXPERIMENT 1b: INTERSECTION OF TWO SORTED ARRAYS
void intersectionOfSortedArrays(int arr1[], int n1, int arr2[], int n2) {
    int i = 0, j = 0;
    printf("Intersection: ");

    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            i++;
        } else if (arr2[j] < arr1[i]) {
            j++;
        } else {
            if (i == 0 || arr1[i] != arr1[i - 1])
                printf("%d ", arr1[i]);
            i++;
            j++;
        }
    }
    printf("\n");
}

// LAB 2 - EXPERIMENT 2: SEARCH IN A ROTATED SORTED ARRAY
int searchRotatedSortedArray(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[low] <= arr[mid]) {
            if (key >= arr[low] && key < arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        } else {
            if (key > arr[mid] && key <= arr[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}

// LAB 2 - EXPERIMENT 3: MERGE SORT
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// LAB 2 - EXPERIMENT 4: COUNT INVERSIONS USING MERGE SORT
long long mergeAndCount(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    long long invCount = 0;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            invCount += (n1 - i);
        }
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
    return invCount;
}

long long countInversions(int arr[], int l, int r) {
    long long invCount = 0;
    if (l < r) {
        int m = l + (r - l) / 2;
        invCount += countInversions(arr, l, m);
        invCount += countInversions(arr, m + 1, r);
        invCount += mergeAndCount(arr, l, m, r);
    }
    return invCount;
}

// LAB 3 - EXPERIMENT 1a: MATRIX MULTIPLICATION (BRUTE FORCE)
void matrixMultiplicationBruteForce(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int **allocateMatrix(int n) {
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = (int *)calloc(n, sizeof(int));
    return mat;
}

void freeMatrix(int **mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void addMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// LAB 3 - EXPERIMENT 1b: STRASSEN'S MATRIX MULTIPLICATION
void strassenMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    int **A11 = allocateMatrix(newSize), **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize), **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize), **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize), **B22 = allocateMatrix(newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    int **M1 = allocateMatrix(newSize), **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize), **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize), **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);
    int **temp1 = allocateMatrix(newSize), **temp2 = allocateMatrix(newSize);

    addMatrix(A11, A22, temp1, newSize);
    addMatrix(B11, B22, temp2, newSize);
    strassenMultiply(temp1, temp2, M1, newSize);

    addMatrix(A21, A22, temp1, newSize);
    strassenMultiply(temp1, B11, M2, newSize);

    subMatrix(B12, B22, temp1, newSize);
    strassenMultiply(A11, temp1, M3, newSize);

    subMatrix(B21, B11, temp1, newSize);
    strassenMultiply(A22, temp1, M4, newSize);

    addMatrix(A11, A12, temp1, newSize);
    strassenMultiply(temp1, B22, M5, newSize);

    subMatrix(A21, A11, temp1, newSize);
    addMatrix(B11, B12, temp2, newSize);
    strassenMultiply(temp1, temp2, M6, newSize);

    subMatrix(A12, A22, temp1, newSize);
    addMatrix(B21, B22, temp2, newSize);
    strassenMultiply(temp1, temp2, M7, newSize);

    int **C11 = allocateMatrix(newSize), **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize), **C22 = allocateMatrix(newSize);

    addMatrix(M1, M4, temp1, newSize);
    subMatrix(temp1, M5, temp2, newSize);
    addMatrix(temp2, M7, C11, newSize);

    addMatrix(M3, M5, C12, newSize);

    addMatrix(M2, M4, C21, newSize);

    subMatrix(M1, M2, temp1, newSize);
    addMatrix(temp1, M3, temp2, newSize);
    addMatrix(temp2, M6, C22, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(M1, newSize); freeMatrix(M2, newSize);
    freeMatrix(M3, newSize); freeMatrix(M4, newSize);
    freeMatrix(M5, newSize); freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    freeMatrix(temp1, newSize); freeMatrix(temp2, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
}

// LAB 3 - EXPERIMENT 3: BINARY SEARCH TO MINIMIZE MAX PAGES ALLOTTED
int isFeasible(int pages[], int n, int students, int maxPages) {
    int requiredStudents = 1;
    int currentSum = 0;

    for (int i = 0; i < n; i++) {
        if (pages[i] > maxPages)
            return 0;

        if (currentSum + pages[i] > maxPages) {
            requiredStudents++;
            currentSum = pages[i];
            if (requiredStudents > students)
                return 0;
        } else {
            currentSum += pages[i];
        }
    }
    return 1;
}

int allocateBooksMinimizeMaxPages(int pages[], int n, int students) {
    int low = 0, high = 0;

    for (int i = 0; i < n; i++) {
        low = (pages[i] > low) ? pages[i] : low;
        high += pages[i];
    }

    int result = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isFeasible(pages, n, students, mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return result;
}

// LAB 3 - EXPERIMENT 4: RANDOMIZED QUICK SORT
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(&arr[randomIndex], &arr[high]);
    return partition(arr, low, high);
}

void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pivotIndex - 1);
        randomizedQuickSort(arr, pivotIndex + 1, high);
    }
}

// LAB 3 - EXPERIMENT 5: MEDIAN OF TWO SORTED ARRAYS
double medianOfTwoSortedArrays(int arr1[], int n1, int arr2[], int n2) {
    if (n1 > n2)
        return medianOfTwoSortedArrays(arr2, n2, arr1, n1);

    int low = 0, high = n1;
    int totalLeft = (n1 + n2 + 1) / 2;

    while (low <= high) {
        int cut1 = low + (high - low) / 2;
        int cut2 = totalLeft - cut1;

        int L1 = (cut1 == 0) ? INT_MIN : arr1[cut1 - 1];
        int L2 = (cut2 == 0) ? INT_MIN : arr2[cut2 - 1];
        int R1 = (cut1 == n1) ? INT_MAX : arr1[cut1];
        int R2 = (cut2 == n2) ? INT_MAX : arr2[cut2];

        if (L1 <= R2 && L2 <= R1) {
            if ((n1 + n2) % 2 == 0)
                return (double)(((L1 > L2) ? L1 : L2) + ((R1 < R2) ? R1 : R2)) / 2.0;
            else
                return (double)((L1 > L2) ? L1 : L2);
        } else if (L1 > R2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }
    return -1.0;
}

void lab1Menu() {
    int choice, n;
    int arr[100];

    printf("\n--- LAB 1: SORTING FUNDAMENTALS ---\n");
    printf("1. Insertion Sort (Iterative)\n");
    printf("2. Insertion Sort (Recursive)\n");
    printf("3. Dutch National Flag Problem (0-1-2 Sorting)\n");
    printf("4. Majority Element in an Array\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter %d elements: ", n);
    inputArray(arr, n);

    switch (choice) {
        case 1:
            insertionSortIterative(arr, n);
            printf("Sorted array: ");
            printArray(arr, n);
            break;
        case 2:
            insertionSortRecursive(arr, n);
            printf("Sorted array: ");
            printArray(arr, n);
            break;
        case 3:
            dutchNationalFlag(arr, n);
            printf("Sorted (0-1-2) array: ");
            printArray(arr, n);
            break;
        case 4: {
            int result = majorityElement(arr, n);
            if (result != -1)
                printf("Majority Element: %d\n", result);
            else
                printf("No Majority Element exists.\n");
            break;
        }
        default:
            printf("Invalid choice.\n");
    }
}

void lab2Menu() {
    int choice;
    printf("\n--- LAB 2: DIVIDE & CONQUER ON ARRAYS ---\n");
    printf("1. Union of Two Sorted Arrays\n");
    printf("2. Intersection of Two Sorted Arrays\n");
    printf("3. Search in a Rotated Sorted Array\n");
    printf("4. Merge Sort\n");
    printf("5. Count Inversions using Merge Sort\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2) {
        int n1, n2, arr1[100], arr2[100];
        printf("Enter size of first sorted array: ");
        scanf("%d", &n1);
        printf("Enter %d elements (sorted): ", n1);
        inputArray(arr1, n1);
        printf("Enter size of second sorted array: ");
        scanf("%d", &n2);
        printf("Enter %d elements (sorted): ", n2);
        inputArray(arr2, n2);

        if (choice == 1)
            unionOfSortedArrays(arr1, n1, arr2, n2);
        else
            intersectionOfSortedArrays(arr1, n1, arr2, n2);

    } else if (choice == 3) {
        int n, key, arr[100];
        printf("Enter size of rotated sorted array: ");
        scanf("%d", &n);
        printf("Enter %d elements: ", n);
        inputArray(arr, n);
        printf("Enter key to search: ");
        scanf("%d", &key);

        int index = searchRotatedSortedArray(arr, n, key);
        if (index != -1)
            printf("Element found at index: %d\n", index);
        else
            printf("Element not found.\n");

    } else if (choice == 4) {
        int n, arr[100];
        printf("Enter number of elements: ");
        scanf("%d", &n);
        printf("Enter %d elements: ", n);
        inputArray(arr, n);

        mergeSort(arr, 0, n - 1);
        printf("Sorted array: ");
        printArray(arr, n);

    } else if (choice == 5) {
        int n, arr[100];
        printf("Enter number of elements: ");
        scanf("%d", &n);
        printf("Enter %d elements: ", n);
        inputArray(arr, n);

        long long inversions = countInversions(arr, 0, n - 1);
        printf("Number of inversions: %lld\n", inversions);
        printf("Sorted array: ");
        printArray(arr, n);

    } else {
        printf("Invalid choice.\n");
    }
}

void lab3Menu() {
    int choice;
    printf("\n--- LAB 3: DIVIDE & CONQUER - MATRICES AND SELECTION ---\n");
    printf("1. Matrix Multiplication (Brute Force)\n");
    printf("2. Strassen's Matrix Multiplication (size must be a power of 2)\n");
    printf("3. Binary Search - Minimize Max Pages Allotted to a Student\n");
    printf("4. Randomized Quick Sort\n");
    printf("5. Median of Two Sorted Arrays\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2) {
        int n;
        printf("Enter size 'n' of the square matrices: ");
        scanf("%d", &n);

        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);

        printf("Enter elements of Matrix A (%d x %d):\n", n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &A[i][j]);

        printf("Enter elements of Matrix B (%d x %d):\n", n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &B[i][j]);

        if (choice == 1)
            matrixMultiplicationBruteForce(A, B, C, n);
        else
            strassenMultiply(A, B, C, n);

        printf("Resultant Matrix C = A x B:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%d ", C[i][j]);
            printf("\n");
        }

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);

    } else if (choice == 3) {
        int n, students, pages[100];
        printf("Enter number of books: ");
        scanf("%d", &n);
        printf("Enter pages in each book: ");
        inputArray(pages, n);
        printf("Enter number of students: ");
        scanf("%d", &students);

        int result = allocateBooksMinimizeMaxPages(pages, n, students);
        printf("Minimized maximum pages allotted: %d\n", result);

    } else if (choice == 4) {
        int n, arr[100];
        printf("Enter number of elements: ");
        scanf("%d", &n);
        printf("Enter %d elements: ", n);
        inputArray(arr, n);

        srand((unsigned int)time(NULL));
        randomizedQuickSort(arr, 0, n - 1);
        printf("Sorted array: ");
        printArray(arr, n);

    } else if (choice == 5) {
        int n1, n2, arr1[100], arr2[100];
        printf("Enter size of first sorted array: ");
        scanf("%d", &n1);
        printf("Enter %d elements (sorted): ", n1);
        inputArray(arr1, n1);
        printf("Enter size of second sorted array: ");
        scanf("%d", &n2);
        printf("Enter %d elements (sorted): ", n2);
        inputArray(arr2, n2);

        double median = medianOfTwoSortedArrays(arr1, n1, arr2, n2);
        printf("Median of the two sorted arrays: %.2lf\n", median);

    } else {
        printf("Invalid choice.\n");
    }
}

int main() {
    int labChoice;

    do {
        printf("\n============================================\n");
        printf(" DESIGN AND ANALYSIS OF ALGORITHMS - LAB MENU\n");
        printf("============================================\n");
        printf("1. Lab 1 - Sorting Fundamentals\n");
        printf("2. Lab 2 - Divide & Conquer on Arrays\n");
        printf("3. Lab 3 - Divide & Conquer: Matrices and Selection\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &labChoice);

        switch (labChoice) {
            case 1:
                lab1Menu();
                break;
            case 2:
                lab2Menu();
                break;
            case 3:
                lab3Menu();
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (labChoice != 0);

    return 0;
}
