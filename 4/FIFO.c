#include <stdio.h>
#include <stdbool.h>
#define MAX_PAGE 10

int page_frames[MAX_PAGE];
int page_references[30] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

int page_fault_count = 0;

bool is_page_in_memory(int page_number) {
    for (int i = 0; i < MAX_PAGE; i++) {
        if (page_frames[i] == page_number) {
            return true;
        }
    }
    return false;
}

void add_page_to_memory(int page_number) {
    for (int i = 0; i < MAX_PAGE; i++) {
        if (page_frames[i] == -1) {
            page_frames[i] = page_number;
            return;
        }
    }
    for (int i = 0; i < MAX_PAGE - 1; i++) {
        page_frames[i] = page_frames[i + 1];
    }
    page_frames[MAX_PAGE - 1] = page_number;
}

int main() {
    for (int i = 0; i < MAX_PAGE; i++) {
        page_frames[i] = -1;
    }

    for (int i = 0; i < 30; i++) {
        int page_number = page_references[i];
        if (!is_page_in_memory(page_number)) {
            add_page_to_memory(page_number);
            page_fault_count++;
        }
    }

    printf("Number of page faults: %d\n", page_fault_count);
    return 0;
}
