#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

int main() {
    int pipe1[2]; // Parent to Child
    int pipe2[2]; // Child to Parent
    pid_t pid;
    char buffer[100];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        cout << "Pipe creation failed!" << endl;
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        cout << "Fork failed!" << endl;
        return 1;
    }

    if (pid == 0) {
        // Child Process
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2

        // Read from parent (pipe1)
        read(pipe1[0], buffer, sizeof(buffer));
        cout << "Child received: " << buffer << endl;

        // Send response to parent (pipe2)
        const char* message = "Hello from child!";
        write(pipe2[1], message, strlen(message) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
    } else {
        // Parent Process
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        // Send message to child (pipe1)
        const char* message = "Hello from parent!";
        write(pipe1[1], message, strlen(message) + 1);

        // Wait for child to process
        wait(NULL);

        // Read response from child (pipe2)
        read(pipe2[0], buffer, sizeof(buffer));
        cout << "Parent received: " << buffer << endl;

        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}