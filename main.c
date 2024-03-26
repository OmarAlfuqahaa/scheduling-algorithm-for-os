// Omar Alfoqahaa     1200207
// Mohammad R Khalaf  1201982
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define INT_MAX 10

struct Process {
    int processID;
    int burstTime;
    int priority;
};

void roundRobinScheduling(struct Process processes[], int numProcesses, int timeQuantum) {
    int completedProcesses = 0;
    int currentTime = 0;

    while (completedProcesses < numProcesses) {
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].burstTime > 0) {
                if (processes[i].burstTime <= timeQuantum) {
                    currentTime += processes[i].burstTime;
                    processes[i].burstTime = 0;
                    printf("Process %d executed at time %d\n", processes[i].processID, currentTime);
                    printf("Process %d completed at time %d\n", processes[i].processID, currentTime);
                    completedProcesses++;
                } else {
                    currentTime += timeQuantum;
                    processes[i].burstTime -= timeQuantum;
                    printf("Process %d executed at time %d\n", processes[i].processID, currentTime);
                }
            }
        }
    }
}

void priorityScheduling(struct Process processes[], int numProcesses) {
    int completedProcesses = 0;
    int currentTime = 0;

    while (completedProcesses < numProcesses) {
        int highestPriority = -1;
        int highestPriorityIndex = -1;

        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].burstTime > 0 && processes[i].priority > highestPriority) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex != -1) {
            processes[highestPriorityIndex].burstTime--;
            currentTime++;
            printf("Process %d executed at time %d\n", processes[highestPriorityIndex].processID, currentTime);

            if (processes[highestPriorityIndex].burstTime == 0) {
                completedProcesses++;
                printf("Process %d completed at time %d\n", processes[highestPriorityIndex].processID, currentTime);
            }
        } else {
            currentTime++;
        }
    }
}

void sjfScheduling(struct Process processes[], int numProcesses) {
    int completedProcesses = 0;
    int currentTime = 0;

    while (completedProcesses < numProcesses) {
        int shortestJobIndex = -1;
        int shortestJobTime = INT_MAX;

        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].burstTime > 0 && processes[i].burstTime < shortestJobTime) {
                shortestJobTime = processes[i].burstTime;
                shortestJobIndex = i;
            }
        }

        if (shortestJobIndex != -1) {
            processes[shortestJobIndex].burstTime--;
            currentTime++;
            printf("Process %d executed at time %d\n", processes[shortestJobIndex].processID, currentTime);

            if (processes[shortestJobIndex].burstTime == 0) {
                completedProcesses++;
                printf("Process %d completed at time %d\n", processes[shortestJobIndex].processID, currentTime);
            }
        } else {
            currentTime++;
        }
    }
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int numProcesses;

    printf("Enter the number of processes : ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].processID = i + 1;
    }

    int choice;
    printf("\nSelect the scheduling algorithm:\n");
    printf("1. Round Robin Scheduling\n");
    printf("2. Priority Scheduling\n");
    printf("3. Shortest Job First (SJF) Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            int timeQuantum;
            printf("Enter time quantum for Round Robin Scheduling: ");
            scanf("%d", &timeQuantum);
            printf("\nRound Robin Scheduling:\n");
            roundRobinScheduling(processes, numProcesses, timeQuantum);
            break;
        }
        case 2:
            printf("\nPriority Scheduling:\n");
            priorityScheduling(processes, numProcesses);
            break;
        case 3:
            printf("\nShortest Job First (SJF) Scheduling:\n");
            sjfScheduling(processes, numProcesses);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}