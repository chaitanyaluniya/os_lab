#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void cscan(vector<int>& requests, int head, int diskSize) {
    vector<int> left, right;
    vector<int> order;

    for (int req : requests) {
        if (req >= head) right.push_back(req);
        else left.push_back(req);
    }

    // Add end points
    right.push_back(diskSize - 1);
    left.push_back(0);

    sort(right.begin(), right.end());
    sort(left.begin(), left.end());

    int seekCount = 0;
    int current = head;

    cout << "\nCurrent\tNext\tDiff\n";

    // Service the right side
    for (int req : right) {
        int diff = abs(current - req);
        cout << current << "\t" << req << "\t" << diff << endl;
        seekCount += diff;
        current = req;
        order.push_back(current);
    }

    // Jump from end to start (circular)
    int jump = (diskSize - 1);
    cout << current << "\t0\t" << jump << " (Jump to start)\n";
    seekCount += jump;
    current = 0;

    // Service the left side
    for (int req : left) {
        int diff = abs(current - req);
        cout << current << "\t" << req << "\t" << diff << endl;
        seekCount += diff;
        current = req;
        order.push_back(current);
    }

    cout << "\nTotal seek operations: " << seekCount << endl;
    cout << "Average seek time: " << (float)seekCount / requests.size() << endl;
}

int main() {
    vector<int> requests = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int diskSize = 200;

    cscan(requests, head, diskSize);

    return 0;
}
