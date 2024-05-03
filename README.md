# Dining Philosophers Problem

![Dining Philosophers Problem](https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png)

## Overview
This project is part of the 42 school curriculum and focuses on multi-threading/multi-process programming using mutexes and semaphores. It includes three different programs that simulate variations of the classic Dining Philosophers problem, adhering to the same fundamental rules. The objective is to optimize C code to minimize CPU usage, ensuring the survival of the philosophers.

### Programs
- `philo_one`: Utilizes multi-threading with mutexes.
- `philo_two`: Employs multi-threading with semaphores.
- `philo_three`: Uses multi-processes with semaphores.

## Rules
- The project must be coded in C, following the 42 Norm. Any memory leak, crash, undefined behavior, or norm violation will result in a score of 0.
- Philosophers are engaged in one of three activities: eating, thinking, or sleeping, without overlapping actions.
- They require two forks to eat the spaghetti served at the circular table.
- Philosophers must not starve and should not communicate or predict the death of their peers.
- The simulation ends when a philosopher dies.
- 
![Eating Rules](https://camo.githubusercontent.com/9e4ebb996ddb180a2523cabaaa01c16a7a45d5020eb0fb3686acb6f093fa053d/68747470733a2f2f7a7570696d616765732e6e65742f75702f32302f33382f697337712e706e67)

## Simulation Options
- `number_of_philosophers`: The count of philosophers and forks.
- `time_to_die`: The maximum time (ms) a philosopher can go without eating before dying.
- `time_to_eat`: The duration (ms) it takes for a philosopher to eat, holding two forks.
- `time_to_sleep`: The time (ms) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat`: Optional, stops the simulation if all philosophers eat this many times.

## Philosopher Numbering
- Philosophers are numbered from 1 to `number_of_philosophers`.
- Philosopher 1 sits next to philosopher `number_of_philosophers`. Others sit between philosophers N - 1 and N + 1.

## Logging
- Changes in philosopher status must be logged with the format:
  - `timestamp_in_ms X has taken a fork`
  - `timestamp_in_ms X is sleeping`
  - `timestamp_in_ms X is thinking`
  - `timestamp_in_ms X died`

## Constraints
- Status logs must not be mixed up with other philosophers' logs.
- Death of a philosopher must be printed within 10 ms of occurrence.
