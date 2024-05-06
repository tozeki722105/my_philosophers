/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/05/06 22:13:26 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_common init_common(int argc, char **argv)
{
	t_common common;

	common.someone_died = false;
	common.die_time = atoi(argv[2]); 
	common.eat_time = atoi(argv[3]); 
	common.sleep_time = atoi(argv[4]); 
	if (argc == 6)
		common.must_eat_count = atoi(argv[5]);
	else
		common.must_eat_count = NO_COUNT;
	return (common);
}

t_fork *init_forks(int philo_count)
{
	t_fork	*fork_array;
	int		*last_ead_id_array;
	int		i;

	fork_array = (t_fork *)malloc(philo_count * sizeof(t_fork));
	last_ead_id_array = make_last_ead_id_array(philo_count);
	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_init(&(fork_array[i].lock), NULL);
		fork_array[i].last_eat_id = last_ead_id_array[i];
		i++;
	}
	free(last_ead_id_array);
	return (fork_array);
}

t_philo *init_philos(int philo_count, t_common *common, t_fork *forks)
{
	t_philo		*philo_array;
	int			i;

	philo_array = (t_philo *)malloc(philo_count * sizeof(t_philo));
	i = 0;
	while (i < philo_count)
	{
		philo_array[i].common = common;
		philo_array[i].id = i;
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

void print_init(t_philo *philos, int philo_count)
{
	size_t i;

	i = 0;
	while (i < philo_count)
	{
		printf("philo_id=%d;\n", philos[i].id);
		printf("die_time=%d;\n", philos[i].common->die_time);
		printf("eat_time=%d;\n", philos[i].common->eat_time);
		printf("sleep_time=%d;\n", philos[i].common->sleep_time);
		printf("must_eat_count=%d;\n", philos[i].common->must_eat_count);
		printf("eat_count=%d;\n", philos[i].eat_count);
		printf("right_fork.last_eat_id=%d;\n", philos[i].right_fork->last_eat_id);
		printf("left_fork.last_eat_id=%d;\n", philos[i].left_fork->last_eat_id);
		printf("\n\n");
		i++;
	}
}

int main (int argc, char **argv)
{
	int			philo_count;
	t_common	common;
	t_fork		*forks;
	t_philo		*philos;
	
	if (!(argc == 5 || argc == 6))
		return (1);
	philo_count = atoi(argv[1]);
	common = init_common(argc, argv);
	forks = init_forks(philo_count);
	philos = init_philos(philo_count, &common, forks);
	print_init(philos, philo_count);
	// for (int i = 0; i < philo_count; i++)
	// 	pthread_create(&(philo[i]), NULL, func, (void *)i);
	// for (int i = 0; i < philo_count; i++)
	// 	pthread_join(&(philo[i]), NULL);
	free(forks);
	free(philos);
}