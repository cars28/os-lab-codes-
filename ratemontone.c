#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
 
// Function to sort processes based on periods (ascending order) 
void sort(int proc[], int b[], int pt[], int n) { 
    for (int i = 0; i < n; i++) { 
        for (int j = i; j < n; j++) { 
            if (pt[j] < pt[i]) { 
                // Swapping process ids 
                int temp = proc[i]; 
                proc[i] = proc[j]; 
                proc[j] = temp; 
 
                // Swapping burst times 
                temp = b[i]; 
                b[i] = b[j]; 
                b[j] = temp; 
 
                // Swapping periods 
                temp = pt[i]; 
                pt[i] = pt[j]; 
                pt[j] = temp; 
            } 
        } 
    } 
} 
 
// Function to compute the least common multiple of all periods 
int lcmul(int p[], int n) { 
    int lcm = p[0]; 
    for (int i = 1; i < n; i++) { 
        int a = lcm, b = p[i]; 
        while (b != 0) { 
            int r = a % b; 
            a = b; 
            b = r; 
        } 
        lcm = (lcm * p[i]) / a; 
    } 
    return lcm; 
} 
 
int main() { 
    int n; 
    printf("Enter the number of processes: "); 
    scanf("%d", &n); 
    int proc[n], b[n], pt[n], rem[n]; 
 
    printf("Enter the CPU burst times:\n"); 
    for (int i = 0; i < n; i++) scanf("%d", &b[i]); 
    printf("Enter the time periods:\n"); 
    for (int i = 0; i < n; i++) scanf("%d", &pt[i]); 
    for (int i = 0; i < n; i++) proc[i] = i + 1; 
 
    sort(proc, b, pt, n); 
    int l = lcmul(pt, n); 
 
    printf("\nRate Monotonic Scheduling:\n"); 
    printf("PID\t Burst\tPeriod\n"); 
    for (int i = 0; i < n; i++) printf("%d\t\t%d\t\t%d\n", proc[i], b[i], pt[i]); 
 
      // Feasibility check 
    double sum = 0.0; 
    for (int i = 0; i < n; i++) { 
        sum += (double)b[i] / pt[i]; 
    } 
    double rhs = n * (pow(2.0, (1.0 / n)) - 1.0); 
    printf("\n%lf <= %lf => %s\n", sum, rhs, (sum <= rhs) ? "true" : "false"); 
    if (sum > rhs) { 
        printf("The given set of processes is not schedulable.\n"); 
        exit(0); 
    } 
 
    printf("Scheduling occurs for %d ms\n\n", l); 
 
    int time = 0, prev = -1; 
    for (int i = 0; i < n; i++) rem[i] = b[i]; 
    int nextRelease[n]; 
    for (int i = 0; i < n; i++) nextRelease[i] = 0; 
 
    while (time < l) { 
        int taskToExecute = -1; 
        for (int i = 0; i < n; i++) { 
            if (time == nextRelease[i]) { 
                rem[i] = b[i];  // Reset remaining time at the start of the period 
                nextRelease[i] += pt[i];  // Schedule next release 
            } 
            if (rem[i] > 0 && (taskToExecute == -1 || pt[i] < pt[taskToExecute])) { 
                taskToExecute = i;}} 
       if (taskToExecute != -1) { 
            if (prev != taskToExecute) { 
                printf("%dms: Task %d is running.\n", time, proc[taskToExecute]); 
                prev = taskToExecute;            } 
            rem[taskToExecute]--; 
        } else if (prev != -1) { 
            printf("%dms: CPU is idle.\n", time); 
            prev = -1;        } 
        time++;    }    return 0;}