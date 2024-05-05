#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 4

typedef enum e_fork_state
{
	USING	= -1,
	USED	= 0,
	WAIT	= 1
}	t_fstate;

typedef struct s_table
{
	int				seat_id;
	t_fstate		forks[NUM];
	pthread_mutex_t	mutex;
}	t_table;

typedef struct s_philo
{
	int	id;
	int	left;
	int	right;
}	t_philo;



void * func(void *arg)
{
	t_table	*table;
	t_philo	philo;

	table = (t_table *)arg;
	philo.id = table->seat_id;

	if (philo.id == 0)
		philo.right = NUM - 1;
	else
		philo.right = philo.id - 1;
	philo.left = philo.id;

	if (table->forks[philo.right] == WAIT)
	{
		table->forks[philo.right] = philo.id;
	}
	if (table->forks[philo.left] == WAIT)
	{
		table->forks[philo.left] = philo.id;
	}
	if (table->forks[philo.right] == philo.id && table->forks[philo.left] == philo.id)
	{
		printf("%d番目の哲学者は食事中\n", philo.id);
		usleep(50000);
		table->forks[philo.right] = WAIT;
		table->forks[philo.left] = WAIT;
		usleep(50000);
	}

	if (table->forks[philo.right] == WAIT)
	{
		table->forks[philo.right] = philo.id;
	}
	if (table->forks[philo.left] == WAIT)
	{
		table->forks[philo.left] = philo.id;
	}
	if (table->forks[philo.right] == philo.id && table->forks[philo.left] == philo.id)
	{
		printf("%d番目の哲学者は食事中\n", philo.id);
		// table->forks[philo.right] = WAIT;
		// table->forks[philo.left] = WAIT;
	}
	return (NULL);
}



int main()
{
	pthread_t	th[NUM];
	t_table		table;
	int			i;
	
	pthread_mutex_init(&(table.mutex), NULL);
	table.seat_id = 0;
	i = 0;
	while(i < NUM)
	{
		table.forks[i] = WAIT;
		i++;
	}

	i = 0;
	while(i < NUM)
	{
		pthread_create(&(th[i]), NULL, func, &table);
		usleep(10000);
		table.seat_id++;
		i++;
	}

	i = 0;
	while(i < NUM)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&(table.mutex));
}


while(i < NUM)
{
	A();
	B();
	C();
	D();
}