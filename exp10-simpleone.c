#include <stdio.h>
#include <stdlib.h>

// custom abs function (for lab style)
int absDiff(int a, int b)
{
    return abs(a - b);
}

// FCFS
int FCFS(int req[], int n)
{
    int seek = 0;
    for(int i = 1; i < n; i++)
        seek += absDiff(req[i], req[i-1]);
    return seek;
}

// sort function
void sort(int arr[], int n)
{
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++)
            if(arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}

// SCAN (LOOK behavior)
int SCAN(int req[], int n, int head)
{
    int seek = 0;

    sort(req, n);

    int i;
    for(i = 0; i < n; i++)
        if(req[i] >= head)
            break;

    // move right only
    for(int j = i; j < n; j++)
    {
        seek += absDiff(head, req[j]);
        head = req[j];
    }

    return seek;
}

int main()
{
    int n, head, end;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter requests:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter head and disk end: ");
    scanf("%d %d", &head, &end);  // end kept for format

    int fcfsSeek = FCFS(req, n);
    int scanSeek = SCAN(req, n, head);

    printf("FCFS Seek Time: %d\n", fcfsSeek);
    printf("SCAN Seek Time: %d\n", scanSeek);

    return 0;
}