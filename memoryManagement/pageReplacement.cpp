#include <iostream>
using namespace std;

void fifo(int pages[], int n, int capacity) {
    int frames[100], size = 0, pageFaults = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (size < capacity) {
                frames[size++] = pages[i];
            } else {
                for (int j = 1; j < capacity; j++)
                frames[j - 1] = frames[j];
                frames[capacity - 1] = pages[i];
            }
            pageFaults++;
        }
    }

    cout << "FIFO Page Faults: " << pageFaults << endl;
}

void lru(int pages[], int n, int capacity) {
    int frames[100], age[100], size = 0, pageFaults = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;

        for (int j = 0; j < size; j++) {
            age[j]++;
            if (frames[j] == pages[i]) {
                age[j] = 0;
                found = true;
            }
        }

        if (!found) {
            if (size < capacity) {
                frames[size] = pages[i];
                age[size] = 0;
                size++;
            } else {
                int oldest = 0;
                for (int j = 1; j < capacity; j++) {
                    if (age[j] > age[oldest])
                        oldest = j;
                }
                frames[oldest] = pages[i];
                age[oldest] = 0;
            }
            pageFaults++;
        }
    }

    cout << "LRU Page Faults: " << pageFaults << endl;
}

int predict(int pages[], int frames[], int n, int index, int capacity) {
    int res = -1, farthest = index;
    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimal(int pages[], int n, int capacity) {
    int frames[100], size = 0, pageFaults = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (size < capacity) {
                frames[size++] = pages[i];
            } else {
                int pos = predict(pages, frames, n, i + 1, capacity);
                frames[pos] = pages[i];
            }
            pageFaults++;
        }
    }

    cout << "Optimal Page Faults: " << pageFaults << endl;
}

int main() {
    int choice, n, capacity, pages[100];

    cout << "Enter number of pages: ";
    cin >> n;
    cout << "Enter the pages: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter frame capacity: ";
    cin >> capacity;

    cout << "\nChoose Page Replacement Algorithm:\n";
    cout << "1. FIFO\n";
    cout << "2. LRU\n";
    cout << "3. Optimal\n";
    cout << "Enter choice (1-3): ";
    cin >> choice;

    switch (choice) {
        case 1:
            fifo(pages, n, capacity);
            break;
        case 2:
            lru(pages, n, capacity);
            break;
        case 3:
            optimal(pages, n, capacity);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}

// 7 0 1 2 0 3 0 4