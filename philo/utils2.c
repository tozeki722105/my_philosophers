/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:33:32 by toshi             #+#    #+#             */
/*   Updated: 2024/06/11 16:12:53 by toshi            ###   ########.fr       */
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

// die以外のlogを出力する
void	put_active_log(t_philo *philo, t_common *common, char *status)
{

	pthread_mutex_lock(&(common->lock));
	if (!common->simulation_run_flag)
	{
		pthread_mutex_unlock(&(common->lock));
		return ;
	}
	printf("%lu %d %s\n",
		get_time() - common->start_time, philo->id, status);
	pthread_mutex_unlock(&(common->lock));
}
