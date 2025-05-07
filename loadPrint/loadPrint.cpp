#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class OS {
private:
    char M[100][4];
    char buffer[80];
    fstream infile;
    ofstream outfile;

public:
    void LOAD();
    void PRINTMEMORY();
    void setInputFile(const string& filename);
    void setOutputFile(const string& filename);
};

void OS::setInputFile(const string& filename) {
    infile.open(filename, ios::in);
    if (!infile) {
        cout << "Failure: File not found!" << endl;
        exit(1);
    }
}


void OS::LOAD() {
    cout << "Reading Input File..." << endl;

    int memIndex = 0;

    while (infile.getline(buffer, 80)) {
        if (strncmp(buffer, "$AMJ", 4) == 0) {
            // Clear memory
            for (int i = 0; i < 100; i++)
                for (int j = 0; j < 4; j++)
                    M[i][j] = ' ';
            memIndex = 0;
        }
        else if (strncmp(buffer, "$DTA", 4) == 0) {
            // Stop loading code
            break;
        }
        else if (strncmp(buffer, "$END", 4) == 0) {
            continue;
        }
        else {
            // Load instructions in 4-char chunks
            int len = strlen(buffer);
            for (int i = 0; i < len; i += 4) {
                for (int j = 0; j < 4; j++) {
                    if (i + j < len)
                        M[memIndex][j] = buffer[i + j];
                    else
                        M[memIndex][j] = ' ';
                }
                memIndex++;
            }
        }
    }

    infile.close();
}

void OS::PRINTMEMORY() {
    cout << "\nMemory Dump:\n";
    outfile << "\nMemory Dump:\n"; // Write header to output file
    for (int i = 0; i < 100; i++) {
        cout << "[" << i << "] ";
        outfile << "[" << i << "] "; // Write to output file
        for (int j = 0; j < 4; j++) {
            cout << M[i][j];
            outfile << M[i][j]; // Write each character to output file
        }
        cout << endl;
        outfile << endl;
    }
}

int main() {
    OS os;
    os.setInputFile("input.txt");
    os.setOutputFile("output.txt"); // Set output file to write memory dump
    os.LOAD();
    os.PRINTMEMORY();
    return 0;
}
