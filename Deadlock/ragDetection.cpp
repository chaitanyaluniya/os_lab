
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class RAG {
    int V; 
    vector<vector<int>> adj;
    unordered_map<string, int> nodeIndex;
    vector<string> indexToName;
    int index = 0;

public:
    RAG(int total) : V(total) {
        adj.resize(total);
        indexToName.resize(total);
    }

    void addNode(string name) {
        nodeIndex[name] = index;
        indexToName[index] = name;
        index++;
    }

    void addEdge(string from, string to) {
        int u = nodeIndex[from];
        int v = nodeIndex[to];
        adj[u].push_back(v);
    }

    bool isCyclicUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
        visited[v] = true;
        recStack[v] = true;

        for (int u : adj[v]) {
            if (!visited[u] && isCyclicUtil(u, visited, recStack))
                return true;
            else if (recStack[u])
                return true;
        }

        recStack[v] = false;
        return false;
    }

    bool detectDeadlock() {
        vector<bool> visited(V, false), recStack(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i])
                if (isCyclicUtil(i, visited, recStack)) {
                    cout << "\nCycle detected involving node: " << indexToName[i] << "\n";
                    return true;
                }
        }
        return false;
    }
};

int main() {
    int numProcesses, numResources;
    cout << "Enter number of processes: ";
    cin >> numProcesses;
    cout << "Enter number of resources: ";
    cin >> numResources;

    int totalNodes = numProcesses + numResources;
    RAG rag(totalNodes);

    cout << "\nEnter names of processes:\n";
    vector<string> processes(numProcesses);
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i];
        rag.addNode(processes[i]);
    }

    cout << "\nEnter names of resources:\n";
    vector<string> resources(numResources);
    for (int i = 0; i < numResources; ++i) {
        cout << "Resource " << i + 1 << ": ";
        cin >> resources[i];
        rag.addNode(resources[i]);
    }

    int edges;
    cout << "\nEnter number of edges (allocation or request): ";
    cin >> edges;
    cout << "Enter edges in format: FROM TO (example: P1 R1 or R2 P2)\n";

    for (int i = 0; i < edges; ++i) {
        string from, to;
        cin >> from >> to;
        rag.addEdge(from, to);
    }

    if (rag.detectDeadlock())
        cout << "\n Deadlock detected!\n";
    else
        cout << "\n No deadlock detected. System is safe.\n";

    return 0;
}
