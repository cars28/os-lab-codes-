#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define N 5
#define MAX_PHILOSOPHERS 5

bool spoon[N] = {true, true, true, true, true}; // true means the spoon is available
int state[N] = {THINKING, THINKING, THINKING, THINKING, THINKING};

bool wait(int i)
{
    return !spoon[i]; // if spoon is not available, return true
}

void signal(int i)
{
    spoon[i] = true; // make the spoon available
}

void take_spoon(int i)
{
    spoon[i] = false; // take the spoon
}

void test(int i)
{
    if (state[i] == HUNGRY && !wait(i) && !wait((i + 1) % N))
    {
        state[i] = EATING;
        take_spoon(i);
        take_spoon((i + 1) % N);
        printf("Philosopher %d is Granted to Eat\n", i + 1);
    }
}

void put_spoon(int i)
{
    signal(i);
    signal((i + 1) % N);
    state[i] = THINKING;
    printf("Philosopher %d is Waiting\n", i + 1);
}

int completed()
{
    for (int i = 0; i < N; i++)
    {
        if (state[i] != THINKING)
            return 0;
    }
    printf("Dinner completed\n");
    return 1;
}

void allow_one_to_eat(int hungry[], int n)
{
    for (int i = 0; i < n; i++)
    {
        state[hungry[i]-1]=HUNGRY;
    }
    for (int i = 0; i < n; i++)
    {
        int pos = hungry[i] - 1;
        test(pos);
        if (state[pos] == EATING)
        {
            put_spoon(pos);
        }
        for (int j = 0; j < n; j++)
        {
            if (state[hungry[j] - 1] == HUNGRY)
            {
                printf("Philosopher %d is Waiting\n", hungry[j]);
            }
        }
    }
}

void allow_two_to_eat(int hungry[], int n)
{
    if (n < 2 || n > MAX_PHILOSOPHERS)
    {
        printf("Invalid number of philosophers.\n");
        return;
    }
    else if(n==2)
    {
        if(abs(hungry[0]-hungry[1])==1)
        {
            printf("Not possible");
            exit(0);
        }
        printf("P %d and P %d are granted to eat\n", hungry[0], hungry[1]);
    }
    else{
int combination_count = 1,a[n-2];

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
                int p=0;

        if(abs(hungry[i]-hungry[j])==1)
        {
            continue;
        }
            printf("\n\n\ncombination %d\n\n", combination_count);

            printf("P %d and P %d are granted to eat\n", hungry[i], hungry[j]);

            for (int k = 0; k < n; k++) {
                if (k != i && k != j) {
                    printf("P %d is waiting\n", hungry[k]);
                    a[p]=k;
                    p++;
                }
            }
            printf("\n");
            printf("P %d is waiting\n", hungry[i]);
            printf("P %d is waiting\n", hungry[j]);
            int com=1;
            if(abs(a[0]-a[1])!=1 && n>3)
            {
                    if(n==5)
                    {
                        printf("Combination %d.%d\n",combination_count,com);
                    }
                    printf("P %d and P %d are granted to eat\n", hungry[a[0]], hungry[a[1]]);
                    if(n==5)
                    {
                        printf("P %d is waiting\n", hungry[a[2]]);
                    }
                    printf("P %d is waiting\n", hungry[a[0]]);
                    printf("P %d is waiting\n", hungry[a[1]]);
                    com++;
            }
            if(abs(a[2]-a[1])!=1 && n>4)
            {
                    printf("Combination %d.%d\n",combination_count,com);
                    printf("P %d and P %d are granted to eat\n", hungry[a[2]], hungry[a[1]]);
                    printf("P %d is waiting\n", hungry[a[0]]);
                    printf("P %d is waiting\n", hungry[a[1]]);
                    printf("P %d is waiting\n", hungry[a[2]]);
                    com++;
            }
            if(abs(a[0]-a[2])!=1 && n>4)
            {
                    printf("Combination %d.%d\n",combination_count,com);
                    printf("P %d and P %d are granted to eat\n", hungry[a[0]], hungry[a[2]]);
                    printf("P %d is waiting\n", hungry[a[1]]);
                    printf("P %d is waiting\n", hungry[a[0]]);
                    printf("P %d is waiting\n", hungry[a[2]]);

            }
            combination_count++;
        }
    }
    }
}

int main()
{
    while (1)
    {
        int total_philosophers, hungry_count;
        int hungry_positions[MAX_PHILOSOPHERS];

        printf("DINING PHILOSOPHER PROBLEM\n");
        printf("Enter the total no. of philosophers: %d\n", N);
        total_philosophers = N;

        printf("How many are hungry: ");
        scanf("%d", &hungry_count);

        if (hungry_count < 1 || hungry_count > total_philosophers)
        {
            printf("Invalid number of hungry philosophers.\n");
            return 1;
        }

        for (int i = 0; i < hungry_count; i++)
        {
            printf("Enter philosopher %d position: ", i + 1);
            scanf("%d", &hungry_positions[i]);

            if (hungry_positions[i] < 1 || hungry_positions[i] > total_philosophers)
            {
                printf("Invalid philosopher position.\n");
                return 1;
            }
        }

        int choice;
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Allow one philosopher to eat at any time\n");
                allow_one_to_eat(hungry_positions, hungry_count);
                break;
            case 2:
                printf("Allow two philosophers to eat at the same time\n");
                allow_two_to_eat(hungry_positions, hungry_count);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
