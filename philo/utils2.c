/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:33:32 by toshi             #+#    #+#             */
/*   Updated: 2024/06/10 18:19:38 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks_mutex(t_fork *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(forks[i].lock));
		i++;
	}
}

void	put_log(t_philo *philo, t_common *common, char *status)
{
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	if (is_simulate_end(common))
	{
		pthread_mutex_unlock(&lock);
		return ;
	}
	printf("%lu %d %s\n",
		get_time() - common->start_time, philo->id, status);
	pthread_mutex_unlock(&lock);
}
