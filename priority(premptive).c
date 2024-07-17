#include <stdio.h>
#include <stdbool.h>

// Function to find the waiting time, turnaround time, and completion time for all processes using Priority Scheduling (Preemptive)
void findCompletionTime(int processes[], int n, int bt[], int at[], int wt[], int tat[], int ct[], int rt[], int priority[], bool isLowerPriorityHigher)
{
    int remaining[n]; // Array to store remaining burst time of processes
    int currentTime = 0; // Current time
    int completed = 0; // Counter for completed processes
    bool isFinished[n]; // Array to indicate if the process is finished

    // Initialize remaining array with burst times and set response times
    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
        isFinished[i] = false;
        rt[i] = -1; // Response time is initially unset
    }

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = isLowerPriorityHigher ? 1000000 : -1; // Adjust initial value based on priority type

        // Find the process with the highest priority that has arrived and is not finished
        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && !isFinished[i] &&
                ((isLowerPriorityHigher && priority[i] < highestPriority) ||
                 (!isLowerPriorityHigher && priority[i] > highestPriority))) {
                highestPriority = priority[i];
                highestPriorityIndex = i;
            }
        }

        // If no process is found, move to the next time
        if (highestPriorityIndex == -1) {
            currentTime++;
            continue;
        }

        int currentProcess = highestPriorityIndex;

        // Set response time if it's the first time the process is executed
        if (rt[currentProcess] == -1) {
            rt[currentProcess] = currentTime - at[currentProcess];
        }

        // Execute the process for 1 unit of time
        remaining[currentProcess]--;
        currentTime++;

        // If the process is completed
        if (remaining[currentProcess] == 0) {
            isFinished[currentProcess] = true;
            completed++;
            ct[currentProcess] = currentTime; // Set completion time for the process
            tat[currentProcess] = ct[currentProcess] - at[currentProcess]; // Calculate turnaround time
            wt[currentProcess] = tat[currentProcess] - bt[currentProcess]; // Calculate waiting time
        }
    }

    // Print the table
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i], rt[i]);
    }
}

void main()
{
    // Number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Process id's
    int processes[n];
    // Burst time of all processes
    int burst_time[n];
    // Arrival time of all processes
    int arrival_time[n];
    // Priority of all processes
    int priority[n];
    // Priority type (true for lower number = higher priority, false for higher number = higher priority)
    int priorityType;
    bool isLowerPriorityHigher;

    printf("Enter 1 if lower number indicates higher priority, 0 if higher number indicates higher priority: ");
    scanf("%d", &priorityType);
    isLowerPriorityHigher = (priorityType == 1);

    printf("Enter Process Number:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i]);
    }
    printf("Enter Priority:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }
    printf("Enter Arrival Time:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrival_time[i]);
    }
    printf("Enter Burst Time:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
    }

    // Arrays to store waiting time, turnaround time, completion time, and response time
    int wt[n], tat[n], ct[n], rt[n];

    printf("\nPriority Scheduling (Preemptive):\n");
    findCompletionTime(processes, n, burst_time, arrival_time, wt, tat, ct, rt, priority, isLowerPriorityHigher);
}