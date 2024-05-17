/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:57:17 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 14:21:22 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_num_in_odd_pattern(int *array, int len)
{
	int i;
	int num;

	num = 2;
	i = 0;
	while (i + 3 < len)
	{
		array[i] = num;
		array[i + 1] = num;
		num += 2;
		i += 2;
	}
	array[i++] = num++;
	array[i++] = num;
	array[i] = num;
}

static void	set_num_in_even_pattern(int *array, int len)
{
	int i;
	int num;

	num = 2;
	i = 0;
	while (i < len)
	{
		array[i] = num;
		array[i + 1] = num;
		num += 2;
		i += 2;
	}
}

static int *make_last_eat_id_array(int philo_count)
{
	int *array;

	array = (int *)malloc_wrap(philo_count * sizeof(int));
	if (!array)
		return (NULL);
	if (philo_count == 1)
		array[0] = 0;
	else if (philo_count % 2 == 0)
		set_num_in_even_pattern(array, philo_count);
	else
		set_num_in_odd_pattern(array, philo_count);
	return (array);
}

static int	set_fork_data(int philo_count, t_fork *forks_cpy, int *last_eat_id_array)
{
	int i;

	i = 0;
	while (i < philo_count)
	{
		if (mutex_init_wrap(&(forks_cpy[i].lock)) == ERROR)
			break ;
		forks_cpy[i].last_eat_id = last_eat_id_array[i];
		i++;
	}
	return (i);
}

// memset(forks_cpy, '0', philo_count * sizeof(t_fork));
bool	initialize_forks(int philo_count, t_fork **forks)
{
	t_fork	*forks_cpy;
	int		*last_eat_id_array;
	int		set_count;

	forks_cpy = (t_fork *)malloc_wrap(philo_count * sizeof(t_fork));
	if (!forks_cpy)
		return (false);
	last_eat_id_array = make_last_eat_id_array(philo_count);
	if (!last_eat_id_array)
	{
		free(forks_cpy);
		return (false);
	}
	set_count = set_fork_data(philo_count, forks_cpy, last_eat_id_array);
	free(last_eat_id_array);
	if (set_count < philo_count)
	{
		destroy_forks_mutex(forks_cpy, set_count);
		free(forks_cpy);
		return (false);
	}
	*forks = forks_cpy;
	return (true);
}

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
		|| mutex_init_wrap((&common_cpy->someone_died_lock)) == ERROR)
	{
		free(common_cpy);
		return (false);
	}
	common_cpy->someone_died = false;
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
