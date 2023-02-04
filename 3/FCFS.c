#include <stdio.h>

#define NO_OF_P 5

int burst_time[NO_OF_P];
int arrival_time[NO_OF_P];
int waiting_time[NO_OF_P];
int turn_around_time[NO_OF_P];

void read_data() {
   printf("Enter the burst time and arrival time of each process:\n");
   for (int i = 0; i < NO_OF_P; i++) {
      printf("Brust Time for process %d:",i+1);
      scanf("%d", &burst_time[i]);
      printf("Arrival Time for process %d:",i+1);
      scanf("%d", &arrival_time[i]);
   }
}

void calculate_waiting_time() {
   waiting_time[0] = 0;
   for (int i = 1; i < NO_OF_P; i++) {
      waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
      waiting_time[i] -= arrival_time[i];
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
   calculate_waiting_time();
   calculate_turn_around_time();
   print_results();
   return 0;
}