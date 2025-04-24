#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calculateSeekTime(vector<int> requests, int head) {
    int seekTime = 0;
    for (int i = 0; i < requests.size(); i++) {
        seekTime += abs(requests[i] - head);
        head = requests[i];
    }
    return seekTime;
}

void fcfs(vector<int> requests, int head) {
    cout << "\nFCFS Order: ";
    for (int i = 0; i < requests.size(); i++) {
        cout << requests[i] << " ";
    }
    cout << "\nTotal Seek Time: " << calculateSeekTime(requests, head) << endl;
}

void sstf(vector<int> requests, int head) {
    vector<int> order;
    vector<bool> visited(requests.size(), false);
    int initialHead = head;

    for (int i = 0; i < requests.size(); i++) {
        int minDistance = 1e9;
        int index = -1;

        for (int j = 0; j < requests.size(); j++) {
            if (!visited[j] && abs(requests[j] - head) < minDistance) {
                minDistance = abs(requests[j] - head);
                index = j;
            }
        }

        visited[index] = true;
        order.push_back(requests[index]);
        head = requests[index];
    }

    cout << "\nSSTF Order: ";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i] << " ";
    }
    cout << "\nTotal Seek Time: " << calculateSeekTime(order, initialHead) << endl;
}


void scan(vector<int> requests, int head, int totalCylinders) {
    vector<int> left, right;

    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] > head)
            right.push_back(requests[i]);
        else
            left.push_back(requests[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    vector<int> order;
    for (int i = 0; i < right.size(); i++) {
        order.push_back(right[i]);
    }

    order.push_back(totalCylinders - 1);

    for (int i = left.size() - 1; i >= 0; i--) {
        order.push_back(left[i]);
    }

    cout << "\nSCAN Order: ";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i] << " ";
    }

    cout << "\nTotal Seek Time: " << calculateSeekTime(order, head) << endl;
}

void cscan(vector<int> requests, int head, int totalCylinders) {
    vector<int> left, right;

    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] > head)
            right.push_back(requests[i]);
        else
            left.push_back(requests[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    vector<int> order;
    for (int i = 0; i < right.size(); i++) {
        order.push_back(right[i]);
    }

    order.push_back(totalCylinders - 1);
    order.push_back(0);

    for (int i = 0; i < left.size(); i++) {
        order.push_back(left[i]);
    }

    cout << "\nC-SCAN Order: ";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i] << " ";
    }

    cout << "\nTotal Seek Time: " << calculateSeekTime(order, head) << endl;
}


int main() {
    int numRequests;
    cout << "Enter number of requests: ";
    cin >> numRequests;

    vector<int> requests(numRequests);
    cout << "Enter the request queue: ";
    for (int i = 0; i < numRequests; i++) {
        cin >> requests[i];
    }

    int headPosition;
    cout << "Enter initial head position: ";
    cin >> headPosition;

    int totalCylinders;
    cout << "Enter total number of cylinders: ";
    cin >> totalCylinders;

    fcfs(requests, headPosition);
    sstf(requests, headPosition);
    scan(requests, headPosition, totalCylinders);
    cscan(requests, headPosition, totalCylinders);

    return 0;
}
