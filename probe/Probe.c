#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_PROCESSES 5

// Define wait-for graph with assigned values
int wfg[NUM_PROCESSES][NUM_PROCESSES] = {
    {0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0}
};

int *visited;

// Function declaration
bool probe_dd(int sender, int target, int visited_elements[]);

int main() {
    int sender;
    printf("Process initiated deadlock detection.\n");

    // Allocate memory for visited array
    visited = (int *)calloc(NUM_PROCESSES, sizeof(int));

    printf("Enter the starting node for deadlock detection: ");
    scanf("%d", &sender);
    getchar();  // Consume the newline character from the input buffer

    bool deadlock = probe_dd(sender, sender, visited);
    if (deadlock) {
        printf("\nDeadlock has been detected!");
    } else {
        printf("\nNo deadlock has been detected!");
    }

    // Free dynamically allocated memory
    free(visited);

    return 0;
}

bool probe_dd(int sender, int target, int visited_elements[]) {
    if (visited_elements[target]) {
        return true; // Deadlock detected
    }

    visited_elements[target] = 1; // Mark the element as visited

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (wfg[target][i] == 1) {
            if (probe_dd(sender, i, visited_elements)) {
                return true; // Deadlock detected
            }
        }
    }

    return false; // No deadlock detected
}
