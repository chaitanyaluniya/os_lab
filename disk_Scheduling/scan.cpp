#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void scanAlgo(vector<int>& request, int head, int disk_size, string direction) {
    vector<int> left, right, seek_sequence;
    int seekTime = 0;

    if (direction == "left") left.push_back(0);
    if (direction == "right") right.push_back(disk_size - 1);

    for (int req : request) {
        if (req < head) left.push_back(req);
        else right.push_back(req);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\nCurrent\tNext\tDiff\n";

    if (direction == "left") {
        reverse(left.begin(), left.end());
        for (int track : left) {
            cout << head << "\t" << track << "\t" << abs(track - head) << endl;
            seek_sequence.push_back(track);
            seekTime += abs(head - track);
            head = track;
        }
        for (int track : right) {
            cout << head << "\t" << track << "\t" << abs(track - head) << endl;
            seek_sequence.push_back(track);
            seekTime += abs(head - track);
            head = track;
        }
    } else if (direction == "right") {
        for (int track : right) {
            cout << head << "\t" << track << "\t" << abs(track - head) << endl;
            seek_sequence.push_back(track);
            seekTime += abs(head - track);
            head = track;
        }
        reverse(left.begin(), left.end());
        for (int track : left) {
            cout << head << "\t" << track << "\t" << abs(track - head) << endl;
            seek_sequence.push_back(track);
            seekTime += abs(head - track);
            head = track;
        }
    }

    cout << "\nSeek Sequence: ";
    for (int track : seek_sequence) {
        cout << track << " ";
    }

    cout << "\nTotal Seek Time: " << seekTime << endl;
}

int main() {
    int n, head, disk_size;
    string direction;

    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> request(n);
    cout << "Enter the disk requests:\n";
    for (int i = 0; i < n; i++) {
        cin >> request[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    cout << "Enter the total disk size: ";
    cin >> disk_size;

    cout << "Enter the direction (left/right): ";
    cin >> direction;

    scanAlgo(request, head, disk_size, direction);

    return 0;
}
