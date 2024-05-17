/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:57:17 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 21:09:14 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_arg_overflow(t_common common, int argc)
{
	if (common.philo_count == ERROR \
		|| common.die_time == ERROR \
		|| common.eat_time == ERROR \
		|| common.sleep_time == ERROR \
		|| (argc == 6 && common.must_eat_count == ERROR))
	{
		print_err("There is an argument for int_overflow");
		return (true);
	}
	return (false);
}

// 数値だけの文字列限定、自然数限定のatoi
// 数字以外を含んだ文字列(+/-含む)は事前にハジく必要あり
static int	atoi_for_natural(const char *str)
{
	int	num;

	num = 0;
	while (*str)
	{	
		if (num > (INT_MAX / 10)
			|| (num == (INT_MAX / 10) && (*str - '0') > (INT_MAX % 10)))
			return (-1);
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}

bool	initialize_common(int argc, char **argv, t_common **common)
{
	t_common *common_cpy;

	common_cpy = (t_common *)malloc_wrap(sizeof(t_common));
	if (!common_cpy)
		return (false);
	common_cpy->philo_count = atoi_for_natural(argv[1]);
	common_cpy->die_time = atoi_for_natural(argv[2]);
	common_cpy->eat_time = atoi_for_natural(argv[3]);
	common_cpy->sleep_time = atoi_for_natural(argv[4]);
	if (argc == 6)
		common_cpy->must_eat_count = atoi_for_natural(argv[5]);
	else
		common_cpy->must_eat_count = NO_COUNT;
	if (is_arg_overflow(*common_cpy, argc) \
		|| mutex_init_wrap(&(common_cpy->someone_died_lock)) == ERROR)
	{
		free(common_cpy);
		return (false);
	}
	common_cpy->someone_died = false;
	if (mutex_init_wrap(&(common_cpy->ready_flag_lock)) == ERROR)
	{
		pthread_mutex_destroy(&(common_cpy->someone_died_lock));
		free(common_cpy);
		return (false);
	}
	common_cpy->ready_flag = false;
	common_cpy->common_start = 0;
	*common = common_cpy;
	return (true);
}

bool	initialize_philos(int philo_count, t_common *common, t_fork *forks, t_philo **philo)
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
		philos_cpy[i].start_time = 0;
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

bool	initialize_and_create_threads(pthread_t **threads, t_common *common, t_philo *philos)
{
	pthread_t *threads_cpy;
	int i;

	threads_cpy = (pthread_t *)malloc_wrap(common->philo_count * sizeof(pthread_t));
	if (!threads_cpy)
		return (false);
	*threads = threads_cpy;
	i = 0;
	while (i < common->philo_count)
	{
		if (pthread_create_wrap(&(threads_cpy[i]), simulation, (void *)&(philos[i])) != 0)
			break ;
		i++;
	}
	if (i < common->philo_count)
	{
		pthread_mutex_lock(&(common->ready_flag_lock));
		common->ready_flag = ERROR;
		pthread_mutex_unlock(&(common->ready_flag_lock));
		return (false);
	}
	pthread_mutex_lock(&(common->ready_flag_lock));
	common->ready_flag = true;
	pthread_mutex_unlock(&(common->ready_flag_lock));
	return (true);
}
