#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;       // Process ID
    int arrival;   // Arrival Time
    int burst;     // Burst Time (Total CPU Time Required)
    int remaining; // Remaining Burst Time
    int completion;// Completion Time
    int waiting;   // Waiting Time
    int turnaround;// Turnaround Time
} Process;

void calculateTimes(Process p[], int n) {
    int completed = 0, time = 0, shortest, min_time;
    int is_completed[MAX_PROCESSES] = {0};

    while (completed != n) {
        shortest = -1;
        min_time = 9999;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !is_completed[i] && p[i].remaining < min_time) {
                min_time = p[i].remaining;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++; // No process available, increment time
            continue;
        }

        // Process execution
        p[shortest].remaining--;
        time++;

        // If process is completed
        if (p[shortest].remaining == 0) {
            completed++;
            is_completed[shortest] = 1;
            p[shortest].completion = time;
            p[shortest].turnaround = p[shortest].completion - p[shortest].arrival;
            p[shortest].waiting = p[shortest].turnaround - p[shortest].burst;
        }
    }
}

void printTable(Process p[], int n) {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, 
               p[i].completion, p[i].turnaround, p[i].waiting);
    }
}

int main() {
    int n;
    Process p[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst; // Initialize remaining burst time
    }

    // Calculate SRTF scheduling
    calculateTimes(p, n);

    // Print results
    printTable(p, n);

    return 0;
}
