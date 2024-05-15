/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:57:17 by toshi             #+#    #+#             */
/*   Updated: 2024/05/15 19:06:36 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_null(t_common **common, t_fork **forks, t_philo **philos, pthread_t **threads)
{
	*common = NULL;
	*forks = NULL;
	*philos = NULL;
	*threads = NULL;
}

void	finalize(t_common *common, t_fork *forks, t_philo *philos, pthread_t *threads)
{
	int i;
	
	if (common)
	{
		pthread_mutex_destroy(&(common->someone_died_lock));
		free(common);
	}
	if (forks)
	{
		i = 0;
		while (i < common->philo_count)
		{
			pthread_mutex_destroy(&(forks[i].lock));
			i++;
		}
		free(forks);
	}
	if (philos)
		free(philos);
	if (threads)
		free(threads);
}

static t_philo	*initialize_philos(int philo_count, t_common *common, t_fork *forks)
{
	t_philo		*philo_array;
	int			i;

	philo_array = (t_philo *)malloc(philo_count * sizeof(t_philo));
	if (!philo_array)
		return (NULL);
	i = 0;
	while (i < philo_count)
	{
		philo_array[i].common = common;
		philo_array[i].id = i + 1;
		philo_array[i].start_time = 0;
		philo_array[i].last_eat_time = 0;
		philo_array[i].eat_count = 0;
		if (i == 0)
			philo_array[i].right_fork = &(forks[philo_count - 1]);
		else
			philo_array[i].right_fork = &(forks[i - 1]);
		philo_array[i].left_fork = &(forks[i]);
		i++;
	}
	return (philo_array);
}

// memset(forks_cpy, '0', philo_count * sizeof(t_fork));
static bool	initialize_forks(int philo_count, t_fork **forks)
{
	t_fork	*forks_cpy;
	int		*last_eat_id_array;
	int		i;

	forks_cpy = (t_fork *)malloc(philo_count * sizeof(t_fork));
	if (!forks_cpy)
		return (false);
	*forks = forks_cpy;
	last_eat_id_array = make_last_ead_id_array(philo_count);
	if (!last_eat_id_array)
		return (false);
	i = 0;
	while (i < philo_count \
		&& pthread_mutex_init(&(forks_cpy[i].lock), NULL) != ERROR)
	{
		forks_cpy[i].last_eat_id = last_eat_id_array[i];
		i++;
	}
	free(last_eat_id_array);
	if (i < philo_count)
		return (false);
	return (true);
}

static bool	is_arg_overflow(t_common common, int argc)
{
	if (common.philo_count == ERROR || common.die_time == ERROR \
		|| common.eat_time == ERROR || common.sleep_time == ERROR \
		|| (argc == 6 && common.must_eat_count == ERROR))
	{
		ft_putendl_fd("argv is int_overflow", STDERR_FILENO);
		return (true);
	}
	return (false);
}

static bool	initialize_common(int argc, char **argv, t_common **common)
{
	t_common *common_cpy;

	common_cpy = (t_common *)malloc(sizeof(t_common));
	if (!common_cpy)
		return (false);
	*common = common_cpy;
	common_cpy->philo_count = atoi(argv[1]);
	common_cpy->die_time = atoi(argv[2]);
	common_cpy->eat_time = atoi(argv[3]);
	common_cpy->sleep_time = atoi(argv[4]);
	if (argc == 6)
		common_cpy->must_eat_count = atoi(argv[5]);
	else
		common_cpy->must_eat_count = NO_COUNT;
	if (is_arg_overflow(*common_cpy, argc) \
		|| pthread_mutex_init((&common_cpy->someone_died_lock), NULL) == ERROR)
		return (false);
	common_cpy->someone_died = false;
	common_cpy->common_start = 0;
	return (true);
}

t_philo	*initialize(int argc, char **argv, t_common **common, t_fork **forks)
{
	t_philo *philos;

	if (!validate_args(argc, argv))
		return (NULL);
	if (!initialize_common(argc, argv, common))
	{
		finalize(*common, NULL, NULL, NULL);
		return (NULL);
	}
	if (!initialize_forks((*common)->philo_count, forks))
	{
		finalize(*common, *forks, NULL, NULL);
		return (NULL);
	}
	philos = initialize_philos((*common)->philo_count, *common, *forks);
	if (!philos)
	{
		finalize(*common, *forks, philos, NULL);
		return (NULL);
	}
	return (philos);
}



// void	print_init(t_philo *philo)
// {
// 	printf("philo_id=%d;\n", philo->id);
// 	printf("die_time=%d;\n", philo->common->die_time);
// 	printf("eat_time=%d;\n", philo->common->eat_time);
// 	printf("sleep_time=%d;\n", philo->common->sleep_time);
// 	printf("must_eat_count=%d;\n", philo->common->must_eat_count);
// 	printf("eat_count=%d;\n", philo->eat_count);
// 	printf("right_fork.last_eat_id=%d;\n", philo->right_fork->last_eat_id);
// 	printf("left_fork.last_eat_id=%d;\n", philo->left_fork->last_eat_id);
// 	printf("\n\n");
// }

// void print_init_array(t_philo *philos, int philo_count)
// {
// 	size_t i;

// 	i = 0;
// 	while (i < philo_count)
// 	{
// 		print_init(&(philos[i]));
// 		i++;
// 	}
// }



// t_common init_common(int argc, char **argv)
// {
// 	t_common common;

// 	common.die_time = atoi(argv[2]);
// 	common.eat_time = atoi(argv[3]);
// 	common.sleep_time = atoi(argv[4]);
// 	if (argc == 6)
// 		common.must_eat_count = atoi(argv[5]);
// 	else
// 		common.must_eat_count = NO_COUNT;
// 	// if (is_arg_overflow())
// 	pthread_mutex_init((&common.someone_died_lock), NULL);
// 	common.someone_died = false;
// 	common.common_start = 0;
// 	return (common);
// }

// void destroy_mutexs(t_fork *forks_cpy, int count)
// {
// 	int i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		pthread_mutex_destroy(&(forks_cpy[i].lock));
// 		i++;
// 	}
// }

// bool	init_forks(int philo_count, t_fork **forks)
// {
// 	t_fork	*forks_cpy;
// 	int		*last_eat_id_array;
// 	int		i;

// 	forks_cpy = (t_fork *)malloc(philo_count * sizeof(t_fork));
// 	last_eat_id_array = make_last_ead_id_array(philo_count);
// 	i = 0;
// 	while (i < philo_count)
// 	{
// 		pthread_mutex_init(&(forks_cpy[i].lock), NULL);
// 		forks_cpy[i].last_eat_id = last_eat_id_array[i];
// 		i++;
// 	}
// 	free(last_eat_id_array);
// 	*forks = forks_cpy;
// 	return (true);
// }

// t_philo *init_philos(int philo_count, t_common *common, t_fork *forks)
// {
// 	t_philo		*philo_array;
// 	int			i;

// 	philo_array = (t_philo *)malloc(philo_count * sizeof(t_philo));
// 	i = 0;
// 	while (i < philo_count)
// 	{
// 		philo_array[i].common = common;
// 		philo_array[i].id = i + 1;
// 		philo_array[i].eat_count = 0;
// 		philo_array[i].last_eat_time = 0;
// 		if (i == 0)
// 			philo_array[i].right_fork = &(forks[philo_count - 1]);
// 		else
// 			philo_array[i].right_fork = &(forks[i - 1]);
// 		philo_array[i].left_fork = &(forks[i]);
// 		i++;
// 	}
// 	return (philo_array);
// }