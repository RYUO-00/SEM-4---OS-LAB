#include <stdio.h>
void FCFS(int processes[], int n, int burst_time[])
{
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0,
    total_turnaround_time = 0;
    waiting_time[0] = 0;
    // Waiting time for first process is 0
    // Calculating waiting time for each process
    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
    }
    // Calculating turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("First-Come, First-Served (FCFS) Scheduling Algorithm\n");
    printf("----------------------------------------------------\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    // Printing process details
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n", processes[i], burst_time[i],waiting_time[i],
        turnaround_time[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n",(float)total_turnaround_time / n);
    printf("\n");
}
void SJF(int processes[], int n, int burst_time[])
{
    int waiting_time[n], turnaround_time[n], completion_time[n],total_waiting_time =
    0,total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        int shortest_job_index = i;
        // Find the shortest job
        for (int j = i + 1; j < n; j++)
        {
            if (burst_time[j] < burst_time[shortest_job_index])
                shortest_job_index = j;
        }
        // Swap the shortest job with the current process
        int temp = burst_time[i];
        burst_time[i] = burst_time[shortest_job_index];
        burst_time[shortest_job_index] = temp;
        
        temp = processes[i];
        processes[i] = processes[shortest_job_index];
        processes[shortest_job_index] = temp;
    }
    waiting_time[0] = 0;
    // Waiting time for first process is 0
    // Calculating waiting time for each process
    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
    }
    // Calculating turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("Shortest Job First (SJF) Scheduling Algorithm\n");
    printf("----------------------------------------------------\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    // Printing process details
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n", processes[i], burst_time[i],waiting_time[i],
        turnaround_time[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("\n");
}
void RoundRobin(int process[], int n, int burst_time[], int quantum)
{
    int remaining_time[n], waiting[n], turnaround[n];
    int time = 0, done;

    float total_wt = 0, total_tat = 0;

    // copy burst time to remaining time
    for(int i = 0; i < n; i++)
        remaining_time[i] = burst_time[i];

    while(1)
    {
        done = 1;

        for(int i = 0; i < n; i++)
        {
            if(remaining_time[i] > 0)
            {
                done = 0;

                if(remaining_time[i] > quantum)
                {
                    time += quantum;
                    remaining_time[i] -= quantum;
                }
                else
                {
                    time += remaining_time[i];
                    waiting[i] = time - burst_time[i];
                    remaining_time[i] = 0;
                }
            }
        }

        if(done == 1)
            break;
    }

    // calculate turnaround time
    for(int i = 0; i < n; i++)
        turnaround[i] = burst_time[i] + waiting[i];
  
       

    // print output (same format)
    printf("\nRound Robin Scheduling Algorithm\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n",
               process[i], burst_time[i], waiting[i], turnaround[i]);
            
        total_wt += waiting[i];
        total_tat += turnaround[i];
        
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n], priority[n];
    printf("Enter the burst time and priority for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
        processes[i] = i + 1;
    }
    int quantum;
    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);
    printf("\n");
    FCFS(processes, n, burst_time);
    SJF(processes, n, burst_time);
    RoundRobin(processes, n, burst_time, quantum);
    return 0;
}