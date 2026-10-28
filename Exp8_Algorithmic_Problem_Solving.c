
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int coinChange(int coins[], int n, int amount) {
    int *dp = malloc((amount + 1) * sizeof(int));

    if (dp == NULL)
        return -1;

    for (int i = 0; i <= amount; i++)
        dp[i] = amount + 1;

    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] > 0 && coins[j] <= i &&
                dp[i - coins[j]] != amount + 1) {
                int temp = dp[i - coins[j]] + 1;

                if (temp < dp[i])
                    dp[i] = temp;
            }
        }
    }

    int ans = dp[amount];
    free(dp);

    if (ans == amount + 1)
        return -1;

    return ans;
}

int singleElement(int a[], int n) {
    int result = 0;

    for (int i = 0; i < n; i++)
        result ^= a[i];

    return result;
}

int canPlace(int a[], int n, int k, int diff) {
    int count = 1;
    int last = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] - last >= diff) {
            count++;
            last = a[i];

            if (count >= k)
                return 1;
        }
    }

    return count >= k;
}

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;

    return 0;
}

int maxMinDifference(int a[], int n, int k) {
    qsort(a, n, sizeof(int), compare);

    int low = 0;
    int high = a[n - 1] - a[0];
    int ans = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canPlace(a, n, k, mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ans;
}

int main() {
    int choice, n, k, a[MAX];

    do {
        printf("\n1. Coin Change Using DP\n");
        printf("2. Single Non-Repeating Element\n");
        printf("3. Maximize Minimum Absolute Difference\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int coins[MAX], amount;

            printf("Enter number of denominations: ");
            scanf("%d", &n);

            if (n < 1 || n > MAX) {
                printf("Invalid size.\n");
                continue;
            }

            printf("Enter denominations: ");
            int valid = 1;

            for (int i = 0; i < n; i++) {
                scanf("%d", &coins[i]);

                if (coins[i] <= 0)
                    valid = 0;
            }

            if (!valid) {
                printf("Denominations must be positive.\n");
                continue;
            }

            printf("Enter amount: ");
            scanf("%d", &amount);

            if (amount < 0 || amount > 1000000) {
                printf("Invalid amount.\n");
                continue;
            }

            int ans = coinChange(coins, n, amount);

            if (ans == -1)
                printf("Change not possible.\n");
            else
                printf("Minimum coins required: %d\n", ans);

        } else if (choice == 2) {
            printf("Enter array size: ");
            scanf("%d", &n);

            if (n < 1 || n > MAX) {
                printf("Invalid size.\n");
                continue;
            }

            printf("Enter elements: ");
            for (int i = 0; i < n; i++)
                scanf("%d", &a[i]);

            printf("Single non-repeating element: %d\n",
                   singleElement(a, n));

        } else if (choice == 3) {
            printf("Enter number of elements: ");
            scanf("%d", &n);

            if (n < 1 || n > MAX) {
                printf("Invalid size.\n");
                continue;
            }

            printf("Enter elements: ");
            for (int i = 0; i < n; i++)
                scanf("%d", &a[i]);

            printf("Enter number of elements to select: ");
            scanf("%d", &k);

            if (k < 2 || k > n) {
                printf("K must be between 2 and n.\n");
                continue;
            }

            printf("Maximum minimum difference: %d\n",
                   maxMinDifference(a, n, k));

        } else if (choice != 0) {
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
