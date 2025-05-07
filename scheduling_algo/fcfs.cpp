#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, completion, turnaround, waiting;
};

bool compare(Process a, Process b) {
    return a.arrival < b.arrival;
}

void FCFS(Process p[], int n) {
    sort(p, p + n, compare);  

    int currentTime = 0;
    float avgTAT = 0, avgWT = 0;

    for (int i = 0; i < n; i++) {
        currentTime = max(currentTime, p[i].arrival) + p[i].burst;
        p[i].completion = currentTime;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        avgTAT += p[i].turnaround;
        avgWT += p[i].waiting;
    }


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

    FCFS(p, n);

    return 0;
}
