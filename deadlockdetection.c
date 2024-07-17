#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

bool isSafe(int processes[], int avail[], int req[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int np, int nr) {
    int need[MAX_PROCESSES][MAX_RESOURCES];


    bool finish[MAX_PROCESSES] = {0};
    int safeSeq[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    for (int i = 0; i < nr; i++)
        work[i] = avail[i];


    int count = 0,d;
    while (count < np) {
        bool found = false;
        for (int p = 0; p < np; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < nr; j++)
                    if (req[p][j] > work[j])
                    {
                        d=p;
                        break;
                    }
                if (j == nr) {
                    for (int k = 0; k < nr; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (found == false) {
            printf("Deadlock Detected at processes <",d);
            for (int i=0; i<np; i++)
                if (finish[i] == 0)
                    printf("%d ", i);
            printf(">");
            return false;
        }
    }

    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < np; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

void printResourceAllocationDetails(int np, int nr, int processes[], int req[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int avail[]) {
    printf("\nProcess\t\tAllocation\tRequest\t\tAvailable\n");
    for (int i = 0; i < np; i++) {
        printf("%d\t", processes[i]);

        // Print Allocation
        printf("\t");
        for (int j = 0; j < nr; j++)
            printf("%d ", allot[i][j]);

        // Print Max
        printf("\t\t");
        for (int j = 0; j < nr; j++)
            printf("%d ", req[i][j]);

        // Print Available
        if (i == 0) {
            printf("\t\t");
            for (int j = 0; j < nr; j++)
                printf("%d ", avail[j]);
        }
        printf("\n");
    }
}

int main() {
    int np, nr;
    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter number of resource types: ");
    scanf("%d", &nr);

    int processes[MAX_PROCESSES];
    for (int i = 0; i < np; i++) processes[i] = i;

    int avail[MAX_RESOURCES];
    printf("Enter available resources: ");
    for (int i = 0; i < nr; i++)
        scanf("%d", &avail[i]);

    int req[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter Request matrix:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < nr; j++)
            scanf("%d", &req[i][j]);
    }

    int allot[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter allocation resource matrix:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < nr; j++)
            scanf("%d", &allot[i][j]);
    }

    printResourceAllocationDetails(np, nr, processes, req, allot, avail);

    isSafe(processes, avail, req, allot, np, nr);

    return 0;
}
