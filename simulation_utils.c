/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:26:04 by toshi             #+#    #+#             */
/*   Updated: 2024/05/12 03:32:09 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_wrap(unsigned long mili_time)
{
	unsigned long limit;

	// unsigned long time = get_time();
	if (mili_time == 0)
		;
	else if (mili_time > 10)
	{
		limit = get_time() + mili_time;
		usleep((mili_time * 1000) - 10000);
		while (get_time() < limit)
			usleep(100 + 0);
		return ;
	}
	else
		usleep(mili_time * 1000);
	// printf("diff=%lu;\n", get_time() - time);
}

// ミリ秒単位で返す
unsigned long	get_time()
{
	struct timeval  time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	catch_fork(t_fork *fork, t_common *common, t_philo *philo, int hand_flag)
{
	if (hand_flag == RIGHT)
		printf("%10lu %d has taken a right\n", get_time() - common->common_start, philo->id);
	else if (hand_flag == LEFT)
		printf("%10lu %d has taken a left\n", get_time() - common->common_start, philo->id);
}

void	do_eat(t_philo *philo, t_common *common)
{
	philo->last_eat_time = get_time();
	printf("%10lu %d is eating\n", philo->last_eat_time - common->common_start, philo->id);
 	usleep_wrap(common->eat_time);
	philo->eat_count++;
}
void	release_fork(t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&(fork->lock));
	fork->last_eat_id = philo->id;
	pthread_mutex_unlock(&(fork->lock));
}

// TODO mutexして、someone_diedを確認し、trueだったら出力しない
void	do_sleep(t_philo *philo, t_common *common)
{
	printf("%10lu %d is sleeping\n", get_time() - common->common_start, philo->id);
	usleep_wrap(common->sleep_time);
}

void catch_eat_release_sleep(t_philo *philo, t_common *common)
{
	catch_fork(philo->left_fork, common, philo, LEFT);
	catch_fork(philo->right_fork, common, philo, RIGHT);
	do_eat(philo, common);
	release_fork(philo->left_fork, philo);
	release_fork(philo->right_fork, philo);
	do_sleep(philo, common);
}
