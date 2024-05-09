/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:29:16 by toshi             #+#    #+#             */
/*   Updated: 2024/05/10 00:31:35 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	print_status(unsigned long start, int id, t_status status)
// {
// 	if (status == THINKING)
// 		printf("%lu %d is thinking\n", get_time() - start, id);
// 	else if (status == TAKE_FORK)
// 		printf("%lu %d has taken a fork\n", get_time() - start, id);
// 	else if (status == EATING)
// 		printf("%lu %d is eating\n", get_time() - start, id);
// 	else if (status == SLEEPING)
// 		printf("%lu %d is sleeping\n", get_time() - start, id);
// 	else
// 		printf("%lu %d died\n", get_time() - start, id);
	
// }

unsigned long	get_time()
{
	struct timeval  time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec/1000));
}

void	do_eat(t_philo *philo, t_common *common)
{
	philo->last_eat_time = get_time();
	printf("%10lu %d is eating\n", philo->last_eat_time - common->common_start, philo->id);
	usleep(common->eat_time * 1000);
	philo->eat_count++;
}

void	do_sleep(t_philo *philo, t_common *common)
{
	// printf("%10lu %d is sleeping\n", get_time() - start, id);
	usleep(common->sleep_time * 1000);
}

void	catch_fork_R(t_fork *fork, t_common *common, t_philo *philo)
{
	pthread_mutex_lock(&(fork->lock));
	fork->catched_id = philo->id;
	pthread_mutex_unlock(&(fork->lock));
	// printf("%10lu %d has taken a right\n", get_time() - common->common_start, philo->id);
}

void	catch_fork_L(t_fork *fork, t_common *common, t_philo *philo)
{
	pthread_mutex_lock(&(fork->lock));
	fork->catched_id = philo->id;
	pthread_mutex_unlock(&(fork->lock));
	// printf("%10lu %d has taken a left\n", get_time() - common->common_start, philo->id);
}

void	release_fork(t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&(fork->lock));
	fork->catched_id = NO_CATCHED;
	fork->last_eat_id = philo->id;
	pthread_mutex_unlock(&(fork->lock));
}

bool	is_dead(t_philo *philo, t_common *common)
{
	unsigned long	time;
	
	time = get_time();
	if (time - philo->last_eat_time >= common->die_time)
	{
		printf("%lu %d died\n", time - common->common_start, philo->id);
		return (true);
	}
	return (false);
}

void	*finish_full_ret_null(t_common *common)
{
	pthread_mutex_lock(&(common->eat_count_lock));
	common->end_eat_count++;
	pthread_mutex_unlock(&(common->eat_count_lock));
	return (NULL);
}

void	*finish_died_ret_null(t_common *common)
{
	pthread_mutex_lock(&(common->someone_died_lock));
	common->someone_died = true;
	pthread_mutex_unlock(&(common->someone_died_lock));
	return (NULL);
}
