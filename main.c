/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 02:20:34 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__attribute__((destructor))
 static void destructor() {
    system("leaks -q philo");
}

void	set_null(t_common **common, t_fork **forks, t_philo **philos, pthread_t **threads)
{
	*common = NULL;
	*forks = NULL;
	*philos = NULL;
	*threads = NULL;
}

void	finalize(t_common *common, t_fork *forks, t_philo *philos, pthread_t *threads)
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
		pthread_mutex_destroy(&(common->someone_died_lock));
		free(common);
	}
}

bool	initialize_and_create_threads(pthread_t **threads, t_common *common, t_philo *philos)
{
	pthread_t *threads_cpy;
	int i;

	threads_cpy = (pthread_t *)malloc_wrap(common->philo_count * sizeof(pthread_t));
	if (!threads_cpy)
		return (false);
	*threads = threads_cpy;
	i = 0;
	while (i < common->philo_count)
	{
		pthread_create(&(threads_cpy[i]), NULL, simulation, (void *)&(philos[i]));
		i++;
	}
	return (true);
}

void	wait_threads(pthread_t *threads, t_common *common)
{
	int i;

	i = 0;
	while (i < common->philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int main (int argc, char **argv)
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
		|| !initialize_and_create_threads(&threads, common, philos))
	{
		finalize(common, forks, philos, threads);
		return (FAIL_EXIT_STATUS);
	}
	wait_threads(threads, common);
	finalize(common, forks, philos, threads);
	return (SUCCESS_EXIT_STATUS);
}
