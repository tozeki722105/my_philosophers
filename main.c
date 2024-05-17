/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 21:22:06 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// __attribute__((destructor))
//  static void destructor() {
//     system("leaks -q philo");
// }

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
