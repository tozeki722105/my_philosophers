/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/05/10 17:56:04 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q philo");
// }

// 自分が死んでいない && 他者も死んでいない && must_eat_countに達していない
// && 両フォークにアクセスできなかったら->sleep(100)
void *func(void *data)
{
	t_philo *philo;
	t_common *common;
	t_fork	*right_fork;
	t_fork	*left_fork;

	philo = (t_philo *)data;
	common = philo->common;
	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	philo->last_eat_time = common->common_start;
	while (1)
	{
		while (!is_dead(philo, common) && !common->someone_died \
			&& philo->eat_count < common->must_eat_count \
			&& !(can_catch_fork(left_fork, philo) && can_catch_fork(right_fork, philo)))
			usleep(100);
		if (common->someone_died || philo->eat_count >= common->must_eat_count)
			break ;
		catch_fork(left_fork, common, philo, LEFT);
		catch_fork(right_fork, common, philo, RIGHT);
		eat_release_sleep(philo, common);
	}
	return (terminate(common));
}
// if (left_fork->last_eat_id != philo->id && left_fork->catched_id == NO_CATCHED)
// if (right_fork->last_eat_id != philo->id && right_fork->catched_id == NO_CATCHED)
// if (left_fork->catched_id == philo->id && right_fork->catched_id == philo->id)
// usleep(100);

int main (int argc, char **argv)
{
	int			philo_count;
	t_common	common;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	*threads;
	
	if (!(argc == 5 || argc == 6))
		return (1);
	philo_count = atoi(argv[1]);
	common = init_common(argc, argv);
	forks = init_forks(philo_count);
	philos = init_philos(philo_count, &common, forks);
	threads = (pthread_t *)malloc(philo_count * sizeof(pthread_t));
	philos->common->common_start = get_time();
	for (int i = 0; i < philo_count; i++)
		pthread_create(&(threads[i]), NULL, func, (void *)&(philos[i]));
	for (int i = 0; i < philo_count; i++)
		pthread_join(threads[i], NULL);
	free(threads);
	free(forks);
	free(philos);
}