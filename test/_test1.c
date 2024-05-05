#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 4

typedef enum e_fork_state
{
	USED	= 0,
	STAY	= 1
}	t_fstate;

typedef struct s_table
{
	int				seat_id;
	t_fstate		forks[NUM];
	pthread_mutex_t	mutex;
}	t_table;

typedef struct s_philo
{
	int			id;
}	t_philo;

// void * func(void *arg)
// {
// 	t_table	*table;
// 	t_philo	philo;

// 	table = (t_table *)arg;
// 	philo.id = table->seat_id;

	
// 	if (philo.id % 2 == 0)
// 		table->forks[philo.id] = USED;
// 	if (philo.id % 2 == 0)
// 	{
// 		if (philo.id != 0)
// 			table->forks[philo.id - 1] = USED;
// 		else
// 			table->forks[NUM - 1] = USED;
// 	}
// 	usleep(10000);
	
// 	printf("philo_id %d, fork %d\n", philo.id, table->forks[philo.id]);	
// 	return (NULL);
// }


// void * func1(void *arg)
// {
// 	t_table	*table;
// 	t_philo	philo;

// 	table = (t_table *)arg;
// 	//飢餓時間を迎えるか、完食したら、抜ける
// 		//飢餓時間を迎えるか確認 -> 迎えていたらbreak;
// 		// 右手(id)のフォークに自分のNUMが記入されていない && (mutex) -1 = waitである
// 			// OKなら(mutex)そのフォークに自分のNUMを記入
// 		//飢餓時間を迎えるか確認 -> 迎えていたらbreak; 
// 		// 左手(id-1)の〜〜
// 			// OKなら〜〜
// 		//飢餓時間を迎えるか確認 -> 迎えていたらbreak;
// 		// 両手のフォークが自分のNUMが記入されている
// 			// OKなら、(mutex)食事数を-1して、(mutex)フォークをwaitさせて、睡眠をとる
// 	return (NULL);
// }


int main()
{
	pthread_t	th[NUM];
	t_table		table;
	int			i;
	
	//データの初期化
	pthread_mutex_init(&(table.mutex), NULL);
	table.seat_id = 0;
	i = 0;
	while(i < NUM)
	{
		table.forks[i] = STAY;
		i++;
	}

	//スレッドを生成し、実行
	// i = 0;
	// while(i < NUM)
	// {
		pthread_create(&(th[i]), NULL, func1, &table);
		usleep(10000);
		table.seat_id++;
		i++;
		pthread_create(&(th[i]), NULL, func2, &table);
		usleep(10000);
		table.seat_id++;
		i++;
		pthread_create(&(th[i]), NULL, func3, &table);
		usleep(10000);
		table.seat_id++;
		i++;
		pthread_create(&(th[i]), NULL, func4, &table);
		usleep(10000);
		table.seat_id++;
		i++;
	// }
	

	// 処理の終了待ち
	i = 0;
	while(i < NUM)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&(table.mutex));
}
