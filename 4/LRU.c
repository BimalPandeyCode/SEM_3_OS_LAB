#include <stdio.h>
#include <stdbool.h>
#define MAX_PAGE 10

int page_frames[MAX_PAGE];
int page_references[30] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

int page_fault_count = 0;
int page_frame_usage[MAX_PAGE];

bool is_page_in_memory(int page_number) {
    for (int i = 0; i < MAX_PAGE; i++) {
        if (page_frames[i] == page_number) {
            return true;
        }
    }
    return false;
}

void add_page_to_memory(int page_number) {
    int l_r_u_index = 0;
    int l_r_u_value = page_frame_usage[0];
    for (int i = 1; i < MAX_PAGE; i++) {
        if (page_frame_usage[i] < l_r_u_value) {
            l_r_u_index = i;
            l_r_u_value = page_frame_usage[i];
        }
    }
    page_frames[l_r_u_index] = page_number;
    page_frame_usage[l_r_u_index] = 0;
}

int main() {
    for (int i = 0; i < MAX_PAGE; i++) {
        page_frames[i] = -1;
        page_frame_usage[i] = 0;
    }

    for (int i = 0; i < 30; i++) {
        int page_number = page_references[i];
        if (!is_page_in_memory(page_number)) {
            add_page_to_memory(page_number);
            page_fault_count++;
        }
        for (int j = 0; j < MAX_PAGE; j++) {
            if (page_frames[j] != -1) {
                page_frame_usage[j]++;
            }
        }
    }

    printf("Number of page faults: %d\n", page_fault_count);
    return 0;
}
