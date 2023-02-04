#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_REQUESTS 200

int requests[MAX_REQUESTS];
int head_position;
int request_count;

int total_seek_time = 0;
bool processed[MAX_REQUESTS];

void get_requests() {
    printf("Enter the number of disk requests: ");
    scanf("%d", &request_count);
    printf("Enter the requests, separated by a space: ");
    for (int i = 0; i < request_count; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head_position);
}

int get_next_request() {
    int closest_request = -1;
    int closest_distance = INT_MAX;
    for (int i = 0; i < request_count; i++) {
        if (!processed[i] && requests[i] >= head_position) {
            int distance = requests[i] - head_position;
            if (distance < closest_distance) {
                closest_distance = distance;
                closest_request = i;
            }
        }
    }
    if (closest_request == -1) {
        for (int i = request_count - 1; i >= 0; i--) {
            if (!processed[i] && requests[i] < head_position) {
                int distance = head_position - requests[i];
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest_request = i;
                }
            }
        }
    }
    return closest_request;
}

void simulate_look() {
    while (true) {
        int closest_request = get_next_request();
        if (closest_request == -1) {
            break;
        }
        processed[closest_request] = true;
        int seek_time = abs(requests[closest_request] - head_position);
        total_seek_time += seek_time;
        head_position = requests[closest_request];
    }
}

int main() {
    get_requests();
    simulate_look();
    printf("Total seek time: %d\n", total_seek_time);
    printf("Average seek time: %f\n", (float) total_seek_time / request_count);
    return 0;
}
