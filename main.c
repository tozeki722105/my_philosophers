/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/05/15 19:05:54 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q philo");
// }

int main (int argc, char **argv)
{
	t_common	*common;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	*threads;
	
	fill_null(&common, &forks, &philos, &threads);
	philos = initialize(argc, argv, &common, &forks);
	if (!philos)
	{
		ft_putendl_fd("error", STDERR_FILENO);
		return (1);	
	}
	threads = (pthread_t *)malloc(common->philo_count * sizeof(pthread_t));
	philos->common->common_start = get_time();
	for (int i = 0; i < common->philo_count; i++)
		pthread_create(&(threads[i]), NULL, simulation, (void *)&(philos[i]));
	for (int i = 0; i < common->philo_count; i++)
		pthread_join(threads[i], NULL);
	finalize(common, forks, philos, threads);
}