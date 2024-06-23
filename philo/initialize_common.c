/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_common.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 00:21:47 by toshi             #+#    #+#             */
/*   Updated: 2024/06/24 04:11:03 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_arg_overflow(t_common common, int argc)
{
	if (common.philo_count == ERROR
		|| common.die_time == ERROR
		|| common.eat_time == ERROR
		|| common.sleep_time == ERROR
		|| (argc == 6 && common.must_eat_count == ERROR))
	{
		put_err("There is an argument for int_overflow");
		return (true);
	}
	return (false);
}

// 数値だけの文字列限定、自然数限定のatoi
// 数字以外を含んだ文字列(+/-含む)は事前にハジく必要あり
static int	atoi_natural(const char *str)
{
	int	num;

	num = 0;
	while (*str)
	{	
		if (num > (INT_MAX / 10)
			|| (num == (INT_MAX / 10) && (*str - '0') > (INT_MAX % 10)))
			return (ERROR);
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}

// common.created_threads_count/common.start_timeは
// initialize_threads_and_simulate()で初期化される
bool	initialize_common(int argc, char **argv, t_common **common)
{
	t_common	*common_cpy;

	common_cpy = (t_common *)malloc_wrap(sizeof(t_common));
	if (!common_cpy)
		return (false);
	common_cpy->philo_count = atoi_natural(argv[1]);
	common_cpy->die_time = atoi_natural(argv[2]);
	common_cpy->eat_time = atoi_natural(argv[3]);
	common_cpy->sleep_time = atoi_natural(argv[4]);
	if (argc == 6)
		common_cpy->must_eat_count = atoi_natural(argv[5]);
	else
		common_cpy->must_eat_count = NO_COUNT;
	if (is_arg_overflow(*common_cpy, argc)
		|| mutex_init_wrap(&(common_cpy->lock)) != SUCCESS)
	{
		free(common_cpy);
		return (false);
	}
	common_cpy->simulation_run_flag = DEFAULT;
	common_cpy->eat_up_count = 0;
	*common = common_cpy;
	return (true);
}
