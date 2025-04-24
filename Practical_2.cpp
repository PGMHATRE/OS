// Write a program to implement scheduling algorithms – FCFS, SJF, Round Robin and Priority


//FCFS

#include <iostream>
#include <algorithm>
using namespace std;

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
};

// Sort by arrival time
bool compareArrival(Process a, Process b) {
    return a.arrival_time < b.arrival_time;
}

int main() {
    const int n = 5;
    Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Arrival Time and Burst Time for process " << i+1 << ": ";
        cin >> p[i].pid >> p[i].arrival_time >> p[i].burst_time;
    }

    // Sort processes by arrival time
    sort(p, p + n, compareArrival);

    int completion_time[n], turnaround_time[n], waiting_time[n];
    float total_tt = 0, total_wt = 0;

    // Completion time calculation
    completion_time[0] = p[0].arrival_time + p[0].burst_time;
    for (int i = 1; i < n; i++) {
        if (completion_time[i-1] < p[i].arrival_time)
            completion_time[i] = p[i].arrival_time + p[i].burst_time;
        else
            completion_time[i] = completion_time[i-1] + p[i].burst_time;
    }

    // Turnaround time = completion - arrival
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - p[i].arrival_time;
        total_tt += turnaround_time[i];
    }

    // Waiting time = turnaround - burst
    for (int i = 0; i < n; i++) {
        waiting_time[i] = turnaround_time[i] - p[i].burst_time;
        total_wt += waiting_time[i];
    }

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t"
             << completion_time[i] << "\t" << turnaround_time[i] << "\t" << waiting_time[i] << "\n";
    }

    cout << "\nAverage Turnaround Time: " << total_tt / n << endl;
    cout << "Average Waiting Time   : " << total_wt / n << endl;

    return 0;
}

//Priority 

#include <iostream>
#include <algorithm>
using namespace std;

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int priority; // Added priority field
};

// Sort by priority (higher priority first), and by arrival time in case of tie
bool comparePriority(Process a, Process b) {
    if (a.priority == b.priority) {
        return a.arrival_time < b.arrival_time; // If same priority, sort by arrival time
    }
    return a.priority < b.priority; // Higher priority first
}

int main() {
    const int n = 5;
    Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Arrival Time, Burst Time, and Priority for process " << i+1 << ": ";
        cin >> p[i].pid >> p[i].arrival_time >> p[i].burst_time >> p[i].priority; // Input priority
    }

    // Sort processes by priority (and arrival time in case of tie)
    sort(p, p + n, comparePriority);

    int completion_time[n], turnaround_time[n], waiting_time[n];
    float total_tt = 0, total_wt = 0;

    // Completion time calculation
    completion_time[0] = p[0].arrival_time + p[0].burst_time;
    for (int i = 1; i < n; i++) {
        if (completion_time[i-1] < p[i].arrival_time)
            completion_time[i] = p[i].arrival_time + p[i].burst_time;
        else
            completion_time[i] = completion_time[i-1] + p[i].burst_time;
    }

    // Turnaround time = completion - arrival
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - p[i].arrival_time;
        total_tt += turnaround_time[i];
    }

    // Waiting time = turnaround - burst
    for (int i = 0; i < n; i++) {
        waiting_time[i] = turnaround_time[i] - p[i].burst_time;
        total_wt += waiting_time[i];
    }

    // Output
    cout << "\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t"
             << p[i].priority << "\t\t" << completion_time[i] << "\t" << turnaround_time[i] << "\t" << waiting_time[i] << "\n";
    }

    cout << "\nAverage Turnaround Time: " << total_tt / n << endl;
    cout << "Average Waiting Time   : " << total_wt / n << endl;

    return 0;
}


//Round Robin

#include <iostream>
#include <queue>
using namespace std;

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

