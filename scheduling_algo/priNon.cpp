#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, priority, completion, turnaround, waiting;
};

// Sorting function for sorting processes based on arrival time & priority
bool compare(Process a, Process b) {
    if (a.arrival == b.arrival)
        return a.priority < b.priority;  // If same arrival time, sort by priority
    return a.arrival < b.arrival;
}

void priorityScheduling(Process p[], int n) {
    sort(p, p + n, compare);  // Sort based on arrival time and priority

    int currentTime = 0;
    float avgTAT = 0, avgWT = 0;
    vector<bool> completed(n, false);


    for (int i = 0; i < n; i++) {
        int highestPriorityIndex = -1;
        int highestPriority = 9999;

        // Find the highest priority process that has arrived and is not completed
        for (int j = 0; j < n; j++) {
            if (p[j].arrival <= currentTime && !completed[j] && p[j].priority < highestPriority) {
                highestPriority = p[j].priority;
                highestPriorityIndex = j;
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++;  // If no process is ready, increment time
            i--;  // Repeat loop for next available process
            continue;
        }

        // Execute the selected process
        completed[highestPriorityIndex] = true;
        currentTime = max(currentTime, p[highestPriorityIndex].arrival) + p[highestPriorityIndex].burst;
        p[highestPriorityIndex].completion = currentTime;
        p[highestPriorityIndex].turnaround = p[highestPriorityIndex].completion - p[highestPriorityIndex].arrival;
        p[highestPriorityIndex].waiting = p[highestPriorityIndex].turnaround - p[highestPriorityIndex].burst;

        avgTAT += p[highestPriorityIndex].turnaround;
        avgWT += p[highestPriorityIndex].waiting;
    }

    // Display results
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
    }

    priorityScheduling(p, n);

    return 0;
}
