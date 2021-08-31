# Philosophers
Dining Philosopher Problem\
This project introduced me a multithreaded and multiprocessor programming.\
First time i used tools of synchronization like mutex and semaphore.\
I found out the difference between thread and process and specifics of work with them.\
In "philo" directory is the solving with threads and mutexes. In "philo_bonus" solving with semaphores and processes. 
To check the work of program:
1. make
2. ./philo 5 800 200 200(philosophers will not die). 
3. ./philo 4 400 200 200(philosophers will not die).
4. ./philo 1 800 200 200(one philosopher immediately dies).
5. ./philo 4 310 200 100(somebody will die because time to die is small enough).
