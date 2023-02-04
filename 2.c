#include <stdio.h>
#include <stdbool.h>

#define NO_OF_C 5
#define NO_OF_R 3

int available[NO_OF_R];
int maximum[NO_OF_C][NO_OF_R];
int allocation[NO_OF_C][NO_OF_R];
int need[NO_OF_C][NO_OF_R];

void read_data() {
   printf("Enter the number of available instances of each resource:\n");
   for (int i = 0; i < NO_OF_R; i++) {
       printf("%d: ",i);
      scanf("%d", &available[i]);
   }
   printf("Enter the maximum number of resources required by each customer:\n");
   for (int i = 0; i < NO_OF_C; i++) {
      for (int j = 0; j < NO_OF_R; j++) {
          printf("[%d,%d]: ",i,j);
         scanf("%d", &maximum[i][j]);
      }
   }
   printf("Enter the number of resources allocated to each customer:\n");
   for (int i = 0; i < NO_OF_C; i++) {
      for (int j = 0; j < NO_OF_R; j++) {
          printf("[%d,%d]: ",i,j);
         scanf("%d", &allocation[i][j]);
      }
   }
}

void calculate_need() {
   for (int i = 0; i < NO_OF_C; i++) {
      for (int j = 0; j < NO_OF_R; j++) {
         need[i][j] = maximum[i][j] - allocation[i][j];
      }
   }
}

bool is_safe() {
   bool finished[NO_OF_C];
   for (int i = 0; i < NO_OF_C; i++) {
      finished[i] = false;
   }
   int work[NO_OF_R];
   for (int i = 0; i < NO_OF_R; i++) {
      work[i] = available[i];
   }
   int count = 0;
   while (count < NO_OF_C) {
      bool found = false;
      for (int i = 0; i < NO_OF_C; i++) {
         if (!finished[i]) {
            int j;
            for (j = 0; j < NO_OF_R; j++) {
               if (need[i][j] > work[j]) {
                  break;
               }
            }
            if (j == NO_OF_R) {
               for (int k = 0; k < NO_OF_R; k++) {
                  work[k] += allocation[i][k];
               }
               finished[i] = true;
                count++;
                found = true;
            }
        }
    }
    if (!found) {
    break;
    }
}
return count == NO_OF_C;
}

int main() {
    read_data();
    calculate_need();
    if (is_safe()) {
        printf("The system is in a safe state.\n");
    } else {
    printf("The system is in an unsafe state.\n");
    }
    return 0;
}