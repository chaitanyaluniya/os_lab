#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

int findShortest(int head, vector<int>& request, vector<bool>& visited) {
    int minDistance = INT_MAX;
    int index = -1;
    for (int i = 0; i < request.size(); i++) {
        if (!visited[i]) {
            int distance = abs(request[i] - head);
            if (distance < minDistance) {
                minDistance = distance;
                index = i;
            }
        }
    }
    return index;
}

int main() {
    int n, head;
    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> request(n);
    vector<bool> visited(n, false);

    cout << "Enter disk requests:\n";
    for (int i = 0; i < n; i++) {
        cin >> request[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    int totalMovement = 0;
    cout << "\nCurrent\tNext\tDiff\n";

    for (int i = 0; i < n; i++) {
        int index = findShortest(head, request, visited);
        if (index == -1) break;

        int diff = abs(request[index] - head);
        cout << head << "\t" << request[index] << "\t" << diff << endl;

        totalMovement += diff;
        head = request[index];
        visited[index] = true;
    }

    cout << "\nTotal Seek Time: " << totalMovement << endl;
    return 0;
}
