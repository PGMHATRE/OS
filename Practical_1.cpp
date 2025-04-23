#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

void executeCommand(char* cmd[]) {
    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        cout<<"Fork failed";
        exit(1);
    }

    if (pid == 0) {
        // Child process
        if (execvp(cmd[0], cmd) == -1) {
            cout<<"exec failed";
            exit(1);
        }
    } else {
        // Parent process
        wait(NULL);  // Wait for the child process to finish
    }
}

int main() {
    int choice;
    cout << "Linux Command Simulation\n";
    cout << "1. cp (copy file)\n";
    cout << "2. grep (search word in file)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    char *cmd[4]; // Array to hold command and arguments
    
    if (choice == 1) {
        string src, dest;
        cout << "Enter source file: ";
        cin >> src;
        cout << "Enter destination file: ";
        cin >> dest;
        
        cmd[0] = (char*)"cp";
        cmd[1] = (char*)src.c_str();
        cmd[2] = (char*)dest.c_str();
        cmd[3] = NULL;
    }
    else if (choice == 2) {
        string pattern, filename;
        cout << "Enter word to search: ";
        cin >> pattern;
        cout << "Enter filename: ";
        cin >> filename;
        
        cmd[0] = (char*)"grep";
        cmd[1] = (char*)pattern.c_str();
        cmd[2] = (char*)filename.c_str();
        cmd[3] = NULL;
    } 
    else {
        cout << "Invalid choice!\n";
        return 1;
    }

    executeCommand(cmd);  // Execute the chosen command
    return 0;
}

