/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:33:32 by toshi             #+#    #+#             */
/*   Updated: 2024/05/18 02:33:40 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks_mutex(t_fork *forks, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(forks[i].lock));
		i++;
	}
}
