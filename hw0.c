/*
Name: Md Kamal Hossain Chowdhury
Email: mhchowhdhury@crimson.ua.edu
Course: CS 691
Homework #: 0
Instructions to compile the program: (for example: gcc -Wall -O -o hw0 hw0.cpp)
Instructions to run the program: (for example: ./hw0 1000 1000)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define DIES 0
#define ALIVE 1

double gettime(void) {
  struct timeval tval;

  gettimeofday(&tval, NULL);

  return ((double)tval.tv_sec + (double)tval.tv_usec / 1000000.0);
}
int *allocateArray(int N) {

  // for(int i=0;i<N+1;i++)
  int *ptr = malloc((N) * (N) * sizeof(int));
  // printf("size=%d",sizeof(ptr)/sizeof(ptr[0]));
  return ptr;
}
void printArray(int *a, int N) {

  for (int i = 0; i < N + 2; i++) {
    for (int j = 0; j < N + 2; j++)
      printf("%4d ", a[i * (N + 2) + j]);
    printf("\n");
  }
}

int compute(int *life, int *temp, int N) {

  int i, j, value = 0, flag = 0;

  for (i = 1; i < N + 1; i++) {
    for (j = 1; j < N + 1; j++) {
      // value = 0;
      value = life[(i - 1) * (N + 2) + (j-1)] + life[(i - 1) * (N + 2) + j] +life[(i - 1) * (N + 2) + (j + 1)] + 
              life[(i) * (N + 2) + (j - 1)] + life[(i) * (N + 2) + (j + 1)] +
              life[(i + 1) * (N + 2) + (j - 1)] + life[(i+1) * (N + 2) + (j)] + life[(i+1) * (N + 2) + (j + 1)];
       /*  printf("\nlife[%d][%d]=%d %d %d %d %d %d %d %d \n",i,j,life[(i - 1) * (N + 2) + (j-1)] , life[(i - 1) * (N + 2) + j] ,
              life[(i - 1) * (N + 2) + (j + 1)] ,
              life[(i) * (N + 2) + (j - 1)] ,
              life[(i) * (N + 2) + (j + 1)] ,
              life[(i + 1) * (N + 2) + (j - 1)] , life[(i+1) * (N + 2) + (j)] ,
              life[(i+1) * (N + 2) + (j + 1)] ); */

      // printf("life[%d][%d]=%d  ", i, j, value);
      if (life[i * (N + 2) + j] == ALIVE) {

        if (value < 2 || value > 3) {
          temp[i * (N + 2) + j] = DIES;
          flag++;
        } else {
          temp[i * (N + 2) + j] = ALIVE; // no change÷
        }
      } else {

        if (value == 3) {
          temp[i * (N + 2) + j] = ALIVE;
          flag++;
        } else {
          temp[i * (N + 2) + j] = DIES; // no change
        }
      }
    }
  }
//   printf("\ntemp\n");
//   printArray(temp, N);

  return flag;
}

void freeArray(int *a) {

  // free(&a[0]);
  free(a);
}

int main(int argc, char **argv) {

  int r, c, i;
  int N, NTIMES;
  long arg1, arg2;
  int flag = 1;
  double t1,t2;

  int p;

  int *life = NULL, *temp = NULL, *ptr;

  if (argc == 3) {
    char *p;

    arg1 = strtol(argv[1], &p, 10);
    arg2 = strtol(argv[2], &p, 10);
    N = arg1;

    NTIMES = arg2;
  } else {

    fprintf(stderr, "Need two values for size and generation values\n");
    return 0;
  }

  // printf("The N: %d", N);
  life = allocateArray(N + 2);
  temp = allocateArray(N + 2);
  // life = malloc((N + 2) * (N + 2) * sizeof(int));
  // temp = malloc((N + 2) * (N + 2) * sizeof(int));

  // make boundary cells zero
  for (int i = 0; i < (N + 2); i++) {
    for (int j = 0; j < (N + 2); j++) {
      // p=i * (N+2) + j;
      // printf("%4d",p);

      if (i == 0 || i == N + 1 || j == 0 || j == N + 1) {
        life[i * (N + 2) + j] = DIES;
        temp[i * (N + 2) + j] = DIES;
        // printf(" i=%d %4d\n",i,p);
      }
      // printf("i=%d,j=%d\n",i,j);
    }
  }
  // printArray(temp, N);
  //  Initialize the array
  srand(time(NULL));
  for (int i = 1; i < (N + 1); i++) {
    for (int j = 1; j < (N + 1); j++) {
      if ((float)rand() / RAND_MAX > 0.5)
        life[i * (N + 2) + j] = ALIVE;
      else
        life[i * (N + 2) + j] = DIES;
    }
  }

  // printf("\n#####before#####\n");
  // printArray(life, N);
  t1=gettime();
  for (int i = 0; i < NTIMES && flag!=0; i++) {
    flag=0;
    flag = compute(life, temp, N);
    ptr=life;
    life=temp;
    temp = ptr;
    
    // printf("\n#####After#####\n");
    // printArray(life, N);
  }
  t2=gettime();
  
    // printf("\n#####After#####\n");
    // printArray(life, N);
  printf("Time taken %f seconds for %d iterations\n", t2 - t1, NTIMES);


  freeArray(life);
  //   freeArray(temp);

  return 0;
}
