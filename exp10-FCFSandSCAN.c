#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Function to calculate absolute difference between two numbers
int absDiff(int a, int b)
{
    return abs(a - b);
}
// FCFS Disk Scheduling Algorithm
int FCFS(int *requests, int numRequests)
{
    int totalSeekTime = 0;
    for (int i = 1; i < numRequests; i++)
    {
        totalSeekTime += absDiff(requests[i], requests[i - 1]);
    }
    return totalSeekTime;
}
// SCAN Disk Scheduling Algorithm
int SCAN(int *requests, int numRequests, int start, int end)
{
    int totalSeekTime = 0;
    int currentTrack = start;
    bool movingUp = true;
// Moving towards the end of the disk
    while (numRequests > 0)
    {
        for (int i = 0; i < numRequests; i++)
        {
            if (requests[i] == currentTrack)
            {
                totalSeekTime += absDiff(currentTrack, start);
                start = currentTrack;
                requests[i] = -1;
// Mark this request as processed
            }
        }
        if (movingUp)
        {
            currentTrack++;
            if (currentTrack > end)
            {
                movingUp = false;
                currentTrack = end;
            }
        }
        else
        {
            currentTrack--;
            if (currentTrack < 0)
            {
                movingUp = true;
                currentTrack = 0;
            }
        }
// Remove processed requests
        int newNumRequests = 0;
        for (int i = 0; i < numRequests; i++)
        {
            if (requests[i] != -1)
            {
                requests[newNumRequests++] = requests[i];
            }
        }
        numRequests = newNumRequests;
    }
    return totalSeekTime;
}
int main()
{
    int numRequests, start, end;
    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);
    int *requests = (int *)malloc(numRequests * sizeof(int));
    printf("Enter the requests:\n");
    for (int i = 0; i < numRequests; i++)
    {
        scanf("%d", &requests[i]);
    }
    printf("Enter the start and end of the disk: ");
    scanf("%d %d", &start, &end);
    int fcfsSeekTime = FCFS(requests, numRequests);
    int scanSeekTime = SCAN(requests, numRequests, start, end);
    printf("FCFS Seek Time: %d\n", fcfsSeekTime);
    printf("SCAN Seek Time: %d\n", scanSeekTime);
    free(requests);
    return 0;
}