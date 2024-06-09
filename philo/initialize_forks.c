/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_forks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:06:38 by tozeki            #+#    #+#             */
/*   Updated: 2024/06/09 19:02:53 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 長さが奇数のlast_eat_id_arrayに値を入れる 
 * 長さが5 2,2,4,5,5
 * 長さが7 2,2,4,4,6,7,7 
 * 長さが9 2,2,4,4,6,6,8,9,9
 * @param array setする配列
 * @param len 配列の長さ
 */
static void	set_num_in_odd_pattern(int *array, int len)
{
	int	i;
	int	num;

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

/**
 * @brief 長さが偶数のlast_eat_id_arrayに値を入れる 
 * 長さが4 2,2,4,4
 * 長さが6 2,2,4,4,6,6
 * 長さが8 2,2,4,4,6,6,8,8
 * @param array setする配列
 * @param len 配列の長さ
 */
static void	set_num_in_even_pattern(int *array, int len)
{
	int	i;
	int	num;

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

static int	*make_last_eat_id_array(int philo_count)
{
	int	*array;

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

static int	set_fork_data(int philo_count, t_fork *forks_cpy,
			int *last_eat_id_array)
{
	int	i;

	i = 0;
	while (i < philo_count
		&& mutex_init_wrap(&(forks_cpy[i].lock)) == SUCCESS)
	{
		forks_cpy[i].last_eat_id = last_eat_id_array[i];
		i++;
	}
	return (i);
}

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
