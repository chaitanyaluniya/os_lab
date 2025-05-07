#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, completion, turnaround, waiting;
};

// Sorting function to sort processes by arrival time
bool compare(Process a, Process b) {
    return a.arrival < b.arrival;
}

void SJF(Process p[], int n) {
    sort(p, p + n, compare);  // Sort based on arrival time

    int completed = 0, currentTime = 0;
    float avgTAT = 0, avgWT = 0;
    vector<bool> completedFlag(n, false);

    while (completed < n) {
        int minIndex = -1, minBurst = 9999;

        // Find process with shortest burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (!completedFlag[i] && p[i].arrival <= currentTime && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime++;  // If no process is ready, increment time
        } else {
            completedFlag[minIndex] = true;
            currentTime = max(currentTime, p[minIndex].arrival) + p[minIndex].burst;
            p[minIndex].completion = currentTime;
            p[minIndex].turnaround = p[minIndex].completion - p[minIndex].arrival;
            p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;

            avgTAT += p[minIndex].turnaround;
            avgWT += p[minIndex].waiting;

            completed++;
        }
    }

    // Display results
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].completion << "\t" << p[i].turnaround << "\t" << p[i].waiting << "\n";
    }

    cout << "\nAverage Turnaround Time: " << avgTAT / n;
    cout << "\nAverage Waiting Time: " << avgWT / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process p[n];

    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "P" << i + 1 << " AT BT: ";
        cin >> p[i].arrival >> p[i].burst;
    }

    SJF(p, n);

    return 0;
}
