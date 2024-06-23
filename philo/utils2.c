/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:33:32 by toshi             #+#    #+#             */
/*   Updated: 2024/06/24 04:15:00 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulate_end(t_common *common)
{
	bool	ret;

	pthread_mutex_lock(&(common->lock));
	ret = (common->simulation_run_flag == false);
	pthread_mutex_unlock(&(common->lock));
	return (ret);
}

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
