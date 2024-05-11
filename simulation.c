/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:21:03 by toshi             #+#    #+#             */
/*   Updated: 2024/05/12 03:40:18 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// die_timeが過ぎてないか確認し、overならlockし、someone_diedをtrueにする
bool	is_dead(t_philo *philo, t_common *common)
{
	unsigned long	now;
	
	now = get_time();
	if (now - philo->last_eat_time >= common->die_time)
	{
		pthread_mutex_lock(&(common->someone_died_lock));
		common->someone_died = true;
		pthread_mutex_unlock(&(common->someone_died_lock));
		printf("%lu %d died\n", now - common->common_start, philo->id);
		return (true);
	}
	return (false);
}

bool	is_someone_dead(t_common *common)
{
	bool ret;

	pthread_mutex_lock(&(common->someone_died_lock));
	ret = (common->someone_died);
	pthread_mutex_unlock(&(common->someone_died_lock));
	return (ret);
}

// lockをかけ、enc_philos_count++し、NULLを返す
void	*terminate(t_common *common)
{
	pthread_mutex_lock(&(common->end_philos_count_lock));
	common->end_philos_count++;
	pthread_mutex_unlock(&(common->end_philos_count_lock));
	return (NULL);
}

// forkのlast_eat_idとphilo->idが違う かつ catched_id が NO_CATCHEDのとき
// 後半の条件文は今のアルゴリズムではいらない？？
bool can_catch_fork(t_fork *fork, t_philo *philo)
{
	bool ret;

	pthread_mutex_lock(&(fork->lock));
	ret = (fork->last_eat_id != philo->id);
	pthread_mutex_unlock(&(fork->lock));
	return (ret);
}

// int decide_catch_forks_or_think(t_philo *philo, t_common *common)
// {
// 	if (can_catch_fork(philo->left_fork, philo) \
// 	&& can_catch_fork(philo->right_fork, philo))
// 		return (CATCH_FORKS);
// 	printf("%10lu %d is thinking\n", get_time() - common->common_start, \
// 		philo->id);
// 	return (THINK);
// }

// 自分が死んでいない && 他者も死んでいない && must_eat_countに達していない
// && 両フォークにアクセスできなかったら->sleep(100)
void *func(void *data)
{
	t_philo *philo;
	t_common *common;

	philo = (t_philo *)data;
	common = philo->common;
	philo->last_eat_time = common->common_start;
	while (1)
	{
		printf("%10lu %d is thinking\n", get_time() - common->common_start, philo->id);
		while (!is_dead(philo, common) \
			&& !is_someone_dead(common) \
			&& philo->eat_count < common->must_eat_count \
			&& !(can_catch_fork(philo->left_fork, philo) \
			&& can_catch_fork(philo->right_fork, philo)))
			usleep(100);
		if (is_someone_dead(common) || philo->eat_count >= common->must_eat_count)
			break ;
		catch_eat_release_sleep(philo, common);
	}
	return (terminate(common));
}
// if (left_fork->last_eat_id != philo->id && left_fork->catched_id == NO_CATCHED)
// if (right_fork->last_eat_id != philo->id && right_fork->catched_id == NO_CATCHED)
// if (left_fork->catched_id == philo->id && right_fork->catched_id == philo->id)
// usleep(100);