/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:21:03 by toshi             #+#    #+#             */
/*   Updated: 2024/05/18 02:20:44 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	can_start(t_common *common)
{
	bool	ret;

	while (1)
	{
		pthread_mutex_lock(&(common->lock));
		if (common->simulation_run_flag != DEFAULT)
		{
			ret = common->simulation_run_flag;
			pthread_mutex_unlock(&(common->lock));
			return (ret);
		}
		pthread_mutex_unlock(&(common->lock));
	}
}

// eatingの回数がmeetしているか確認する
static void	check_eating_met(t_philo *philo, t_common *common)
{
	if (common->must_eat_count != NO_COUNT
		&& philo->eat_count == common->must_eat_count)
	{
		pthread_mutex_lock(&(common->lock));
		common->eat_up_count++;
		pthread_mutex_unlock(&(common->lock));
	}
}

static bool	can_take_fork(t_fork *fork, t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&(fork->lock));
	ret = (fork->last_eat_id != philo->id);
	pthread_mutex_unlock(&(fork->lock));
	return (ret);
}

static bool	can_take_pair_forks(t_philo *philo)
{
	if (!(philo->right_fork && philo->left_fork))
		return (false);	
	return (can_take_fork(philo->left_fork, philo)
		&& can_take_fork(philo->right_fork, philo));
}

void	*simulate(void *data)
{
	t_philo		*philo;
	t_common	*common;

	philo = (t_philo *)data;
	common = philo->common;
	if (!can_start(common))
		return (NULL);
	philo->last_eat_time = common->start_time;
	while (!is_simulate_end(common)
		&& !is_dead(philo, common))
	{
		check_eating_met(philo, common);
		think(philo, common);
		while (!is_simulate_end(common)
			&& !is_dead(philo, common)
			&& !can_take_pair_forks(philo))
			usleep(100);
		if (is_simulate_end(common))
			return (NULL);
		take_eat_release_sleep(philo, common);
	}
	return (NULL);
}
