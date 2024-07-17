#include <stdio.h>

void findCompletionTime(int processes[], int n, int bt[], int at[], int wt[], int tat[], int ct[])
{
    int remaining[n];   
    int currentTime = 0;
    int completed = 0;  
    for (int i = 0; i < n; i++)
        remaining[i] = bt[i];

    while (completed < n)
    {
        int shortest = -1; 
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currentTime && remaining[i] > 0)
            {
                if (shortest == -1 || remaining[i] <= remaining[shortest])
                    shortest = i;
            }
        }
         if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        
        remaining[shortest]--;

        
        if (remaining[shortest] == 0)
        {
            completed++;
            ct[shortest] = currentTime + 1;
            wt[shortest] = ct[shortest] - bt[shortest] - at[shortest];
            tat[shortest] = ct[shortest] - at[shortest];
        }

        currentTime++;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    avg_tat /= n;
    avg_wt /= n;
    printf("The average Turnaround time is %f\n", avg_tat);
    printf("The average Waiting time is %f\n", avg_wt);
}

void main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];

    printf("Enter Process Number:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &processes[i]);
    }
    printf("Enter Arrival Time:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arrival_time[i]);
    }
    printf("Enter Burst Time:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &burst_time[i]);
    }

    int wt[n], tat[n], ct[n];

    printf("\nSJF (Preemptive) Scheduling:\n");
    findCompletionTime(processes, n, burst_time, arrival_time, wt, tat, ct);
}