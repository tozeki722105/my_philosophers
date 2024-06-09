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

// static void	print_philo(t_philo *philo)
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

bool	can_start(t_common *common)
{
	while (1)
	{
		pthread_mutex_lock(&(common->lock));
		if (common->start_flag != DEFAULT)
		{
			pthread_mutex_unlock(&(common->lock));
			return (common->start_flag == true);
		}
		pthread_mutex_unlock(&(common->lock));
	}
}

void	think(t_philo *philo, t_common *common)
{
	printf("%lu %d is thinking\n",
		get_time() - common->start_time, philo->id);
}

bool	is_eating_finished(t_philo *philo, t_common *common)
{
	return (common->must_eat_count != NO_COUNT
		&& philo->eat_count >= common->must_eat_count);
}

// 自分が死んでいない && 他者も死んでいない && must_eat_countに達していない
// && 両フォークにアクセスできなかったら->sleep(100)
void	*simulate(void *data)
{
	t_philo		*philo;
	t_common	*common;

	philo = (t_philo *)data;
	common = philo->common;
	if (!can_start(common))
		return (NULL);
	philo->last_eat_time = common->start_time;
	while (!is_eating_finished(philo, common)
		&& !is_someone_dead(common)
		&& !is_dead(philo, common))
	{
		think(philo, common);
		while (!can_take_pair_forks(philo)
			&& !is_someone_dead(common)
			&& !is_dead(philo, common))
			usleep(100);
		if (is_someone_dead(common))
			return (NULL);
		take_eat_release_sleep(philo, common);
	}
	return (NULL);
}
