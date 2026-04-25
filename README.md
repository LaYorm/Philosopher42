*This project has been created as part of the 42 curriculum by yorimek.*

# PHILOSOPHER

## Description

***Philosopher*** is an implementation of the dining philosophers problem (*Edsger Dijkstra*). The goal of this project is to introduce multithreading and mutexes.

In this project, a given number of philosophers (>0) sit at a round table, with as many forks as there are philosophers. During the simulation, the philosopher(s) can do three things: eat, sleep, think (in that order). To eat, a philosopher must grab a fork on his left and one on his right. Since the forks are shared among adjacent philosophers, the challenge is in managing these shared resources without running into concurrency issues. The goal is that none of the philosophers die, and, if the user gives a number of meals that the philosophers must eat, that everyone around the table eats at least this number of times.


This project explores complex synchronization concepts, specifically focusing on:
* Creating and managing POSIX threads (`pthread`).
* Preventing **Data Races** and protecting shared memory using Mutexes (`pthread_mutex`).
* Avoiding **Deadlocks** (lock-order inversion) by implementing an asymmetric resource allocation strategy (even/odd fork picking).


## Instructions

This project includes a `Makefile`. Once you have cloned the git repository, use the following command:

To compile all the files and create the program named _**philo**_
```bash
make all
```

To run this program you have to launch it as follows (the last argument is optional).
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Once you have finished using this program, you can use this command to delete all object files.
```bash
make clean
```

Or this command, to delete the program and its objects.
```bash
make fclean
```


## Resources

### References
* These videos from ***CodeVault*** helped me a lot to understand what a thread and a mutex are, how they work, how to use them. The first videos of his playlist *Unix Thread in C* are a perfect introduction to these notions: [CodeVault: Unix Thread in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2).

* This article helped me to visualize the Dining philosophers problem and to understand how I can approach it: [Philosopher](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2).

### Use of AI
I used AI on this project to help me with a few tasks:
* **Debugging**: Analyzed and explained ```bash ThreadSanitizer``` logs due to Data Race or Deadlock.

 * **Exercises**: Created a few practical exercises at the beginning of the project to help me practice handling ```pthread``` and ```mutex```.

