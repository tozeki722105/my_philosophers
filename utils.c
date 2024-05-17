/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:29:16 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 14:08:54 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ミリ秒単位で返す
t_ms	get_time()
{
	struct timeval  time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_err(char *s)
{
	ft_putendl(s, STDERR_FILENO);
}

void	*malloc_wrap(size_t size)
{
	void *ret;
	
	ret = malloc(size);
	if (!ret)
		print_err("malloc error");
	return (ret);
}

int	mutex_init_wrap(pthread_mutex_t *mutex)
{
	int ret;

	ret = pthread_mutex_init(mutex, NULL);
	if (ret == ERROR)
		print_err("mutex error");
	return (ret);
}

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
