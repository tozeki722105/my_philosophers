/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 00:22:44 by toshi             #+#    #+#             */
/*   Updated: 2024/06/09 19:02:47 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	initialize_philos(int philo_count, t_common *common, t_fork *forks,
			t_philo **philo)
{
	t_philo		*philos_cpy;
	int			i;

	philos_cpy = (t_philo *)malloc_wrap(philo_count * sizeof(t_philo));
	if (!philos_cpy)
		return (false);
	i = 0;
	while (i < philo_count)
	{
		philos_cpy[i].common = common;
		philos_cpy[i].id = i + 1;
		philos_cpy[i].last_eat_time = 0;
		philos_cpy[i].eat_count = 0;
		if (i == 0)
			philos_cpy[i].right_fork = &(forks[philo_count - 1]);
		else
			philos_cpy[i].right_fork = &(forks[i - 1]);
		philos_cpy[i].left_fork = &(forks[i]);
		i++;
	}
	*philo = philos_cpy;
	return (true);
}
