/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:29:16 by toshi             #+#    #+#             */
/*   Updated: 2024/06/11 18:31:34 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ミリ秒単位で返す
t_ms	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	put_err(char *s)
{
	ft_putendl(s, STDERR_FILENO);
}

void	*malloc_wrap(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		put_err("malloc error");
	return (ret);
}

int	mutex_init_wrap(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_init(mutex, NULL);
	if (ret != SUCCESS)
		put_err("mutex error");
	return (ret);
}

int	pthread_create_wrap(pthread_t *thread, void *(*routine)(void *), void *arg)
{
	int	ret;

	ret = pthread_create(thread, NULL, routine, arg);
	if (ret != SUCCESS)
		put_err("pthread_create error");
	return (ret);
}
