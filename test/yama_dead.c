#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#define PHILOS 5

int sleep_seconds = 0;

typedef struct s_table {
	int	delay;
	pthread_mutex_t food_lock;
	int	food;
	pthread_mutex_t fork[PHILOS];
	int forks[PHILOS];
} t_table;

t_table table;

// typedef struct s_philo {
// 	size_t 
// }

// void grab_fork (int phil, int c, char *hand)
// {
// 	pthread_mutex_lock (&fork[c]);
// 	printf ("Philosopher %d: got %s fork %d\n", phil, hand, c);
// }

// void down_forks (int c1, int c2)
// {
// 	pthread_mutex_unlock (&fork[c1]);
// 	pthread_mutex_unlock (&fork[c2]);
// }

// int food_on_table ()
// {
// 	static int food = FOOD;
// 	int myfood;

// 	pthread_mutex_lock (&food_lock);
// 	if (food > 0) {
// 		food--;
// 	}
// 	myfood = food;
// 	pthread_mutex_unlock (&food_lock);
// 	return myfood;
// }

void *func(void *num)
{
	int id;
	int i;
	int left_fork;
	int right_fork;
	int f;

	id = (int)num;
	printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
	right_fork = id;
	left_fork = id + 1;

	/* Wrap around the forks. */
	if (left_fork == PHILOS)
		left_fork = 0;

	while (f = food_on_table ()) {

		/* Thanks to philosophers #1 who would like to take a nap
		* before picking up the forks, the other philosophers
		* may be able to eat their dishes and not deadlock.
		*/
		if (id == 1)
			sleep (sleep_seconds);

		grab_fork (id, right_fork, "right ");
		grab_fork (id, left_fork, "left");

		printf ("Philosopher %d: eating.\n", id);
		usleep (DELAY * (FOOD - f + 1));
		down_forks (left_fork, right_fork);
	}

	printf ("Philosopher %d is done eating.\n", id);
	return (NULL);
}

void	init(t_table *table)
{
	table->delay = 500;
	table->food = 100;
	pthread_mutex_init(&(table->food_lock), NULL);
	for (int i = 0; i < PHILOS; i++)
		pthread_mutex_init(&(table->fork[i]), NULL);
}

int main (int argc, char **argv)
{
	pthread_t philo[PHILOS];

	init(&table);
	for (int i = 0; i < PHILOS; i++)
		pthread_create(&philo[i], NULL, func, (void *)i);
	for (int i = 0; i < PHILOS; i++)
		pthread_join(philo[i], NULL);
	return 0;
}

