/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:26:04 by toshi             #+#    #+#             */
/*   Updated: 2024/06/22 22:52:47 by toshi            ###   ########.fr       */
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
	int		remained_time;

	limit = get_time() + ms_time;
	if (ms_time == 0)
		return ;
	if (ms_time > ADJUSTMENT_TIME)
	{
		while (!is_simulate_end(common)
			&& !is_dead(philo, common))
		{
			remained_time = (limit - get_time());
			if (remained_time <= ADJUSTMENT_TIME)
				break ;
			usleep((remained_time / 2) * 1000);
		}
	}
	while (get_time() <= limit)
		usleep(100);
}

// die_timeが過ぎてないか確認し、overならlockし、simulation_run_flagをfalseにする
// die_timeが10msの時、11ms過ぎた時点でdieになる実装
bool	is_dead(t_philo *philo, t_common *common)
{
	if ((int)(get_time() - philo->last_eat_time) > common->die_time)
	{
		put_active_log(philo, common, DIE, true);
		pthread_mutex_lock(&(common->lock));
		common->simulation_run_flag = false;
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
