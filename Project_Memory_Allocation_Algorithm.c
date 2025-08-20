#include <stdio.h>

typedef struct {
    int id, size, allocated;
} typeMemory;

typedef struct {
    int id, required, assigned;
} typeProcess;

void abc(typeMemory memoryList[], typeProcess processList[], int m, int p, int alg) {
    printf("\nAllocation Summary:\n");

    for (int i = 0; i < p; i++) {
        int index = -1; ///flag

        if (alg == 1) { // first fit
            for (int j = 0; j < m; j++) {
                if (memoryList[j].allocated == 0 && memoryList[j].size >= processList[i].required) {
                    index = j;
                    break;
                }
            }
        }

        else if (alg == 2) { // best fit
            for (int j = 0; j < m; j++) {
                if (memoryList[j].allocated == 0 && memoryList[j].size >= processList[i].required) {
                    if (index == -1 || memoryList[j].size < memoryList[index].size) {
                        index = j;
                    }
                }
            }
        }

        else if (alg == 3) { // worst fit
            for (int j = 0; j < m; j++) {
                if (memoryList[j].allocated == 0 && memoryList[j].size >= processList[i].required) {
                    if (index == -1 || memoryList[j].size > memoryList[index].size) {
                        index = j;
                    }
                }
            }
        }

        if (index != -1) {
            memoryList[index].allocated = 1;
            processList[i].assigned = memoryList[index].id;
            printf("Process %d (%d KB) --> Block %d\n", processList[i].id, processList[i].required, processList[i].assigned);
        } else {
            processList[i].assigned = -1;
            printf("Process %d (%d KB) --> Not Allocated\n", processList[i].id, processList[i].required);
        }
    }
}

int main() {
    typeMemory memoryList[10];
    typeProcess processList[10];
    int m, p, choice;

    printf("Enter number of memory blocks (max 10): ");
    scanf("%d", &m);
    printf("Enter sizes of %d memory blocks:\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &memoryList[i].size);
        memoryList[i].id = i + 1;
        memoryList[i].allocated = 0;
    }

    printf("Enter number of process (max 10): ");
    scanf("%d", &p);
    printf("Enter memory required by %d process:\n", p);
    for (int i = 0; i < p; i++) {
        scanf("%d", &processList[i].required);
        processList[i].id = i + 1;
        processList[i].assigned = -1;
    }

    printf("\nChoose Algorithm:\n1. First Fit\n2. Best Fit\n3. Worst Fit\nChoice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }

    abc(memoryList, processList, m, p, choice);

    return 0;
}
