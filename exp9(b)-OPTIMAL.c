#include <stdio.h>
#include <stdbool.h>
// Function to find the index of the page in the frames
int findIndex(int frames[], int n, int page)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == page)
            return i;
    }
    return -1;
}
// Function to print the contents of the frames
void printFrames(int frames[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}
// OPTIMAL page replacement algorithm
void optimal(int pages[], int n, int capacity)
{
    int frames[capacity];
    int pageFaults = 0;
    int index, farthest, futureIndex;
    for (int i = 0; i < capacity; i++)
        frames[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        index = findIndex(frames, capacity, page);
        if (index == -1)
        {
            int emptyIndex = findIndex(frames, capacity, -1);
            if (emptyIndex != -1)
            {
                frames[emptyIndex] = page;
            }
            else
            {
                farthest = i + 1;
                futureIndex = -1;
                for (int j = 0; j < capacity; j++)
                {
                    int currentPage = frames[j];
                    int k;
                    for (k = i + 1; k < n; k++)
                    {
                        if (currentPage == pages[k])
                        {
                            if (k > farthest)
                            {
                                farthest = k;
                                futureIndex = j;
                            }
                            break;
                        }
                    }
                    if (k == n)
                    {
                        futureIndex = j;
                        break;
                    }
                }
                frames[futureIndex] = page;
            }
            pageFaults++;
        }
        printFrames(frames, capacity);
    }
    printf("Optimal Page Faults: %d\n", pageFaults);
}
int main()
{
    int pages[] = {1, 2, 3, 4, 1, 5, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2};
    int capacity = 3;
    int n = sizeof(pages) / sizeof(pages[0]);
    printf("Page reference sequence:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n\n");
    printf("\n");
    printf("Optimal Algorithm:\n");
    optimal(pages, n, capacity);
    printf("\n");
    return 0;
}