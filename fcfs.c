#include<stdio.h>

void main()
{
    int n;
    printf("Enter number of processes:\n");
    scanf("%d",&n);
    int pr[n], at[n], bt[n], ct[n], tat[n], wt[n];
    printf("Enter Process number:\n");
    for (int i=0; i<n; i++)
    {
        scanf("%d", &pr[i]);
    }
    printf("Enter Arrival Time:\n");
    for (int i=0; i<n; i++)
    {
        scanf("%d", &at[i]);
    }
    printf("Enter Burst Time:\n");
    for (int i=0; i<n; i++)
    {
        scanf("%d", &bt[i]);
    }
    int temp1, temp2, temp3;
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            if (at[j]<at[i])
            {
                temp1 = at[j];
                at[j] = at[i];
                at[i] = temp1;

                temp2 = bt[j];
                bt[j] = bt[i];
                bt[i] = temp2;

                temp3 = pr[j];
                pr[j] = pr[i];
                pr[i] = temp3;
            }
        }
    }
    int x=at[0];
    for (int i=0; i<n; i++)
    {
        if (x<at[i])
        {
            x = at[i];
        }
        ct[i] = bt[i] + x;
        x = ct[i];
    }
    for (int i=0; i<n; i++)
    {
        tat[i] = ct[i] - at[i];
    }
    for (int i=0; i<n; i++)
    {
        wt[i] = tat[i] - bt[i];
    }
    for (int i=0; i<n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pr[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    float avg_tat = 0, avg_wt = 0;
    for (int i=0; i<n; i++)
    {
        avg_tat = avg_tat + tat[i];
        avg_wt = avg_wt + wt[i];
    }
    avg_tat = avg_tat/n;
    avg_wt = avg_wt/n;
    printf("The average Turnaround time is: %f", avg_tat);
    printf("\nThe average Waiting time is: %f`", avg_wt);
}