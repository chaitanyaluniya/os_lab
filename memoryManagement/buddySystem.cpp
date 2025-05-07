#include <iostream>
#include <cmath>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

int totalMemory;
map<int, list<int>> freeList;           
map<int, int> allocatedBlocks;          

int nextPowerOf2(int n) {
    return pow(2, ceil(log2(n)));
}

void showMemoryMap() {
    cout << "\n========= Memory Map =========\n";

    // Collect all free and used blocks
    map<int, string> statusMap;

    for (auto& [size, blocks] : freeList) {
        for (int addr : blocks) {
            statusMap[addr] = "Free (" + to_string(size) + " KB)";
        }
    }

    for (auto& [addr, size] : allocatedBlocks) {
        statusMap[addr] = "Used (" + to_string(size) + " KB)";
    }

    for (auto& [addr, status] : statusMap) {
        cout << "[ Addr: " << addr << " ] --> " << status << endl;
    }

    cout << "==============================\n";
}

int allocate(int size) {
    int actualSize = nextPowerOf2(size);
    int currSize = actualSize;

    // Find the smallest fitting block
    while (currSize <= totalMemory && freeList[currSize].empty()) {
        currSize *= 2;
    }

    if (currSize > totalMemory || freeList[currSize].empty()) {
        cout << "Not enough memory to allocate " << size << " KB\n";
        return -1;
    }

    // Start splitting
    int addr = freeList[currSize].front();
    freeList[currSize].pop_front();

    while (currSize > actualSize) {
        currSize /= 2;
        freeList[currSize].push_back(addr + currSize);
    }

    allocatedBlocks[addr] = actualSize;
    cout << "Allocated " << actualSize << " KB at address " << addr << endl;
    return addr;
}

void deallocate(int addr) {
    if (allocatedBlocks.find(addr) == allocatedBlocks.end()) {
        cout << " Address not found in allocated blocks.\n";
        return;
    }

    int size = allocatedBlocks[addr];
    allocatedBlocks.erase(addr);

    bool merged = true;
    int actualSize = size;

    while (merged && actualSize < totalMemory) {
        int buddyAddr = addr ^ actualSize;
        auto& buddyList = freeList[actualSize];
        auto it = find(buddyList.begin(), buddyList.end(), buddyAddr);

        if (it != buddyList.end()) {
            buddyList.erase(it);
            addr = min(addr, buddyAddr);
            actualSize *= 2;
        } else {
            merged = false;
        }
    }

    freeList[actualSize].push_back(addr);
    cout << "Deallocated " << size << " KB from address " << addr << endl;
}

void menu() {
    int choice;
    while (true) {
        cout << "\n======= Buddy System Menu =======\n";
        cout << "1. Allocate Memory\n";
        cout << "2. Deallocate Memory\n";
        cout << "3. Show Memory Map\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int size;
            cout << "Enter size to allocate (in KB): ";
            cin >> size;
            allocate(size);
        } else if (choice == 2) {
            int addr;
            cout << "Enter address to deallocate: ";
            cin >> addr;
            deallocate(addr);
        } else if (choice == 3) {
            showMemoryMap();
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    cout << "Enter total memory size (in KB, power of 2): ";
    cin >> totalMemory;

    if ((totalMemory & (totalMemory - 1)) != 0) {
        cout << " Memory size must be a power of 2.\n";
        return 1;
    }

    freeList[totalMemory].push_back(0);
    menu();

    return 0;
}
