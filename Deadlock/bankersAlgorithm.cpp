#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void printInitialTable(const vector<vector<int>>& allocation, const vector<vector<int>>& max,
                       const vector<vector<int>>& need, const vector<int>& available) {
    int n = allocation.size();
    int m = available.size();

    cout << "\nInitial Resource Table:\n";
    cout << "PID\tAllocation\tMax\t\tNeed\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << i << "\t";
        for (int j = 0; j < m; ++j) cout << allocation[i][j] << " ";
        cout << "\t\t";
        for (int j = 0; j < m; ++j) cout << max[i][j] << " ";
        cout << "\t";
        for (int j = 0; j < m; ++j) cout << need[i][j] << " ";
        cout << "\n";
    }

    cout << "\nAvailable Resources: ";
    for (int i = 0; i < m; ++i) cout << available[i] << " ";
    cout << "\n";
}

void printStepTableHeader(int m) {
    cout << "\nStep-by-Step Safe Sequence Calculation:\n";
    cout << left << setw(6) << "Step"
         << setw(6) << "PID"
         << setw(15) << "Work Before"
         << setw(15) << "Need"
         << setw(15) << "Allocation"
         << setw(15) << "Work After"
         << setw(12) << "Can Proceed"
         << "\n";

    cout << string(84, '-') << "\n";
}

void printStepRow(int step, int pid,
                  const vector<int>& workBefore,
                  const vector<int>& need,
                  const vector<int>& allocation,
                  const vector<int>& workAfter,
                  bool canProceed) {
    auto formatVec = [](const vector<int>& vec) {
        string s;
        for (int val : vec) s += to_string(val) + " ";
        return s;
    };

    cout << left << setw(6) << step
         << "P" + to_string(pid) << "   "
         << setw(15) << formatVec(workBefore)
         << setw(15) << formatVec(need)
         << setw(15) << formatVec(allocation)
         << setw(15) << formatVec(workAfter)
         << setw(12) << (canProceed ? "Yes" : "No") << "\n";
}

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);

    cout << "\nEnter Allocation matrix:\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; ++j) cin >> allocation[i][j];
    }

    cout << "\nEnter Maximum (Requirement) matrix:\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; ++j) cin >> max[i][j];
    }

    cout << "\nEnter Available resources:\n";
    for (int i = 0; i < m; ++i) cin >> available[i];

    // Calculate Need matrix
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            need[i][j] = max[i][j] - allocation[i][j];

    // Display initial table
    printInitialTable(allocation, max, need, available);

    // Safety algorithm
    vector<bool> finish(n, false);
    vector<int> work = available;
    vector<int> safeSequence;
    int step = 1;

    printStepTableHeader(m);

    bool foundProcess;
    do {
        foundProcess = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    vector<int> workBefore = work;
                    for (int j = 0; j < m; ++j) work[j] += allocation[i][j];
                    printStepRow(step++, i, workBefore, need[i], allocation[i], work, true);
                    finish[i] = true;
                    safeSequence.push_back(i);
                    foundProcess = true;
                    break;
                }
            }
        }
    } while (foundProcess);

    bool isSafe = true;
    for (bool done : finish) {
        if (!done) {
            isSafe = false;
            break;
        }
    }

    if (isSafe) {
        cout << "\nSafe Sequence: ";
        for (int i = 0; i < safeSequence.size(); ++i) {
            cout << "P" << safeSequence[i];
            if (i != safeSequence.size() - 1) cout << " -> ";
        }
        cout << "\nSystem is in a SAFE state.\n";
    } else {
        cout << "\nSystem is in an UNSAFE state. No safe sequence found.\n";
    }

    return 0;
}
