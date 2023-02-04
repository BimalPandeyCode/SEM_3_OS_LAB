#include <stdio.h>
#include <stdbool.h>

#define NO_OF_P 5

int burst_time[NO_OF_P];
int arrival_time[NO_OF_P];
int remaining_time[NO_OF_P];
int waiting_time[NO_OF_P];
int turn_around_time[NO_OF_P];
int completion_time[NO_OF_P];
bool finished[NO_OF_P];

void read_data() {
   printf("Enter the burst time and arrival time of each process:\n");
   for (int i = 0; i < NO_OF_P; i++) {
      printf("Brust Time for process %d:",i+1);
      scanf("%d", &burst_time[i]);
      printf("Arrival Time for process %d:",i+1);
      scanf("%d", &arrival_time[i]);
      remaining_time[i] = burst_time[i];
      finished[i] = false;
   }
}

int find_next_process(int time) {
   int next_process = -1;
   int shortest_remaining_time = 100000;
   for (int i = 0; i < NO_OF_P; i++) {
      if (arrival_time[i] <= time && remaining_time[i] < shortest_remaining_time && remaining_time[i] > 0 && !finished[i]) {
         next_process = i;
         shortest_remaining_time = remaining_time[i];
      }
   }
   return next_process;
}

void calculate_waiting_time() {
   waiting_time[0] = 0;
   completion_time[0] = burst_time[0];
   for (int i = 1; i < NO_OF_P; i++) {
      completion_time[i] = completion_time[i - 1] + burst_time[i];
      waiting_time[i] = completion_time[i] - arrival_time[i] - burst_time[i];
   }
}

void calculate_turn_around_time() {
   for (int i = 0; i < NO_OF_P; i++) {
      turn_around_time[i] = burst_time[i] + waiting_time[i];
   }
}

void print_results() {
   printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
   for (int i = 0; i < NO_OF_P; i++) {
      printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turn_around_time[i]);
   }
}

int main() {
   read_data();
   int time = 0;
   while (true) {
      int next_process = find_next_process(time);
      if (next_process == -1) {
         break;
      }
      remaining_time[next_process]--;
      time++;
      if (remaining_time[next_process] == 0) {
         finished[next_process] = true;
      }
   }
   calculate_waiting_time();
   calculate_turn_around_time();
   print_results();
   return 0;
}