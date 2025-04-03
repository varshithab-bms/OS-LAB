#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int id;
    int at, bt, ct, wt, tat, queue;
} process;

void fcfs(process p[], int n, process final_order[], int *index);
void roundRobin(process p[], int n, int q, process final_order[], int *index);
void display(process p[], int n);

int total_wt = 0, total_tat = 0;

int main() {
    int n, q, user_count = 0, s_count = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    process p[n], user[n], system[n], final_order[n];  
    int final_index = 0;  
    
    printf("To differentiate between types of queues: \nEnter 0 for system process, 1 for user process\n");
    
    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, Burst Time, and Type of queue for Process %d: ", i + 1);
        scanf("%d %d %d %d", &p[i].id, &p[i].at, &p[i].bt, &p[i].queue);
    }
     
    for (int i = 0; i < n; i++) {
        if (p[i].queue == 0) {
            system[s_count++] = p[i];
        } else {
            user[user_count++] = p[i];
        }
    }
    
    if (s_count > 0) {
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &q);
        roundRobin(system, s_count, q, final_order, &final_index);
    }
    
    if (user_count > 0) {
        fcfs(user, user_count, final_order, &final_index);
    }
    
    display(final_order, final_index); 
    
    return 0;
}

void fcfs(process p[], int n, process final_order[], int *index) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        currentTime = p[i].ct; 
        final_order[*index] = p[i];
        final_order[*index].queue = 1; 
        (*index)++;
    }
}

void roundRobin(process p[], int n, int q, process final_order[], int *index) {
    int currentTime = 0, completed = 0;
    int remaining_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = p[i].bt;
    }

    while (completed < n) {
        int all_idle = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && remaining_time[i] > 0) {
                all_idle = 0;
                int time_slice = (remaining_time[i] > q) ? q : remaining_time[i];
                currentTime += time_slice;
                remaining_time[i] -= time_slice;

                if (remaining_time[i] == 0) {
                    completed++;
                    p[i].ct = currentTime;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    total_wt += p[i].wt;
                    total_tat += p[i].tat; 
                    final_order[*index] = p[i];
                    final_order[*index].queue = 0; 
                    (*index)++;
                }
            }
        }
        if (all_idle && completed < n) {
            currentTime++;
        }
    }
}

void display(process p[], int n) {
    printf("\nFinal Scheduling Table:\n");
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\tQueue Type\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%s\n", 
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat, 
               (p[i].queue == 0) ? "RR" : "FCFS");
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}
#include <stdio.h>

#define MAX 10

typedef struct {
    int id, arrival, burst, remaining, completion, turnaround, waiting, queue;
} Process;

void sort_by_AT(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void roundRobin(Process p[], int n, int time_quantum, int *time, int queue_level) {
    int completed = 0, i;
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    for (i = 0; i < n; i++) {
        if (p[i].arrival <= *time && p[i].remaining > 0 && p[i].queue == queue_level) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (front < rear) {
        int idx = queue[front++];
        if (p[idx].remaining > time_quantum) {
            *time += time_quantum;
            p[idx].remaining -= time_quantum;
        } else {
            *time += p[idx].remaining;
            p[idx].remaining = 0;
            p[idx].completion = *time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        }

        for (i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrival <= *time && p[i].remaining > 0 && p[i].queue == queue_level) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].remaining > 0) {
            queue[rear++] = idx;
        } else {
            p[idx].queue++; // Move to lower priority queue
        }
    }
}

void fcfs(Process p[], int n, int *time) {
    for (int i = 0; i < n; i++) {
        if (p[i].queue == 3 && p[i].remaining > 0) {
            if (*time < p[i].arrival)
                *time = p[i].arrival;
            p[i].completion = *time + p[i].remaining;
            p[i].turnaround = p[i].completion - p[i].arrival;
            p[i].waiting = p[i].turnaround - p[i].burst;
            *time = p[i].completion;
            p[i].remaining = 0;
        }
    }
}

void printProcesses(Process p[], int n) {
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
    }
}

int main() {
    Process p[MAX];
    int n, quantum1, quantum2, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum for Queue 1 (Round Robin - High Priority): ");
    scanf("%d", &quantum1);

    printf("Enter time quantum for Queue 2 (Round Robin - Medium Priority): ");
    scanf("%d", &quantum2);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival and burst time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].id = i + 1;
        p[i].remaining = p[i].burst;
        p[i].queue = 1; // Start in highest priority queue
    }

    sort_by_AT(p, n);

    printf("\nExecuting Queue 1 (Round Robin - High Priority)\n");
    roundRobin(p, n, quantum1, &time, 1);

    printf("\nExecuting Queue 2 (Round Robin - Medium Priority)\n");
    roundRobin(p, n, quantum2, &time, 2);

    printf("\nExecuting Queue 3 (FCFS - Low Priority)\n");
    fcfs(p, n, &time);

    printf("\nFinal Process Table (Multi-Level Queue Scheduling):\n");
    printProcesses(p, n);

    return 0;
}