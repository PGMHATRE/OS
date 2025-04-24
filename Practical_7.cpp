// void lru(vector<int>& pages, int framesize)
// {
//     int index = -1;
//     vector<int> frame;
//     int pagefault = 0;

//     for(int i = 0; i < pages.size(); i++)
//     {
//         bool found = false;

//         for(int j = 0; j < frame.size(); j++)  // fixed loop condition
//         {
//             if(frame[j] == pages[i])
//             {
//                 found = true;
//                 index = j;
//                 break;
//             }
//         }

//         if(found)
//         {
//             int recent = frame[index];
//             frame.erase(frame.begin() + index);
//             frame.push_back(recent);
//         }
//         else
//         {
//             pagefault++;
//             if(frame.size() == framesize)
//             {
//                 frame.erase(frame.begin());
//             }
//             frame.push_back(pages[i]);
//         }

//         for(int k = 0; k < frame.size(); k++)
//         {
//             cout << frame[k] << " ";
//         }
//         cout << endl;
//     }

//     cout << "page fault: " << pagefault << endl;
// }




// void optimal(vector<int>& pages, int framesize)
// {
//     vector<int> frame;
//     int pagefault = 0;

//     for(int i = 0; i < pages.size(); i++)
//     {
//         bool found = false;

//         for(int j = 0; j < frame.size(); j++)
//         {
//             if(pages[i] == frame[j])
//             {
//                 found = true;
//                 break;
//             }
//         }

//         if(!found)
//         {
//             pagefault++;

//             if(frame.size() == framesize) // 🛠 Only replace if frame is full
//             {
//                 int index = -1;
//                 int far = i + 1;

//                 for(int j = 0; j < frame.size(); j++)
//                 { 
//                     int k;
//                     for(k = i + 1; k < pages.size(); k++)
//                     {
//                         if(pages[k] == frame[j])
//                             break;
//                     }

//                     if(k == pages.size())
//                     {
//                         index = j;
//                         break;
//                     }

//                     if(k > far)
//                     {
//                         far = k;
//                         index = j;
//                     }
//                 }

//                 if(index == -1)
//                     index = 0;

//                 frame.erase(frame.begin() + index);
//             }

//             frame.push_back(pages[i]);
//         }

//         for(int k = 0; k < frame.size(); k++)
//             cout << frame[k] << " ";
//         cout << endl;
//     }

//     cout << "page fault " << pagefault << endl;
// }





#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isframe(vector<int>&frame, int page) {
    return find(frame.begin(), frame.end(), page) != frame.end();
}

