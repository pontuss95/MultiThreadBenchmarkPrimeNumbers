# MultiThreadBenchmarkPrimeNumbers
Very simple code that creates N threads (second input) and calculates how many prime numbers is present between 0 and the first given input.


compile with -pthread library. 

Example usage:

```sh
gcc checkPrime.c -o checkPrime -pthread
```

```sh
./checkPrime 100000000 1
creating nThreads 1 
Created thread 1
Exiting thread 1
Max number checked (first argument): 100000000  Time spent: 19
Primes found 5761455

./checkPrime 100000000 24
creating nThreads 24 
Created thread 2
Created thread 3
Created thread 1
Created thread 9
Created thread 6
Created thread 11
Created thread 10
Created thread 12
Created thread 4
Created thread 8
Created thread 5
Created thread 7
Created thread 13
Created thread 14
Created thread 15
Created thread 16
Created thread 17
Created thread 18
Created thread 19
Created thread 20
Created thread 21
Created thread 23
Created thread 22
Created thread 24
Exiting thread 10
Exiting thread 7
Exiting thread 14
Exiting thread 4
Exiting thread 16
Exiting thread 8
Exiting thread 15
Exiting thread 19
Exiting thread 13
Exiting thread 21
Exiting thread 17
Exiting thread 22
Exiting thread 20
Exiting thread 24
Exiting thread 23
Exiting thread 18
Exiting thread 3
Exiting thread 1
Exiting thread 6
Exiting thread 2
Exiting thread 9
Exiting thread 12
Exiting thread 11
Exiting thread 5
Max number checked (first argument): 100000000  Time spent: 2
Primes found 5761455
```


This code can surely be optimized more to produce results faster, this code should be seen more as a playground where i learned to use and experiment with thread creation and mutexes. 