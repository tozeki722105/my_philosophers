/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:26:04 by toshi             #+#    #+#             */
/*   Updated: 2024/05/15 19:03:04 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// die_timeが過ぎてないか確認し、overならlockし、someone_diedをtrueにする
bool	is_dead(t_philo *philo, t_common *common)
{
	t_ms	now;
	
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

void	usleep_wrap(int ms_time)
{
	t_ms limit;

	if (ms_time == 0)
		return ;
	if (ms_time > 10)
	{
		limit = get_time() + ms_time;
		usleep((ms_time * 1000) - 11000);
		while (get_time() < limit)
			usleep(100);
		return ;
	}
	usleep(ms_time * 1000);
}

bool	is_someone_dead(t_common *common)
{
	bool ret;

	pthread_mutex_lock(&(common->someone_died_lock));
	ret = (common->someone_died);
	pthread_mutex_unlock(&(common->someone_died_lock));
	return (ret);
}

// ミリ秒単位で返す
t_ms	get_time()
{
	struct timeval  time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	think(t_philo *philo, t_common *common)
{
	printf("%10lu %d is thinking\n", \
		get_time() - common->common_start, philo->id);
}

void	take_eat_release_sleep(t_philo *philo, t_common *common)
{
	printf("%10lu %d has taken a right\n", \
		get_time() - common->common_start, philo->id);
	printf("%10lu %d has taken a left\n", \
		get_time() - common->common_start, philo->id);
	philo->last_eat_time = get_time();
	printf("%10lu %d is eating\n", \
		philo->last_eat_time - common->common_start, philo->id);
 	usleep_wrap(common->eat_time);
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
		get_time() - common->common_start, philo->id);
	usleep_wrap(common->sleep_time);
}

// // forkのlast_eat_idとphilo->idが違う かつ catched_id が NO_CATCHEDのとき
// // 後半の条件文は今のアルゴリズムではいらない？？
// bool can_take_fork(t_fork *fork, t_philo *philo)
// {
// 	bool ret;

// 	pthread_mutex_lock(&(fork->lock));
// 	ret = (fork->last_eat_id != philo->id);
// 	pthread_mutex_unlock(&(fork->lock));
// 	return (ret);
// }

// void	take_fork(t_fork *fork, t_common *common, t_philo *philo, int hand_flag)
// {
// 	if (hand_flag == RIGHT)
// 		printf("%10lu %d has taken a right\n", get_time() - common->common_start, philo->id);
// 	else if (hand_flag == LEFT)
// 		printf("%10lu %d has taken a left\n", get_time() - common->common_start, philo->id);
// }

// void	do_eat(t_philo *philo, t_common *common)
// {
// 	philo->last_eat_time = get_time();
// 	printf("%10lu %d is eating\n", philo->last_eat_time - common->common_start, philo->id);
//  	usleep_wrap(common->eat_time);
// 	philo->eat_count++;
// }
// void	release_fork(t_fork *fork, t_philo *philo)
// {
// 	pthread_mutex_lock(&(fork->lock));
// 	fork->last_eat_id = philo->id;
// 	pthread_mutex_unlock(&(fork->lock));
// }

// // TODO mutexして、someone_diedを確認し、trueだったら出力しない
// void	do_sleep(t_philo *philo, t_common *common)
// {
// 	printf("%10lu %d is sleeping\n", get_time() - common->common_start, philo->id);
// 	usleep_wrap(common->sleep_time);
// }
