#include <iostream>
using namespace std;

int main() {
    int n = 5; // Number of processes
    int r = 3; // Number of resources

    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maxm[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {4, 2, 2},
        {5, 3, 3}
    };

    int avail[3] = {3, 3, 2};

    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }

    int need[n][r];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = maxm[i][j] - alloc[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < r; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
        
        
        
    }

    cout << "The Safe Sequence is :" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << ans[i] << " -> ";
    }

    return 0;
}










// int n,r;

// cout<<"n and r"<<endl;
// cin>>n>>r;

// int alloc[n][r];
// cout<<"allocate"<<endl;

// for(int p=0;p<n;p++)
// {
//     for(int m=0;m<r;m++)
//     {
//       cin>>alloc[p][m]; 
//     }
// }




// int maxm[n][r];
// cout<<"allocate"<<endl;
// for(int z=0;z<n;z++)
// {
//     for(int x=0;x<r;x++)
//     {
//       cin>>maxm[z][x]; 
//     }
// }























// All safe Sequencence 


#include <iostream>
using namespace std;

int n = 5; // Number of processes
int r = 3; // Number of resources

int alloc[5][3] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int maxm[5][3] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {4, 2, 2},
    {5, 3, 3}
};

int avail[3] = {3, 3, 2};

int need[5][3];
int ans[5];
bool f[5] = {false}; // Track finished processes

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];
}

void printAllSafeSequences(int index) {
    if (index == n) {
        // Print current safe sequence
        for (int i = 0; i < n; i++) {
            cout << "P" << ans[i];
            if (i != n - 1) cout << " -> ";
        }
        cout << endl;
        return;
    }

    
}
for (int i = 0; i < n; i++) {
        if (!f[i]) {
            bool canRun = true;
            for (int j = 0; j < r; j++) {
                if (need[i][j] > avail[j]) {
                    canRun = false;
                    break;
                }
            }

            if (canRun) {
                // Simulate running process i
                for (int j = 0; j < r; j++) avail[j] += alloc[i][j];
                f[i] = true;
                ans[index] = i;

                printAllSafeSequences(index + 1);

                // Backtrack
                for (int j = 0; j < r; j++) avail[j] -= alloc[i][j];
                f[i] = false;
            }
        }
    }

int main() {
    calculateNeed();
    cout << "All possible safe sequences are:\n";
    printAllSafeSequences(0);
    return 0;
}

