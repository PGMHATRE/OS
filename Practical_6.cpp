#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void firstFit(vector<int> blocks, vector<int> processes) {
    cout << "\nFirst Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        if (processes[i] <= 0) {
            throw runtime_error("Process size must be positive");
        }
    }
    for (int i = 0; i < processes.size(); i++) {
        bool allocated = false;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                cout << "Process " << i + 1 << " of size " << processes[i] << " allocated to block " << j + 1 << "\n";
                blocks[j] -= processes[i];
                allocated = true;
                break;
            }
        }
        if (!allocated)
            cout << "Process " << i + 1 << " of size " << processes[i] << " not allocated\n";
    }
}

void bestFit(vector<int> blocks, vector<int> processes) {
    cout << "\nBest Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        if (processes[i] <= 0) {
            throw runtime_error("Process size must be positive");
        }
    }
    for (int i = 0; i < processes.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            cout << "Process " << i + 1 << " of size " << processes[i] << " allocated to block " << bestIdx + 1 << "\n";
            blocks[bestIdx] -= processes[i];
        } else {
            cout << "Process " << i + 1 << " of size " << processes[i] << " not allocated\n";
        }
    }
}

void worstFit(vector<int> blocks, vector<int> processes) {
    cout << "\nWorst Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        if (processes[i] <= 0) {
            throw runtime_error("Process size must be positive");
        }
    }
    for (int i = 0; i < processes.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            cout << "Process " << i + 1 << " of size " << processes[i] << " allocated to block " << worstIdx + 1 << "\n";
            blocks[worstIdx] -= processes[i];
        } else {
            cout << "Process " << i + 1 << " of size " << processes[i] << " not allocated\n";
        }
    }
}

void nextFit(vector<int> blocks, vector<int> processes) {
    cout << "\nNext Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        if (processes[i] <= 0) {
            throw runtime_error("Process size must be positive");
        }
    }
    int pos = 0; // keeps track of last allocated position
    for (int i = 0; i < processes.size(); i++) {
        bool allocated = false;
        int count = 0;
        while (count < blocks.size()) {
            if (blocks[pos] >= processes[i]) {
                cout << "Process " << i + 1 << " of size " << processes[i] << " allocated to block " << pos + 1 << "\n";
                blocks[pos] -= processes[i];
                allocated = true;
                  pos = (pos + 1) % blocks.size();
                
                break;
            }
            pos = (pos + 1) % blocks.size(); // circular traversal
            count++;
        }
        if (!allocated)
            cout << "Process " << i + 1 << " of size " << processes[i] << " not allocated\n";
    }
}

int main() {
    vector<int> blocks = {100, 500, 200, 300, 600};
    vector<int> processes = {212, 417, 112, 426};

    firstFit(blocks, processes);
    bestFit(blocks, processes);
    worstFit(blocks, processes);
    nextFit(blocks, processes);

    return 0;
}