// FCFS Page Replacement
void FCFS(vector<int>& page, int frameSize) {
    vector<int> frame;
    int pageFault = 0;
    cout << "\nFCFS Page Replacement:\n";

    for (int i = 0; i < page.size(); i++) {
        bool found = false;
        for (int j = 0; j < frame.size(); j++) {
            if (frame[j] == page[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            pageFault++;
            if (frame.size() == frameSize) {
                frame.erase(frame.begin());
            }
            frame.push_back(page[i]);
        }

        for (int j = 0; j < frame.size(); j++) {
            cout << frame[j] << " ";
        }
        cout << endl;
    }

    cout << "Total Page Faults (FCFS): " << pageFault << "\n";
}



void LRU(vector<int>& page, int frameSize) {
    vector<int> frame;
    int pageFault = 0;
    cout << "\nLRU Page Replacement:\n";

    for (int i = 0; i < page.size(); i++) {
        int currentPage = page[i];
        bool found = false;
        for (int j = 0; j < frame.size(); j++) {
            if (frame[j] == currentPage) {
                found = true;
                frame.erase(frame.begin() + j);
                break;
            }
        }

        if (!found) {
            pageFault++;
            if (frame.size() == frameSize) {
                frame.erase(frame.begin());
            }
        }

        frame.push_back(currentPage);

        for (int j = 0; j < frame.size(); j++) {
            cout << frame[j] << " ";
        }
        cout << endl;
    }

    cout << "Total Page Faults (LRU): " << pageFault << "\n";
}


// // Optimal Page Replacement
// void Optimal(vector<int>&page, int frameSize) {
//     vector<int> frame;
//     int pagefault = 0;
//     cout << "\nOptimal Page Replacement:\n";
//     int index = 0;

//     for (int p : page) {
//         if (!isframe(frame, p)) {
//             pagefault++;
//             if (frame.size() < frameSize) {
//                 frame.push_back(p);
//             } else {
//                 int farthest = -1;
//                 int indexToReplace = -1;

//                 for (int i = 0; i < frame.size(); i++) {
//                     int nextUse = -1;
//                     for (int j = index + 1; j < page.size(); j++) {
//                         if (page[j] == frame[i]) {
//                             nextUse = j;
//                             break;
//                         }
//                     }

//                     if (nextUse == -1) {
//                         indexToReplace = i;
//                         break;
//                     } else if (nextUse > farthest) {
//                         farthest = nextUse;
//                         indexToReplace = i;
//                     }
//                 }

//                 frame[indexToReplace] = p;
//             }
//         }

//         for (int f : frame) {
//             cout << f << " ";
//         }
//         cout << endl;

//         index++;
//     }

//     cout << "Total Page Faults (Optimal): " << pagefault << "\n";
// }
// void Optimal(vector<int>& pages, int frameSize) {
//     vector<int> frame;
//     int pageFaults = 0;

//     cout << "\nOptimal Page Replacement:\n";

//     for (int current = 0; current < pages.size(); current++) {
//         int page = pages[current];

//         // If the page is already in frame, no page fault
//         if (find(frame.begin(), frame.end(), page) != frame.end()) {
//             // Just show the frame
//         } else {
//             pageFaults++;

//             if (frame.size() < frameSize) {
//                 // Space is available, just insert the page
//                 frame.push_back(page);
//             } else {
//                 // Find the page in frame that is used farthest in the future
//                 int farthestIndex = -1;
//                 int replaceIndex = -1;

//                 for (int i = 0; i < frame.size(); i++) {
//                     int j;
//                     for (j = current + 1; j < pages.size(); j++) {
//                         if (pages[j] == frame[i]) break;
//                     }

//                     if (j == pages.size()) {
//                         // Page not used again, replace this one
//                         replaceIndex = i;
//                         break;
//                     } else if (j > farthestIndex) {
//                         farthestIndex = j;
//                         replaceIndex = i;
//                     }
//                 }

//                 // Replace the selected page
//                 frame[replaceIndex] = page;
//             }
//         }

//         // Print current frame content
//         for (int f : frame) {
//             cout << f << " ";
//         }
//         cout << endl;
//     }

//     cout << "Total Page Faults (Optimal): " << pageFaults << "\n";
// }
void optimal(vector<int>& pages, int framesize)
{
    vector<int> frame;
    int pagefault = 0;

    for(int i = 0; i < pages.size(); i++)
    {
        bool found = false;

        for(int j = 0; j < frame.size(); j++)
        {
            if(frame[j] == pages[i])
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            pagefault++;
            if(frame.size() == framesize)
            {
                // Find the page in frame that won't be used for the longest time
                int replaceIndex = -1, farthest = i + 1;

                for(int j = 0; j < frame.size(); j++)
                {
                    int k;
                    for(k = i + 1; k < pages.size(); k++)
                    {
                        if(pages[k] == frame[j])
                            break;
                    }

                    if(k == pages.size())  // not used again
                    {
                        replaceIndex = j;
                        break;
                    }

                    if(k > farthest)
                    {
                        farthest = k;
                        replaceIndex = j;
                    }
                }

                if (replaceIndex == -1) {
                      replaceIndex = 0; // fallback
                }
                frame.erase(frame.begin() + replaceIndex);

            }

            frame.push_back(pages[i]);
        }

        for(int k = 0; k < frame.size(); k++)
        {
            cout << frame[k] << " ";
        }
        cout << endl;
    }

    cout << "page fault: " << pagefault << endl;
}

int main() {
    vector<int> pages = {7, 6, 1, 2, 4, 3, 1, 4 };
    int frameSize = 3;

    FCFS(pages, frameSize);
    LRU(pages, frameSize);
    optimal(pages, frameSize);

    return 0;
}