int main() {
    const int n = 5;
    Process p[n];
    int quantum = 2;

    // Input
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Arrival Time and Burst Time for process " << i + 1 << ": ";
        cin >> p[i].pid >> p[i].arrival_time >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time; // initialize remaining time
    }

    int time = 0;
    int completed = 0;
    int ct[n], tat[n], wt[n];
    bool visited[n] = {false};
    queue<int> q;

    // Push first arrived process
    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time == 0) {
            q.push(i);
            visited[i] = true;
        }
    }

    while (completed < n) {
        if (!q.empty()) {
            int i = q.front();
            q.pop();

            int exec_time = min(quantum, p[i].remaining_time);
            time += exec_time;
            p[i].remaining_time -= exec_time;

            // Check for new arrivals
            for (int j = 0; j < n; j++) {
                if (!visited[j] && p[j].arrival_time <= time) {
                    q.push(j);
                    visited[j] = true;
                }
            }

            if (p[i].remaining_time == 0) {
                ct[i] = time;
                completed++;
            } else {
                q.push(i); // put back for next round
            }
        } else {
            time++; // idle time
        }
    }

    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - p[i].arrival_time;
        wt[i] = tat[i] - p[i].burst_time;
        total_tat += tat[i];
        total_wt += wt[i];
    }

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time   : " << total_wt / n << endl;

    return 0;
}


//sjf

#include <iostream>
using namespace std;

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    bool completed;
};

int main() {
    const int n = 5;
    Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Arrival Time and Burst Time for process " << i + 1 << ": ";
        cin >> p[i].pid >> p[i].arrival_time >> p[i].burst_time;
        p[i].completed = false;
    }

    int time = 0, completed = 0;
    int ct[n], tat[n], wt[n];
    float total_tat = 0, total_wt = 0;

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival_time <= time && p[i].burst_time < min_bt) {
                min_bt = p[i].burst_time;
                idx = i;
            }
        }

        if (idx != -1) {
            time += p[idx].burst_time;
            ct[idx] = time;
            p[idx].completed = true;
            completed++;
        } else {
            time++;  // No process is ready to run
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - p[i].arrival_time;
        wt[i] = tat[i] - p[i].burst_time;
        total_tat += tat[i];
        total_wt += wt[i];
    }

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time   : " << total_wt / n << endl;

    return 0;
}


//pre -sjf

#include <iostream>
using namespace std;

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    bool completed;
};

int main() {
    const int n = 3;
    Process p[n];
    
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Arrival Time and Burst Time for process " << i + 1 << ": ";
        cin >> p[i].pid >> p[i].arrival_time >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = false;
    }

    int time = 0, completed = 0;
    int ct[n], tat[n], wt[n];

    while (completed < n) {
        int idx = -1;
        int min_rt = 1e9;

        // Find process with shortest remaining time at current time
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival_time <= time && p[i].remaining_time < min_rt && p[i].remaining_time > 0) {
                min_rt = p[i].remaining_time;
                idx = i;
            }
        }

        if (idx != -1) {
            // Run for 1 unit time
            p[idx].remaining_time--;
            time++;

            // If process is finished
            if (p[idx].remaining_time == 0) {
                p[idx].completed = true;
                ct[idx] = time;
                completed++;
            }
        } else {
            time++;  // No process ready, idle time
        }
    }

    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - p[i].arrival_time;
        wt[i] = tat[i] - p[i].burst_time;
        total_tat += tat[i];
        total_wt += wt[i];
    }

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time   : " << total_wt / n << endl;

    return 0;
}
//priority preemtive

#include <iostream>
using namespace std;

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    bool completed;
};

int main() {
    const int n = 5;
    Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Arrival Time, Burst Time, and Priority for process " << i + 1 << ": ";
        cin >> p[i].pid >> p[i].arrival_time >> p[i].burst_time >> p[i].priority;
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = false;
    }

    int time = 0, completed = 0;
    int ct[n], tat[n], wt[n];

    while (completed < n) {
        int idx = -1;
        int min_priority = 1e9;

        // Select process with highest priority (lowest value), if arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival_time <= time && p[i].remaining_time > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            // Execute process for 1 unit
            p[idx].remaining_time--;
            time++;

            // Completion check
            if (p[idx].remaining_time == 0) {
                p[idx].completed = true;
                ct[idx] = time;
                completed++;
            }
        } else {
            time++; // Idle
        }
    }

    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - p[i].arrival_time;
        wt[i] = tat[i] - p[i].burst_time;
        total_tat += tat[i];
        total_wt += wt[i];
    }

    // Output
    cout << "\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t"
             << p[i].priority << "\t\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time   : " << total_wt / n << endl;

    return 0;
}
