#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

struct Process {
    int id, burst_time, deadline, period;
    int remaining_time;
    int absolute_deadline;
};

void earliest_deadline_first(struct Process p[], int n, int time_limit) {
    printf("\nEarliest Deadline First Scheduling:\n");
    printf("PID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].burst_time, p[i].deadline, p[i].period);
    }

    // Initialization
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = 0;
        p[i].absolute_deadline = -1;
    }

    printf("\nScheduling occurs for %d ms:\n", time_limit);

    for (int time = 0; time < time_limit; time++) {
        // Release new jobs if period matches
        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining_time = p[i].burst_time;
                p[i].absolute_deadline = time + p[i].deadline;
                printf("%dms: Task %d released (Deadline at %dms)\n", time, p[i].id, p[i].absolute_deadline);
            }
        }
        int earliest = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                if (earliest == -1 || p[i].absolute_deadline < p[earliest].absolute_deadline) {
                    earliest = i;
                }
            }
        }
        if (earliest != -1) {
            printf("%dms: Task %d is running.\n", time, p[earliest].id);
            p[earliest].remaining_time--;
        } else {
            printf("%dms: CPU is idle.\n", time);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d] burst time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].id = i + 1;
    }

    printf("Enter the deadlines:\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d] deadline: ", i + 1);
        scanf("%d", &processes[i].deadline);
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d] period: ", i + 1);
        scanf("%d", &processes[i].period);
    }

    int hyperperiod = processes[0].period;
    for (int i = 1; i < n; i++) {
        hyperperiod = lcm(hyperperiod, processes[i].period);
    }

    printf("\nSystem will execute for hyperperiod (LCM of periods): %d ms\n", hyperperiod);

    earliest_deadline_first(processes, n, hyperperiod);

    return 0;
}
