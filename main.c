/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/05/06 23:26:51 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *func(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->common->test));
	print_init(philo);
	printf("\n\n");
	pthread_mutex_unlock(&(philo->common->test));
	return (arg);
}

int main (int argc, char **argv)
{
	int			philo_count;
	t_common	common;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	*threads;
	int		i;
	
	if (!(argc == 5 || argc == 6))
		return (1);
	philo_count = atoi(argv[1]);
	common = init_common(argc, argv);
	forks = init_forks(philo_count);
	philos = init_philos(philo_count, &common, forks);
	threads = (pthread_t *)malloc(philo_count * sizeof(pthread_t));
	i = 0;
	while (i < philo_count)
	{
		pthread_create(&(threads[i]), NULL, func, (void *)&(philos[i]));
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	free(forks);
	free(philos);
}