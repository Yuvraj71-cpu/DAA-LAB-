
#include <stdio.h>
#include <string.h>

/* Count substrings containing exactly K even digits */
int countSubstrings(char s[], int k) {
    int n = strlen(s);
    int count = 0;

    for (int i = 0; i < n; i++) {
        int evenDigits = 0;

        for (int j = i; j < n; j++) {
            int digit = s[j] - '0';

            if (digit % 2 == 0)
                evenDigits++;

            if (evenDigits == k)
                count++;
        }
    }

    return count;
}

/* Longest Common Subsequence using Dynamic Programming */
int lcs(char a[], char b[]) {
    int m = strlen(a);
    int n = strlen(b);
    int dp[101][101] = {0};

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else if (dp[i - 1][j] > dp[i][j - 1])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i][j - 1];
        }
    }

    return dp[m][n];
}

int main() {
    char digits[101], a[101], b[101];
    int k;

    printf("Enter a digit string: ");
    scanf("%100s", digits);

    printf("Enter the required number of even digits: ");
    scanf("%d", &k);

    printf("Substrings with exactly %d even digits: %d\n",
           k, countSubstrings(digits, k));

    printf("\nEnter first string: ");
    scanf("%100s", a);

    printf("Enter second string: ");
    scanf("%100s", b);

    printf("Length of Longest Common Subsequence: %d\n",
           lcs(a, b));

    return 0;
}
