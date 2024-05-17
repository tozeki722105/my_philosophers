/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_eat_release_sleep.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:13:27 by toshi             #+#    #+#             */
/*   Updated: 2024/05/18 02:14:01 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void do_eat(t_philo *philo, t_common *common)
{
	philo->last_eat_time = get_time();
	printf("%10lu %d is eating\n", \
		philo->last_eat_time - common->start_time, philo->id);
 	msleep(common->eat_time, philo, common);
	philo->eat_count++;
}

static void release_fork(t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&(fork->lock));
	fork->last_eat_id = philo->id;
	pthread_mutex_unlock(&(fork->lock));
}

static void	do_sleep(t_philo *philo, t_common *common)
{
	printf("%10lu %d is sleeping\n", get_time() - common->start_time, philo->id);
	msleep(common->sleep_time, philo, common);
}

// philo->last_eat_time = get_time();
// printf("%10lu %d is eating\n", \
// 	philo->last_eat_time - common->start_time, philo->id);
// msleep(common->eat_time, philo, common);
// philo->eat_count++;
// pthread_mutex_lock(&(philo->left_fork->lock));
// philo->left_fork->last_eat_id = philo->id;
// pthread_mutex_unlock(&(philo->left_fork->lock));
// pthread_mutex_lock(&(philo->right_fork->lock));
// philo->right_fork->last_eat_id = philo->id;
// pthread_mutex_unlock(&(philo->right_fork->lock));
void	take_eat_release_sleep(t_philo *philo, t_common *common)
{
	printf("%10lu %d has taken a right\n", \
		get_time() - common->start_time, philo->id);
	printf("%10lu %d has taken a left\n", \
		get_time() - common->start_time, philo->id);
	do_eat(philo, common);
	release_fork(philo->left_fork, philo);
	release_fork(philo->right_fork, philo);
	if (is_someone_dead(common))
		return ;
	do_sleep(philo, common);
}
// printf("%10lu %d is sleeping\n", \
// 	get_time() - common->start_time, philo->id);
// msleep(common->sleep_time, philo, common);