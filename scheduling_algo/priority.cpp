#include <iostream>
using namespace std;

struct Process {
    int pid, arrival, burst, priority, remaining, completion, turnaround, waiting;
    bool completed = false;
};

void priorityScheduling(Process p[], int n) {
    int completed = 0, currentTime = 0, highestPriorityIndex;
    float avgTAT = 0, avgWT = 0;

    while (completed < n) {
        highestPriorityIndex = -1;
        int highestPriority = 9999;

        // Find the highest priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && !p[i].completed && p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++; // No process ready, increment time
        } else {
            p[highestPriorityIndex].remaining--;

            if (p[highestPriorityIndex].remaining == 0) { // Process completed
                completed++;
                p[highestPriorityIndex].completed = true;
                p[highestPriorityIndex].completion = currentTime + 1;
                p[highestPriorityIndex].turnaround = p[highestPriorityIndex].completion - p[highestPriorityIndex].arrival;
                p[highestPriorityIndex].waiting = p[highestPriorityIndex].turnaround - p[highestPriorityIndex].burst;

                avgTAT += p[highestPriorityIndex].turnaround;
                avgWT += p[highestPriorityIndex].waiting;
            }
            currentTime++;
        }
    }

    // Display the results
    cout << "\nPID\tAT\tBT\tP\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t" << p[i].priority
             << "\t" << p[i].completion << "\t" << p[i].turnaround << "\t" << p[i].waiting << "\n";
    }

    cout << "\nAverage Turnaround Time: " << avgTAT / n;
    cout << "\nAverage Waiting Time: " << avgWT / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process p[n];

    cout << "Enter Arrival Time, Burst Time, and Priority for each process:\n";
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "P" << i + 1 << " AT BT P: ";
        cin >> p[i].arrival >> p[i].burst >> p[i].priority;
        p[i].remaining = p[i].burst;  // Initialize remaining burst time
    }

    priorityScheduling(p, n);

    return 0;
}
