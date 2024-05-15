/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:21:03 by toshi             #+#    #+#             */
/*   Updated: 2024/05/15 19:03:17 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_init(t_philo *philo)
{
	printf("philo_id=%d;\n", philo->id);
	printf("die_time=%d;\n", philo->common->philo_count);
	printf("die_time=%d;\n", philo->common->die_time);
	printf("eat_time=%d;\n", philo->common->eat_time);
	printf("sleep_time=%d;\n", philo->common->sleep_time);
	printf("must_eat_count=%d;\n", philo->common->must_eat_count);
	printf("eat_count=%d;\n", philo->eat_count);
	printf("right_fork.last_eat_id=%d;\n", philo->right_fork->last_eat_id);
	printf("left_fork.last_eat_id=%d;\n", philo->left_fork->last_eat_id);
	printf("\n\n");
}

// 自分が死んでいない && 他者も死んでいない && must_eat_countに達していない
// && 両フォークにアクセスできなかったら->sleep(100)
void	*simulation(void *data)
{
	t_philo *philo;
	t_common *common;

	philo = (t_philo *)data;
	common = philo->common;
	philo->last_eat_time = common->common_start;
	pthread_mutex_lock(&(common->someone_died_lock));
	print_init(philo);
	pthread_mutex_unlock(&(common->someone_died_lock));
	// while (!is_dead(philo, common) \
	// 	&& !is_someone_dead(common) \
	// 	&& !is_finished_eating(philo, common))
	// {
	// 	think(philo, common);
	// 	while (!is_dead(philo, common) \
	// 		&& !is_someone_dead(common) \
	// 		&& !can_take_pair_forks(philo))
	// 		usleep(100);
	// 	if (is_someone_dead(common))
	// 		return (NULL);
	// 	take_eat_release_sleep(philo, common);
	// }
	return (NULL);
}
