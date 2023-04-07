#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include<string.h>
#include<unistd.h>

int startNum = 0;
int maxPrime = 500000000;
int batchSize = 500000;
int nPrimes = 0;

pthread_mutex_t lock;

pthread_mutex_t lockNPrimes;


bool IsPrime(int n);
void *checkPrimes(void *);


int main(int argc, char *argv[]){
    struct timespec start, finish;
    double elapsed;
    if(argc != 3)
    {
        printf("Supply two argument supplied arguments %d \n", argc);
        return 1;
    }
    sscanf(argv[1], "%d", &maxPrime);

    int nThreads = 0;
    sscanf(argv[2], "%d", &nThreads);

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&lockNPrimes, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    //Measuring actual time in uint seconds
    time_t now;
    time_t then;
    time ( &now );
    int err;
    pthread_t *tid = malloc(sizeof(pthread_t)*nThreads);
    printf("creating nThreads %i \n", nThreads);
    //return;
    int *threadIds = malloc(sizeof(int)*nThreads);
    for(int i = 0; i< nThreads; i++){
        threadIds[i] = i+1;
    }

    for(int i = 0; i<nThreads; i++){
       err = pthread_create(&(tid[i]), NULL, &checkPrimes, &threadIds[i]);
        if (err != 0){
            printf("\ncan't create thread :[%s]", strerror(err));

        }
    }
    
    for(int i = 0; i<nThreads; i++){
        pthread_join(tid[i], NULL);
    }

    time ( &then );
  
    printf("Max number checked (first argument): %d  Time spent: %ld\n", startNum, then-now);

    printf("Primes found %d\n", nPrimes);
}



void* checkPrimes(void *p)
{
    int threadId = *(int *)p;
    printf("Created thread %i\n", threadId);
    int primeStart = 0;
    int primeEnd = 0;
    int i = 0;
    while (startNum < maxPrime)
    {

        pthread_mutex_lock(&lock);
        // Mutex needed to avoid thread reading and writing to global variables at
        //the same time.
        primeStart = startNum;
        primeEnd = startNum + batchSize;
        startNum = startNum + batchSize;
        pthread_mutex_unlock(&lock);

        for (i = primeStart; i < primeEnd; i++)
        {
            if (IsPrime(i))
            {
                pthread_mutex_lock(&lockNPrimes);

                nPrimes = nPrimes + 1;
                pthread_mutex_unlock(&lockNPrimes);
            }
        }
    }
    printf("Exiting thread %d\n", threadId);
    return (void *)NULL;
}

bool IsPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}