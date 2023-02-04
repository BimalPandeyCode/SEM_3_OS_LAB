#include <stdio.h>
#include <stdbool.h>

#define NO_OF_P 5
#define TIME_QUANTUM 4

int burst_time[NO_OF_P];
int arrival_time[NO_OF_P];
int remaining_time[NO_OF_P];
int waiting_time[NO_OF_P];
int turn_around_time[NO_OF_P];
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

void calculate_waiting_time() {
   int service_time[NO_OF_P];
   service_time[0] = 0;
   waiting_time[0] = 0;
   for (int i = 1; i < NO_OF_P; i++) {
      service_time[i] = service_time[i - 1] + burst_time[i - 1];
      waiting_time[i] = service_time[i] - arrival_time[i];
      if (waiting_time[i] < 0) {
         waiting_time[i] = 0;
      }
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
   int count = 0;
   while (count < NO_OF_P) {
      for (int i = 0; i < NO_OF_P; i++) {
         if (arrival_time[i] <= time && remaining_time[i] > 0 && !finished[i]) {
            remaining_time[i] -= TIME_QUANTUM;
            time += TIME_QUANTUM;
            if (remaining_time[i] <= 0) {
               finished[i] = true;
               count++;
               time = time + remaining_time[i];
            }
         }
      }
   }
   calculate_waiting_time();
   calculate_turn_around_time();
   print_results();
   return 0;
}