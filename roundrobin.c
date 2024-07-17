#include <stdio.h>
#include <stdbool.h>

void findCompletionTime(int processes[], int n, int bt[], int at[], int wt[], int tat[], int ct[], int rt[], int quantum)
{
    int remaining[n]; // Array to store remaining burst time of processes
    bool firstResponse[n]; // Array to track if response time has been set
    int currentTime = 0; // Current time
    int completed = 0; // Counter for completed processes

    // Initialize remaining array with burst times and first response array
    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
        firstResponse[i] = true;
    }

    // Queue to hold the indices of the processes
    int queue[n];
    int front = -1, rear = -1;

    // Function to add process to the queue
    void enqueue(int process) {
        if (rear == n - 1) rear = -1;
        queue[++rear] = process;
        if (front == -1)
            front = 0;
    }

    // Function to remove process from the queue
    int dequeue() {
        int process = queue[front];
        if (front == rear)
            front = rear = -1;
        else {
            front++;
            if (front == n)
                front = 0;
        }
        return process;
    }

    // To track which processes have been added to the queue
    bool inQueue[n];
    for (int i = 0; i < n; i++)
        inQueue[i] = false;

    while (completed < n) {
        // Add all processes to the queue that have arrived by the current time
        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && !inQueue[i]) {
                enqueue(i);
                inQueue[i] = true;
            }
        }

        // If no process is ready, increment the current time
        if (front == -1) {
            currentTime++;
            continue;
        }

        int currentProcess = dequeue();

        // Set response time if it's the first time the process is executed
        if (firstResponse[currentProcess]) {
            rt[currentProcess] = currentTime - at[currentProcess];
            firstResponse[currentProcess] = false;
        }

        // Execute the process for the time quantum or until completion
        if (remaining[currentProcess] > quantum) {
            remaining[currentProcess] -= quantum;
            currentTime += quantum;
        } else {
            currentTime += remaining[currentProcess];
            remaining[currentProcess] = 0;
            completed++;
            // Set completion time for the process
            ct[currentProcess] = currentTime;
            // Calculate waiting time and turnaround time for the process
            tat[currentProcess] = ct[currentProcess] - at[currentProcess];
            wt[currentProcess] = tat[currentProcess] - bt[currentProcess];
        }

        // Add all processes to the queue that have arrived by the current time
        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && !inQueue[i]) {
                enqueue(i);
                inQueue[i] = true;
            }
        }

        // Re-enqueue the current process if it is not finished
        if (remaining[currentProcess] > 0) {
            enqueue(currentProcess);
        }
    }

    // Print the table
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
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

    printf("Enter Process Number:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i]);
    }
    printf("Enter Arrival Time:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrival_time[i]);
    }
    printf("Enter Burst Time:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
    }

    // Time quantum for Round Robin
    int quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Arrays to store waiting time, turnaround time, completion time, and response time
    int wt[n], tat[n], ct[n], rt[n];

    printf("\nRound Robin Scheduling:\n");
    findCompletionTime(processes, n, burst_time, arrival_time, wt, tat, ct, rt, quantum);
}