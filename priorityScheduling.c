#include <stdio.h>

#define MAX 10

typedef struct {
    int pid, at, bt, pt, remaining_bt, ct, tat, wt, rt, is_completed, st;
} Process;

// Function for Non-Preemptive Priority Scheduling
void nonPreemptivePriority(Process p[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int highest_priority = -1, selected = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].is_completed && p[i].pt > highest_priority) {
                highest_priority = p[i].pt;
                selected = i;
            }
        }

        if (selected == -1) {
            time++;
            continue;
        }

        // If RT is not yet calculated, calculate it
        if (p[selected].rt == -1) {
            p[selected].st = time;  // Start time
            p[selected].rt = time - p[selected].at;  // Response Time = Start Time - Arrival Time
        }

        time += p[selected].bt;
        p[selected].ct = time;
        p[selected].tat = p[selected].ct - p[selected].at;
        p[selected].wt = p[selected].tat - p[selected].bt;
        p[selected].is_completed = 1;
        completed++;
    }
}

// Function for Preemptive Priority Scheduling
void preemptivePriority(Process p[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int highest_priority = -1, selected = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining_bt > 0 && p[i].pt > highest_priority) {
                highest_priority = p[i].pt;
                selected = i;
            }
        }

        if (selected == -1) {
            time++;
            continue;
        }

        // If RT is not yet calculated, calculate it
        if (p[selected].rt == -1) {
            p[selected].st = time;  // Start time
            p[selected].rt = time - p[selected].at;  // Response Time = Start Time - Arrival Time
        }

        p[selected].remaining_bt--;
        time++;

        if (p[selected].remaining_bt == 0) {
            p[selected].ct = time;
            p[selected].tat = p[selected].ct - p[selected].at;
            p[selected].wt = p[selected].tat - p[selected].bt;
            completed++;
        }
    }
}

// Function to display the results of processes
void displayProcesses(Process p[], int n) {
    float avg_tat = 0, avg_wt = 0, avg_rt = 0;

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        avg_rt += p[i].rt;
    }

    printf("\nAverage TAT: %.2f", avg_tat / n);
    printf("\nAverage WT: %.2f", avg_wt / n);
    printf("\nAverage RT: %.2f\n", avg_rt / n);
}

int main() {
    Process p[MAX];
    int n, choice;

    // Asking the user for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Getting arrival times, burst times, and priorities for each process
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1; // Process ID starts from 1
        printf("\nEnter Arrival Time, Burst Time, and Priority for Process %d:\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority (higher number means higher priority): ");
        scanf("%d", &p[i].pt);
        p[i].remaining_bt = p[i].bt;  // Initialize remaining burst time
        p[i].is_completed = 0;        // Mark process as incomplete
        p[i].rt = -1;                 // Response time will be calculated later
    }

    // Menu to choose the scheduling method
    while (1) {
        printf("\nPriority Scheduling Menu:\n");
        printf("1. Non-Preemptive Priority Scheduling\n");
        printf("2. Preemptive Priority Scheduling\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                nonPreemptivePriority(p, n);
                printf("Non-Preemptive Scheduling Completed!\n");
                displayProcesses(p, n);
                break;
            case 2:
                preemptivePriority(p, n);
                printf("Preemptive Scheduling Completed!\n");
                displayProcesses(p, n);
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
