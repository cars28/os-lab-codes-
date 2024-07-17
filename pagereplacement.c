#include <stdio.h>
#include <stdlib.h>

void printFrames(int frames[], int n, int faults, int x) {
    printf("[");
    for (int i = 0; i < n; i++)
        printf(" %d ", frames[i]);
        if (x==1)
            printf("] Fault %d \n", faults);
        else
            printf("] \n");
}

void FIFO(int pages[], int n, int frame_size) {
    int frames[frame_size];
    for (int i = 0; i < frame_size; i++) frames[i] = -1;
    int index = 0, faults = 0;
    printf("FIFO: \n");
    for (int i = 0; i < n; i++)
    {
        int found=0;
        int x=0;
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % frame_size;
            faults++;
            x=1;
        }
        printFrames(frames, frame_size, faults, x);
    }
    printf("Total faults: %d\n", faults);
}

void LRU(int pages[], int n, int frame_size) {
    int frames[frame_size], last_used[frame_size];
    for (int i = 0; i < frame_size; i++) frames[i] = -1;
    for (int i = 0; i < frame_size; i++) last_used[i] = 0;
    int time = 0, faults = 0;

    printf("LRU: \n");
    for (int i = 0; i < n; i++)
    {
        int x=0;
        int found = 0;
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                last_used[j] = ++time;
                break;
            }
        }
        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < frame_size; j++) {
                if (last_used[j] < last_used[lru_index])
                    lru_index = j;
            }
            frames[lru_index] = pages[i];
            last_used[lru_index] = ++time;
            faults++;
            x=1;
        }
        printFrames(frames, frame_size, faults, x);
    }
    printf("Total faults: %d\n", faults);
}

void OPTIMAL(int pages[], int n, int frame_size) {
    int frames[frame_size];
    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;
    int faults = 0;

    printf("OPTIMAL: \n");
    for (int i = 0; i < n; i++)
    {
        int x=0;
        int found = 0;
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        for(int p = 0; p < frame_size; p++)
        {
            if(frames[p]==-1 && found==0)
            {
                found=1;
                frames[p] = pages[i];
                faults++;
                x=1;
                break;
            }
        }
        if (!found) {
            int replace_index = 0, farthest = -1;
            for (int j = 0; j < frame_size; j++)
            {

                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        if (k > farthest)
                        {
                            farthest = k;
                            replace_index = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    replace_index = j;
                    break;
                }
            }
            frames[replace_index] = pages[i];
            faults++;
            x=1;
        }
        printFrames(frames, frame_size, faults, x);
    }
    printf("Total faults: %d\n", faults);
}

int main() {
    int n, frame_size;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int *pages = (int *)malloc(n * sizeof(int));
    printf("Enter the page sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frame_size);

    FIFO(pages, n, frame_size);
    LRU(pages, n, frame_size);
    OPTIMAL(pages, n, frame_size);

    free(pages);
    return 0;
}