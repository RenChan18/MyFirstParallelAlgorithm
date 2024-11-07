#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#ifndef OPTION_NUMBER
#define OPTION_NUMBER 1
#endif 

#ifndef RAND_RANGE
#define RAND_RANGE 100
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 100000
#endif

#ifndef THREADS_NUM
#define THREADS_NUM 5
#endif

#ifndef LOOP_NUM
#define LOOP_NUM 100000
#endif


double measure_time(long long (*func)(long long*, size_t), long long *arr, size_t size, long long *result) {
    clock_t begin = clock();
    *result = func(arr, size); 
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
    return time_spent; 
}

void random_fill(long long *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % RAND_RANGE;
    }
}

/*********************************************
 *            ОДНОПОТОЧНЫЙ АЛГОРИТМ          *
 *********************************************/

long long count_sum(long long *arr, size_t size) {
    long long sum = 0; 
    for (size_t i = 0; i < size; ++i) { 
        sum += arr[i];
    }
    return sum;
}

/*********************************************
 *            ПАРАЛЛЕЛЬНЫЙ  АЛГОРИТМ         *
 *********************************************/
typedef struct {
    long long *arr;
    size_t size;
    long long result;
    int thread_id;
} ThreadData;

void* parallel_count(void *arg) {
   ThreadData *data = (ThreadData*) arg;
   size_t start = data->thread_id * data->size;
   size_t end = (data->thread_id +1) * data->size;
   data->result = 0;

   for(size_t i = start; i < end && i < ARRAY_SIZE; ++i) {
       data->result += data->arr[i];
   }

   if (data->thread_id == THREADS_NUM - 1) {
       end = ARRAY_SIZE;  
   }

   pthread_exit (NULL);
}





int main() {

    long long *arr = malloc(ARRAY_SIZE * sizeof(long long));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));
    random_fill(arr, ARRAY_SIZE);
    
    long long sum = 0;
    double elapsed_time = 0.0; 

   /* for (size_t i = 0; i < ARRAY_SIZE; ++i) { 
        printf("arr[%ld] = %lld\n", i, arr[i]);
    }*/


#if OPTION_NUMBER == 1

    elapsed_time = measure_time(count_sum, arr, ARRAY_SIZE, &sum); 

#elif OPTION_NUMBER == 2
    clock_t begin = clock();

    for (size_t i = 0; i < LOOP_NUM; ++i) {

       ThreadData thread_data[THREADS_NUM];
       pthread_t threadID[THREADS_NUM];
       size_t partition_size = ARRAY_SIZE / THREADS_NUM;

       for (int i = 0 ; i < THREADS_NUM ; i++) {
           thread_data[i].arr = arr;
           thread_data[i].size = partition_size;
           thread_data[i].thread_id = i;
           pthread_create (&threadID[i], NULL,parallel_count , (void*)&thread_data[i]);
       }
       
       for (int i = 0 ; i < THREADS_NUM ; i++) {
          pthread_join (threadID[i], NULL);
          sum += thread_data[i].result;
       }
    }

    clock_t end = clock();
    elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC; 

#endif

    printf("Sum of array elements: %lld\n", sum);
    printf("The elapsed time is %f seconds\n", elapsed_time/LOOP_NUM); 
    free(arr);
    return 0;
}

