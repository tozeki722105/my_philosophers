/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:29:16 by toshi             #+#    #+#             */
/*   Updated: 2024/05/11 17:23:21 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_wrap(unsigned long time)
{
	unsigned long limit;

	if (time == 0)
		return ;
	//if (time > 10)
	//{
	//	limit = get_time() + time;
	//	usleep((time * 1000) - 10000); //10ms残す - 10000
	//	while (get_time() < limit)
	//		usleep(400); //((limit - get_time()) * 1000)
	//}
	//else
	//	usleep(time * 1000);
	
	unsigned long diff;
	
	limit = get_time() + time;
	diff = time * 1000;
	while (diff > 1000)
	{
		usleep(diff / 2);
		diff = (limit - get_time()) % 1000;
		printf("aaa=%lu\n", diff);
	}
}


//1ミリ秒=1
unsigned long	get_time()
{
	struct timeval  time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	do_eat(t_philo *philo, t_common *common)
{
	philo->last_eat_time = get_time();
	printf("%10lu %d is eating\n", philo->last_eat_time - common->common_start, philo->id);
	unsigned long time = get_time();
 	usleep_wrap(common->eat_time);
	printf("diff=%lu;\n", get_time() - time);
	philo->eat_count++;
}

void	do_sleep(t_philo *philo, t_common *common)
{
	printf("%10lu %d is sleeping\n", get_time() - common->common_start, philo->id);
	unsigned long time = get_time();
	usleep_wrap(common->sleep_time);
	printf("diff=%lu;\n", get_time() - time);
}

void	catch_fork(t_fork *fork, t_common *common, t_philo *philo, int hand_flag)
{
	if (hand_flag == RIGHT)
		printf("%10lu %d has taken a right\n", get_time() - common->common_start, philo->id);
	else if (hand_flag == LEFT)
		printf("%10lu %d has taken a left\n", get_time() - common->common_start, philo->id);
}

void	release_fork(t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&(fork->lock));
	fork->last_eat_id = philo->id;
	pthread_mutex_unlock(&(fork->lock));
	// fork->catched_id = NO_CATCHED;
}

void	eat_release_sleep(t_philo *philo, t_common *common)
{
	do_eat(philo, common);
	release_fork(philo->left_fork, philo);
	release_fork(philo->right_fork, philo);
	do_sleep(philo, common);
}

// die_timeが過ぎてないか確認し、overならlockし、someone_diedをtrueにする
bool	is_dead(t_philo *philo, t_common *common)
{
	unsigned long	time;
	
	time = get_time();
	if (time - philo->last_eat_time >= common->die_time)
	{
		pthread_mutex_lock(&(common->someone_died_lock));
		common->someone_died = true;
		pthread_mutex_unlock(&(common->someone_died_lock));	
		printf("%lu %d died\n", time - common->common_start, philo->id);
		return (true);
	}
	return (false);
}

// lockをかけ、enc_philos_count++し、NULLを返す
void	*terminate(t_common *common)
{
	pthread_mutex_lock(&(common->end_philos_count_lock));
	common->end_philos_count++;
	pthread_mutex_unlock(&(common->end_philos_count_lock));
	return (NULL);
}

// forkのlast_eat_idとphilo->idが違う かつ catched_id が NO_CATCHEDのとき
// 後半の条件文は今のアルゴリズムではいらない？？
bool can_catch_fork(t_fork *fork, t_philo *philo)
{
	return (fork->last_eat_id != philo->id);//&& fork->catched_id == NO_CATCHED
}
