#include <stdio.h>
#define MAX_REQ 200

int requests[MAX_REQ];
int head_position;
int req_count;

int total_seek_time = 0;

void get_requests() {
    printf("Enter the number of disk requests: ");
    scanf("%d", &req_count);
    printf("Enter the requests, separated by a space: ");
    for (int i = 0; i < req_count; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head_position);
}

void simulate_fcfs() {
    int previous_head_position = head_position;
    for (int i = 0; i < req_count; i++) {
        int seek_time = abs(requests[i] - previous_head_position);
        total_seek_time += seek_time;
        previous_head_position = requests[i];
    }
}

int main() {
    get_requests();
    simulate_fcfs();
    printf("Total seek time: %d\n", total_seek_time);
    printf("Average seek time: %f\n", (float) total_seek_time / req_count);
    return 0;
}
