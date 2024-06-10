/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:10:04 by tozeki            #+#    #+#             */
/*   Updated: 2024/06/10 16:38:13 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_null(t_common **common, t_fork **forks, t_philo **philos,
			pthread_t **threads)
{
	*common = NULL;
	*forks = NULL;
	*philos = NULL;
	*threads = NULL;
}

void	finalize(t_common *common, t_fork *forks, t_philo *philos,
			pthread_t *threads)
{
	if (threads)
		free(threads);
	if (philos)
		free(philos);
	if (forks)
	{
		destroy_forks_mutex(forks, common->philo_count);
		free(forks);
	}
	if (common)
	{
		pthread_mutex_destroy(&(common->lock));
		free(common);
	}
}

void	wait_threads(pthread_t *threads, t_common *common)
{
	while (!is_simulate_end(common))
	{
		pthread_mutex_lock(&(common->eat_up_lock));
		if (common->eat_up_count == common->philo_count)
		{
			pthread_mutex_lock(&(common->lock));
			common->simulation_run_flag = false;
			pthread_mutex_unlock(&(common->lock));
			pthread_mutex_unlock(&(common->eat_up_lock));
			break ;
		}
		pthread_mutex_unlock(&(common->eat_up_lock));
	}
	int	i;

	i = 0;
	while (i < common->created_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

static bool	is_num_only_str(char *str)
{
	if (*str == '\0')
	{
		print_err("Contains an empty string");
		return (false);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			print_err("Contains a non-numeric value");
			return (false);
		}
		str++;
	}
	return (true);
}

bool	validate_args(int argc, char **argv)
{
	int		i;

	if (!(argc == 5 || argc == 6))
	{
		print_err("Incorrect number of arguments");
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_num_only_str(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

// int main(int argc, char **argv)
// {
// 	if (!validate_args(argc, argv))
// 		printf("error\n");
// 	else
// 		printf("ok\n");
// }
