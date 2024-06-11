/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:26:04 by toshi             #+#    #+#             */
/*   Updated: 2024/05/18 02:20:49 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//0.まず死んでいるか確認
//1. A=time/9 B=time%9 
//2.9msごとにスリープ->死んでいるか確認 これをA回
//3.100umごとにスリープしてlimitを確認し続ける
void	msleep(int ms_time, t_philo *philo, t_common *common)
{
	t_ms	limit;
	t_ms	quotient;

	limit = get_time() + ms_time;
	if (ms_time == 0)
		return ;
	// if (ms_time >= DEAD_LINE)
	// {
	// 	quotient = ms_time / DEAD_LINE;
	// 	while (!is_simulate_end(common)
	// 		&& !is_dead(philo, common)
	// 		&& quotient--)
	// 		usleep(100 * DEAD_LINE);
	// }
	while (!is_simulate_end(common)
		&& !is_dead(philo, common)
		&& get_time() < limit)
		usleep(100);
}

// die_timeが過ぎてないか確認し、overならlockし、simulation_run_flagをfalseにする
// die_timeが10msの時、11ms過ぎた時点でdieになる実装
bool	is_dead(t_philo *philo, t_common *common)
{
	t_ms	now;

	now = get_time();
	if ((int)(now - philo->last_eat_time) > common->die_time)
	{
		pthread_mutex_lock(&(common->lock));
		common->simulation_run_flag = false;
		printf("%lu %d %s", now - common->start_time, philo->id, DIE);
		pthread_mutex_unlock(&(common->lock));
		return (true);
	}
	return (false);
}

bool	is_simulate_end(t_common *common)
{
	bool	ret;

	pthread_mutex_lock(&(common->lock));
	ret = (common->simulation_run_flag == false);
	pthread_mutex_unlock(&(common->lock));
	return (ret);
}

static bool	can_take_fork(t_fork *fork, t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&(fork->lock));
	ret = (fork->last_eat_id != philo->id);
	pthread_mutex_unlock(&(fork->lock));
	return (ret);
}

bool	can_take_pair_forks(t_philo *philo)
{
	return (can_take_fork(philo->left_fork, philo)
		&& can_take_fork(philo->right_fork, philo));
}
// bool tmp1;
// bool tmp2;

// pthread_mutex_lock(&(philo->left_fork->lock));
// tmp1 = (philo->left_fork->last_eat_id != philo->id);
// pthread_mutex_unlock(&(philo->left_fork->lock));
// pthread_mutex_lock(&(philo->right_fork->lock));
// tmp2 = (philo->right_fork->last_eat_id != philo->id);
// pthread_mutex_unlock(&(philo->right_fork->lock));
// return (tmp1 && tmp2);
