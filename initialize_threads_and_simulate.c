/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_threads_and_simulate.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:57:17 by toshi             #+#    #+#             */
/*   Updated: 2024/05/18 01:26:31 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads_and_ret_count(pthread_t *threads_cpy, t_philo *philos, int philo_count)
{
	int i;

	i = 0;
	while (i < philo_count \
		&& pthread_create_wrap(&(threads_cpy[i]), simulate, (void *)&(philos[i])) == SUCCESS)
		i++;
	return (i);
}

bool	initialize_threads_and_simulate(pthread_t **threads, t_common *common, t_philo *philos)
{
	pthread_t *threads_cpy;

	threads_cpy = (pthread_t *)malloc_wrap(common->philo_count * sizeof(pthread_t));
	if (!threads_cpy)
		return (false);
	common->create_count = create_threads_and_ret_count(threads_cpy, philos, common->philo_count);
	common->start_time = get_time();
	pthread_mutex_lock(&(common->lock));
	common->start_flag = (common->create_count == common->philo_count);
	pthread_mutex_unlock(&(common->lock));
	*threads = threads_cpy;
	return (true);
}
