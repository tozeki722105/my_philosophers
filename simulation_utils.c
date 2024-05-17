/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:26:04 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 12:55:44 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// die_timeが過ぎてないか確認し、overならlockし、someone_diedをtrueにする
// die_timeが10msの時、11ms過ぎた時点でdieになる実装
bool	is_dead(t_philo *philo, t_common *common)
{
	t_ms	now;
	
	now = get_time();
	if (now - philo->last_eat_time > common->die_time)
	{
		pthread_mutex_lock(&(common->someone_died_lock));
		common->someone_died = true;
		pthread_mutex_unlock(&(common->someone_died_lock));
		printf("%lu %d died\n", now - philo->start_time, philo->id);
		return (true);
	}
	return (false);
}

//0.まず死んでいるか確認
//1. A=time/9 B=time%9 
//2.9msごとにスリープ->死んでいるか確認 これをA回
//3.100umごとにスリープしてlimitを確認し続ける
void	msleep(int ms_time, t_philo *philo, t_common *common)
{
	t_ms limit;
	t_ms quotient;

	limit = get_time() + ms_time;
	if (ms_time == 0)
		return ;
	if (ms_time >= DEAD_LINE)
	{
		quotient = ms_time / DEAD_LINE;
		while (!is_someone_dead(common) \
			&& !is_dead(philo, common) \
			&& quotient--)
			usleep(100 * DEAD_LINE);
	}
	while (!is_someone_dead(common) \
		&& !is_dead(philo, common) \
		&& get_time() < limit)
		usleep(100);
}

bool	can_take_pair_forks(t_philo *philo)
{
	bool tmp1;
	bool tmp2;

	pthread_mutex_lock(&(philo->left_fork->lock));
	tmp1 = (philo->left_fork->last_eat_id != philo->id);
	pthread_mutex_unlock(&(philo->left_fork->lock));
	pthread_mutex_lock(&(philo->right_fork->lock));
	tmp2 = (philo->right_fork->last_eat_id != philo->id);
	pthread_mutex_unlock(&(philo->right_fork->lock));
	return (tmp1 && tmp2);
}

bool	is_finished_eating(t_philo *philo, t_common *common)
{
	return (common->must_eat_count != NO_COUNT \
		&& philo->eat_count >= common->must_eat_count);
}

bool	is_someone_dead(t_common *common)
{
	bool ret;

	pthread_mutex_lock(&(common->someone_died_lock));
	ret = (common->someone_died);
	pthread_mutex_unlock(&(common->someone_died_lock));
	return (ret);
}

void	think(t_philo *philo, t_common *common)
{
	printf("%10lu %d is thinking\n", \
		get_time() - philo->start_time, philo->id);
}

void	take_eat_release_sleep(t_philo *philo, t_common *common)
{
	printf("%10lu %d has taken a right\n", \
		get_time() - philo->start_time, philo->id);
	printf("%10lu %d has taken a left\n", \
		get_time() - philo->start_time, philo->id);
	philo->last_eat_time = get_time();
	printf("%10lu %d is eating\n", \
		philo->last_eat_time - philo->start_time, philo->id);
 	msleep(common->eat_time, philo, common);
	philo->eat_count++;
	pthread_mutex_lock(&(philo->left_fork->lock));
	philo->left_fork->last_eat_id = philo->id;
	pthread_mutex_unlock(&(philo->left_fork->lock));
	pthread_mutex_lock(&(philo->right_fork->lock));
	philo->right_fork->last_eat_id = philo->id;
	pthread_mutex_unlock(&(philo->right_fork->lock));
	if (is_someone_dead(common))
		return ;
	printf("%10lu %d is sleeping\n", \
		get_time() - philo->start_time, philo->id);
	msleep(common->sleep_time, philo, common);
}
