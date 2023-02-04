#include <stdio.h>
#include <stdbool.h>
#define MAX_PAGE 10

int page_frames[MAX_PAGE];
int page_references[30] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

int page_fault_count = 0;
int page_reference_count[MAX_PAGE];

bool is_page_in_memory(int page_number) {
    for (int i = 0; i < MAX_PAGE; i++) {
        if (page_frames[i] == page_number) {
            page_reference_count[i]++;
            return true;
        }
    }
    return false;
}

void add_page_to_memory(int page_number) {
    int l_f_u_index = 0;
    int l_f_u_value = page_reference_count[0];
    for (int i = 1; i < MAX_PAGE; i++) {
        if (page_reference_count[i] < l_f_u_value) {
            l_f_u_index = i;
            l_f_u_value = page_reference_count[i];
        }
    }
    page_frames[l_f_u_index] = page_number;
    page_reference_count[l_f_u_index] = 1;
}

int main() {
    for (int i = 0; i < MAX_PAGE; i++) {
        page_frames[i] = -1;
        page_reference_count[i] = 0;
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
