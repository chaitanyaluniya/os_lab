#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main() {
    int head, n;
    cout << "Enter the total number of disk requests: ";
    cin >> n;

    vector<int> request(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter disk request (track number): ";
        cin >> request[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    int totalMovement = 0;
    cout << "\nService Order and Details:\n";
    cout << "Current\tNext\tDiff\n";

    for (int i = 0; i < n; i++) {
        int diff = abs(request[i] - head);
        cout << head << "\t" << request[i] << "\t" << diff << endl;
        totalMovement += diff;
        head = request[i];
    }

    cout << "\nTotal Seek Time: " << totalMovement << endl;
    return 0;
}
