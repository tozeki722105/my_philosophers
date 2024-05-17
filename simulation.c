/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:21:03 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 21:04:54 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_philo(t_philo *philo)
{
	printf("philo_id=%d;\n", philo->id);
	printf("start_time=%lu;\n", philo->start_time);
	printf("laste_time=%lu;\n", philo->last_eat_time);
	printf("die_time=%d;\n", philo->common->die_time);
	printf("eat_time=%d;\n", philo->common->eat_time);
	printf("sleep_time=%d;\n", philo->common->sleep_time);
	printf("must_eat_count=%d;\n", philo->common->must_eat_count);
	printf("eat_count=%d;\n", philo->eat_count);
	printf("right_fork.last_eat_id=%d;\n", philo->right_fork->last_eat_id);
	printf("left_fork.last_eat_id=%d;\n", philo->left_fork->last_eat_id);
	printf("\n\n");
}

bool wait_start(t_common *common, t_philo *philo)
{
	while (1)
	{
		printf("id=%d\n", philo->id);
		pthread_mutex_lock(&(common->ready_flag_lock));
		if (common->ready_flag != false)
		{
			pthread_mutex_unlock(&(common->ready_flag_lock));
			return (common->ready_flag == true);
		}
		pthread_mutex_unlock(&(common->ready_flag_lock));
	}
}

// 自分が死んでいない && 他者も死んでいない && must_eat_countに達していない
// && 両フォークにアクセスできなかったら->sleep(100)
void	*simulation(void *data)
{
	t_philo *philo;
	t_common *common;

	philo = (t_philo *)data;
	common = philo->common;
	//if (!wait_start(common, philo))
	//	return (NULL);
	philo->start_time = get_time();
	philo->last_eat_time = philo->start_time;
	while (!is_someone_dead(common) \
		&& !is_dead(philo, common) \
		&& !is_finished_eating(philo, common))
	{
		think(philo, common);
		while (!is_someone_dead(common) \
			&& !is_dead(philo, common) \
			&& !can_take_pair_forks(philo))
			usleep(100);
		if (is_someone_dead(common))
			return (NULL);
		take_eat_release_sleep(philo, common);
	}
	return (NULL);
}
