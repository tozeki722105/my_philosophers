/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:26:04 by toshi             #+#    #+#             */
/*   Updated: 2024/07/02 16:24:41 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo, t_common *common)
{
	if (get_time() - philo->last_eat_time > (t_ms)common->die_time)
	{
		put_active_log(philo, common, DIE, true);
		pthread_mutex_lock(&(common->lock));
		common->simulation_run_flag = false;
		pthread_mutex_unlock(&(common->lock));
		return (true);
	}
	return (false);
}

void	put_active_log(t_philo *philo, t_common *common, char *status,
			bool put_stop)
{
	static pthread_mutex_t	put_lock = PTHREAD_MUTEX_INITIALIZER;
	static bool				active_flag = true;

	pthread_mutex_lock(&put_lock);
	if (!active_flag)
	{
		pthread_mutex_unlock(&put_lock);
		return ;
	}
	printf("%lu %d %s\n",
		get_time() - common->start_time, philo->id, status);
	active_flag = !put_stop;
	pthread_mutex_unlock(&put_lock);
}

void	msleep(int ms_time, t_philo *philo, t_common *common)
{
	t_ms	limit;
	int		remained_time;

	limit = get_time() + ms_time;
	if (ms_time == 0)
		return ;
	if (ms_time >= PUT_DIE_LIMIT)
	{
		while (!is_simulate_end(common)
			&& !is_dead(philo, common))
		{
			remained_time = limit - get_time();
			if (remained_time < PUT_DIE_LIMIT)
				break ;
			usleep(PUT_DIE_LIMIT_HALF_US);
		}
	}
	while (!is_simulate_end(common)
		&& !is_dead(philo, common)
		&& get_time() < limit)
		usleep(100);
}

// void	print_philo(t_philo *philo)
// {
// 	printf("philo_id=%d;\n", philo->id);
// 	printf("laste_time=%lu;\n", philo->last_eat_time);
// 	printf("die_time=%d;\n", philo->common->die_time);
// 	printf("eat_time=%d;\n", philo->common->eat_time);
// 	printf("sleep_time=%d;\n", philo->common->sleep_time);
// 	printf("must_eat_count=%d;\n", philo->common->must_eat_count);
// 	printf("eat_count=%d;\n", philo->eat_count);
// 	printf("right_fork.last_eat_id=%d;\n", philo->right_fork->last_eat_id);
// 	printf("left_fork.last_eat_id=%d;\n", philo->left_fork->last_eat_id);
// 	printf("\n\n");
// }
