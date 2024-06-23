/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:13:27 by toshi             #+#    #+#             */
/*   Updated: 2024/06/23 19:33:52 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, t_common *common)
{
	put_active_log(philo, common, THINK, false);
}

static void	do_eat(t_philo *philo, t_common *common)
{
	philo->last_eat_time = get_time();
	put_active_log(philo, common, EAT, false);
	msleep(common->eat_time, philo, common);
	philo->eat_count++;
}

static void	release_fork(t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&(fork->lock));
	fork->last_eat_id = philo->id;
	pthread_mutex_unlock(&(fork->lock));
}

static void	do_sleep(t_philo *philo, t_common *common)
{
	put_active_log(philo, common, SLEEP, false);
	msleep(common->sleep_time, philo, common);
}

void	take_eat_release_sleep(t_philo *philo, t_common *common)
{
	put_active_log(philo, common, TAKE_FORK, false);
	put_active_log(philo, common, TAKE_FORK, false);
	do_eat(philo, common);
	if (is_simulate_end(common) || is_dead(philo, common))
		return ;
	release_fork(philo->left_fork, philo);
	release_fork(philo->right_fork, philo);
	do_sleep(philo, common);
}
