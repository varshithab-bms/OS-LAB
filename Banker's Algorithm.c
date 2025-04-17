#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m, i, j, k;
    int alloc[MAX][MAX], max[MAX][MAX], avail[MAX], need[MAX][MAX];
    int finish[MAX] = {0}, safeSeq[MAX], work[MAX];


    printf("Enter number of processes and resources:\n");
    scanf("%d %d", &n, &m);

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter maximum matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available matrix:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for (i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;
    bool found;

    while (count < n) {
        found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m) {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found)
            break;
    }

    if (count == n) {
        printf("System is in safe state\n");
        printf("Safe sequence is: ");
    for (i = 0; i < n; i++) {
    printf("P%d", safeSeq[i]);
    if (i != n - 1)
        printf(" -> ");
     }

        printf("\n");
    } else {
        printf("System is in unsafe state\n");
    }

    return 0;
}
