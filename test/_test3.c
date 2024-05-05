#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define	NUM		5
#define FOODS	10

typedef enum e_fork_state
{
	WAIT	= -1
}	t_fstate;

typedef struct s_table
{
	int				seat_id;
	t_fstate		forks[NUM];
	int				foods;
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

	//両手のフォーク番号を設定
	if (philo.id == 0)
		philo.right = NUM - 1;
	else
		philo.right = philo.id - 1;
	philo.left = philo.id;
	// printf("philo_id %d, right %d left %d\n", philo.id, philo.right, philo.left);
	
	while(table->foods > 0)
	{
		//哲学者の左右のフォークがWAITならフォークを持つ
		if (table->forks[philo.right] == WAIT)
		{
			table->forks[philo.right] = philo.id;
			// printf("%d番目の哲学者が 右 のフォ-クを持った\n", philo.id);
		}
		if (table->forks[philo.left] == WAIT)
		{
			table->forks[philo.left] = philo.id;
			// printf("%d番目の哲学者が 左 のフォ-クを持った\n", philo.id);
		}
		if (table->forks[philo.right] == philo.id && table->forks[philo.left] == philo.id)
		{
			printf("%d番目の哲学者は食事中\n", philo.id);
			usleep(100000); //飯食ってる
			table->foods--;
			table->forks[philo.right] = WAIT;
			table->forks[philo.left] = WAIT;
			usleep(100000); //寝てる
		}
		else
			usleep(100000);
	}
	return (NULL);
}



int main()
{
	pthread_t	th[NUM];
	t_table		table;
	int			i;
	
	//データの初期化
	pthread_mutex_init(&(table.mutex), NULL);
	table.seat_id = 0;
	table.foods = FOODS;
	i = 0;
	while(i < NUM)
	{
		table.forks[i] = WAIT;
		i++;
	}

	//スレッドを生成し、実行
	i = 0;
	while(i < NUM)
	{
		pthread_create(&(th[i]), NULL, func, &table);
		usleep(10000);
		table.seat_id++;
		i++;
	}

	// 処理の終了待ち
	i = 0;
	while(i < NUM)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&(table.mutex));


	i = 0;
	while(i < NUM)
	{
		if (table.forks[i] == WAIT)
			printf("fork[%d] = WAIT\n", i);
		else
			printf("fork[%d] = %dが持っている\n", i, table.forks[i]);
		i++;
	}	
}
