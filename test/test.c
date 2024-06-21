#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	long			last_meal;
	int				isalive;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             eat_count;
	long            start_time;
}	t_philo;

long get_time_in_ms() {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec * (long)1000 + tv.tv_usec / 1000;
}

void print_status(int philo_id, long time, char *status) {
	printf("%ld ms: Philosopher %d is %s\n", time, philo_id, status);
}

void	*philo_behavior(void *arg) {
	t_philo *philo = (t_philo *)arg;

	while (philo->isalive && philo->eat_count > 0) {
		// Try to take forks
		if (pthread_mutex_lock(philo->l_fork) && pthread_mutex_lock(philo->r_fork))
		{
			print_status(philo->philo_id, get_time_in_ms() - philo->start_time, "taking a fork");

			// Eating
			philo->last_meal = get_time_in_ms();
			print_status(philo->philo_id, get_time_in_ms() - philo->start_time, "eating");
			usleep(philo->time_to_eat * 1000); 

			philo->eat_count--;

			// Put down forks
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);

			// Sleeping
			print_status(philo->philo_id, get_time_in_ms() - philo->start_time, "sleeping");
			usleep(philo->time_to_sleep * 1000); 

			// Check if philosopher has died
			if (get_time_in_ms() - philo->last_meal > philo->time_to_die) {
				philo->isalive = 0;
				print_status(philo->philo_id, get_time_in_ms() - philo->start_time, "dying");
			}
		}
	}

	return NULL;
}

int	main(int argc, char **argv)
{
	int number_of_philosophers;
	t_philo *philosophers;
	pthread_mutex_t *forks;
	int i;
	long start_time;

	if (argc < 5 || argc > 6) {
		printf("Error: wrong number of arguments\n");
		return 1;
	}

	number_of_philosophers = atoi(argv[1]);
	start_time = get_time_in_ms();

	// Initialize philosophers and forks
	philosophers = malloc(sizeof(t_philo) * number_of_philosophers);
	forks = malloc(sizeof(pthread_mutex_t) * number_of_philosophers);
	for (i = 0; i < number_of_philosophers; i++) {
		philosophers[i].philo_id = i + 1;
		philosophers[i].isalive = 1;
		philosophers[i].l_fork = &forks[i];
		philosophers[i].r_fork = &forks[(i + 1) % number_of_philosophers];
		pthread_mutex_init(philosophers[i].l_fork, NULL);
		pthread_mutex_init(philosophers[i].r_fork, NULL);
		philosophers[i].time_to_die = atoi(argv[2]);
		philosophers[i].time_to_eat = atoi(argv[3]);
		philosophers[i].time_to_sleep = atoi(argv[4]);
		philosophers[i].eat_count = (argc == 6) ? atoi(argv[5]) : -1;
		philosophers[i].start_time = start_time;
	}

	// Start the simulation
	for (i = 0; i < number_of_philosophers; i++) {
		pthread_create(&philosophers[i].thread, NULL, philo_behavior, &philosophers[i]);
	}

	// Wait for all philosophers to finish
	for (i = 0; i < number_of_philosophers; i++) {
		pthread_join(philosophers[i].thread, NULL);
	}

	// Cleanup
	free(philosophers);
	free(forks);

	return 0;
}