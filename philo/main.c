/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/06/11 20:41:48 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// __attribute__((destructor))
//  static void destructor() {
//     system("leaks -q philo");
// }

void	set_null(t_common **common, t_fork **forks, t_philo **philos,
			pthread_t **threads)
{
	*common = NULL;
	*forks = NULL;
	*philos = NULL;
	*threads = NULL;
}

void	finalize(t_common *common, t_fork *forks, t_philo *philos,
			pthread_t *threads)
{
	if (threads)
		free(threads);
	if (philos)
		free(philos);
	if (forks)
	{
		destroy_forks_mutex(forks, common->philo_count);
		free(forks);
	}
	if (common)
	{
		pthread_mutex_destroy(&(common->lock));
		free(common);
	}
}

void	wait_threads(pthread_t *threads, t_common *common)
{
	int	i;

	while (!is_simulate_end(common))
	{
		usleep(1000);
		pthread_mutex_lock(&(common->lock));
		if (common->eat_up_count == common->philo_count)
		{
			common->simulation_run_flag = false;
			pthread_mutex_unlock(&(common->lock));
			break ;
		}
		pthread_mutex_unlock(&(common->lock));
	}
	i = 0;
	while (i < common->created_threads_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_common	*common;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	*threads;

	set_null(&common, &forks, &philos, &threads);
	if (!validate_args(argc, argv)
		|| !initialize_common(argc, argv, &common)
		|| !initialize_forks(common->philo_count, &forks)
		|| !initialize_philos(common->philo_count, common, forks, &philos)
		|| !initialize_threads_and_simulate(&threads, common, philos))
	{
		finalize(common, forks, philos, threads);
		return (FAIL_EXIT_STATUS);
	}
	wait_threads(threads, common);
	finalize(common, forks, philos, threads);
	return (SUCCESS_EXIT_STATUS);
}
