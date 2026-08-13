*This project has been created as part of the 42 curriculum by dthoo*  

## Philosophers

### Description

This program simulates the dining philosopher problem:

A number of philosophers sit a round table.
The same number of forks are on the table.
One fork lays in between each philosopher.
A philosopher has to grab the forks on both his left and right to start eating.
A philosopher will go to sleep after they have finished eating.
A philosopher will die if they do not eat in time.
The philosophers do not know anything about each other.

The philosophers should avoid dying.

### Instructions

Compilation:
```
make
```
To run:
```
./philo [number of philosophers] [A] [B] [C] [D]
```
- A: time in ms it takes a philosopher to starve from the start of their last meal
- B: time in ms a philosopher needs to finish eating
- C: time in ms a philosopher spends sleeping after a meal
- D: number of times each philosopher should eat, the simulation ends if everyone has eaten this many times
    -   this is an optional argument, the simulation will go on until a philosopher dies if this is omitted

Optional compilation flags:
```
-DTHREAD_LOAD=X
-DBUFLEN=Y
-DSLEEP_THRESHOLD=Z
```
More on those in the overview.

### Overview of the project

My simulation uses a waiter to coordinate the philosophers' dining experience.
A thread is dedicated to update its decision making via the table counter.
The waiter uses an odd/even rule to maximise the number of philosophers eating at once.
If there are an odd number of philosophers, the waiter cycles through an additional group consisting of just the last philosopher.
The waiter checks if the philosopher can currently grab both forks, and if they belong to the group that should currently be eating.

More threads will check each philosopher to see if they have starved. 
- each thread watches X philosophers

Any change in state of a philosopher is printed to stdout.
- a buffer of size Y is used for each message

Philosophers are represented as threads.
Each thread may call usleep to wait out longer delays rather than busy spin the whole duration.
- Z is the time in ms that represents the user defined tolerance for usleep

#### getting this to run fast enough

I discovered that usleep and write were causing delays with just four philosophers.
For usleep, I introduced a tolerance buffer to offset its inaccuracy.
For write, I configure a thread local buffer to be used in one write, and the write call is not bound by a mutex.
- checking the death flag just prior to this does use a mutex.
- an alternate print function using multiple write() calls instead of a buffer is commented out

### Resources

The man pages highlight a number of actions that are unsafe:
- destroying a mutex that someone else expects
- unlocking a mutex that was not locked by the calling thread

Keeping those in mind, I have two control mutexes:
- one for checking conditions prior to each print
- one for calling the waiter, just so it can be interrupted by death checks when necessary
