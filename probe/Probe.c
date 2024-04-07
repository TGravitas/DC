#include <stdio.h>
#include <stdbool.h>  // Added for bool type
#include <stdlib.h>

// Function declaration
bool probe_dd(int sender, int target, int visited_elements[]);

int visited[5];
int wfg[5][5] = {{0, 0, 1, 0, 0}, {1, 0, 0, 1, 0}, {0, 1, 0, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
int sender = 0;
int j = 0, k = 0;

int main() {
    printf("Process initiated deadlock detection: ");
    scanf("%d", &sender);
    getchar();  // Consume the newline character from the input buffer

    for (int i = 0; i < 5; i++) {
        if (wfg[sender][i] == 1) {
            visited[j] = i;
            j++;
        }
    }

    // Introduce an array to keep track of visited elements in the probe_dd function
    int visited_elements[5] = {0};

    bool deadlock = probe_dd(sender, visited[k], visited_elements);
    k++;
    if (deadlock == true) {
        printf("\nDeadlock has been detected!");
    } else {
        printf("\nNo deadlock has been detected!");
    }

    return 0;
}

bool probe_dd(int sender, int target, int visited_elements[]) {
    if (sender == target || visited_elements[target]) {
        return true;
    }

    visited_elements[target] = 1; // Mark the element as visited

    for (int i = 0; i < 5; i++) {
        if (wfg[target][i] == 1) {
            visited[j] = i;
            j++;
        }
    }

    if (visited[k] != '\0') {
            printf("\n%d",visited[k]);
        return probe_dd(sender, visited[k++], visited_elements);
    }

    return false;
}
