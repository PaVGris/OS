#include "library.h"
#include "bitonic.h"
#include "pthread.h"
#include <sys/time.h>

#define INVALID_INPUT 403
#define WRONG_ANSWER 405

#define MAXINT 2147483647
#define UP 1
#define DOWN 0

pthread_mutex_t lock;
size_t max_threads = 1;
size_t use_threads = 1;

void InitArgs(ArgsBitonic *args, int *array, int size, int start, int dir){
    args->array = array;
    args->size  = size;
    args->start = start;
    args->dir   = dir;
}


void Comparator(int *array, int i, int j, int dir){
    if(dir == (array[i] > array[j])){
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void BitonicMergeSinglThread(ArgsBitonic *args){
    if(args->size > 1){
        int nextsize = args->size / 2;
        for(int i = args->start; i < nextsize + args->start; ++i){
                Comparator(args->array, i, i + nextsize, args->dir);
        }

        ArgsBitonic args1;
        ArgsBitonic args2;
        InitArgs(&args1, args->array, nextsize, args->start, args->dir);
        InitArgs(&args2, args->array, nextsize, args->start + nextsize, args->dir);
        
        BitonicMergeSinglThread(&args1);
        BitonicMergeSinglThread(&args2);
    }
}

void BitonicSortSinglThread(ArgsBitonic *args){
    if(args->size > 1){
        int nextsize = args->size / 2;

        ArgsBitonic args1;
        ArgsBitonic args2;
        InitArgs(&args1, args->array, nextsize, args->start, DOWN);
        InitArgs(&args2, args->array, nextsize, args->start + nextsize, UP);

        BitonicSortSinglThread(&args1);
        BitonicSortSinglThread(&args2);
        BitonicMergeSinglThread(args);
    }
}

void BitonicMergeMultiThreads(ArgsBitonic *args){
    if(args->size > 1){        
        int nextsize = args->size / 2;
        int isParal = 0;
        pthread_t tid;

        for(int i = args->start; i < nextsize + args->start; ++i){
                Comparator(args->array, i, i + nextsize, args->dir);
        }

        ArgsBitonic args1;
        ArgsBitonic args2;
        InitArgs(&args1, args->array, nextsize, args->start, args->dir);
        InitArgs(&args2, args->array, nextsize, args->start + nextsize, args->dir);

        pthread_mutex_lock(&lock);
        if(use_threads < max_threads){ 
            ++use_threads;
            pthread_mutex_unlock(&lock);
            isParal = 1;
            pthread_create(&tid, NULL,(void*) &BitonicMergeMultiThreads, &args1);
            BitonicMergeMultiThreads(&args2);
        } else {
            pthread_mutex_unlock(&lock);
            BitonicMergeSinglThread(&args1);
            BitonicMergeSinglThread(&args2);
        }

        if(isParal){
            pthread_join(tid, NULL);
            pthread_mutex_lock(&lock);
            --use_threads;
            pthread_mutex_unlock(&lock);
        }
    }
}
 
void BitonicSortMultiThreads(ArgsBitonic *args){
    if(args->size > 1 ){
        int nextsize = args->size / 2;
        int isParal = 0;
        pthread_t tid;

        ArgsBitonic args1;
        ArgsBitonic args2;
        InitArgs(&args1, args->array, nextsize, args->start, DOWN);
        InitArgs(&args2, args->array, nextsize, args->start + nextsize, UP);

        pthread_mutex_lock(&lock);
        if(use_threads < max_threads){
            ++use_threads;
            pthread_mutex_unlock(&lock);
            isParal = 1;
            pthread_create(&tid, NULL,(void*) &BitonicSortMultiThreads, &args1);
            BitonicSortMultiThreads(&args2);
        } else {
            pthread_mutex_unlock(&lock);
            BitonicSortSinglThread(&args1);
            BitonicSortSinglThread(&args2);
        }

        if(isParal){
            pthread_join(tid, NULL);
            pthread_mutex_lock(&lock);
            --use_threads;
            pthread_mutex_unlock(&lock);
        }
        BitonicMergeMultiThreads(args);
    }
}

void bitonicsort(int *array, int size, int threads){
    pthread_mutex_init(&lock, NULL);

    ArgsBitonic args;
    InitArgs(&args,array,size,0,UP);

    if(threads > 1)
        max_threads = threads;

    BitonicSortMultiThreads(&args);
    
    pthread_mutex_destroy(&lock);
}

int SizeStep(int Num){
    int i = 1;
    while(i < Num)
        i *= 2;
    return i;
}


int ThreadSort(int threads, char* nameF){
    FILE* file;
    if(threads < 1){
        printf("ERROR: Incorrect number of threads\n");
        return INVALID_INPUT;
    }

    int input_size;
    file = fopen(nameF, "r");
    if (file == NULL) printf("ERROR: Can't open this file\n");

    fscanf(file, "%d", &input_size);
    //находим ближашее число 2^k >= input_size
    int size_array = SizeStep(input_size);
    int *array = malloc(sizeof(int)*size_array);

    for(int i = 0; i < input_size; ++i)
        fscanf(file,"%d", array+i);

    fclose(file);

    for(int i = input_size; i < size_array; ++i)
        array[i] = MAXINT;


    bitonicsort(array, size_array, threads);

    for(int i = 1; i < input_size; ++i) {
        if(array[i - 1] > array[i]) {
            printf("ERROR: Something goes wrong. Array is not sorted\n");
            return WRONG_ANSWER;
        }
    }
    printf("Array is sorted\n");

    free(array);
    return 0;
}


