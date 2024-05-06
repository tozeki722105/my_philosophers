/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/05/07 00:37:52 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *func(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// pthread_mutex_lock(&(philo->common->test));
	// print_init(philo);
	// pthread_mutex_unlock(&(philo->common->test));
	while (philo->eat_count < philo->common->must_eat_count && !philo->common->someone_died)
	{
		if (philo->left_fork->last_eat_id != philo->id && philo->left_fork->catched == -1)
		{
			pthread_mutex_lock(&(philo->left_fork->lock));
			printf("philo_id=%d catched left\n", philo->id);
			philo->left_fork->catched = philo->id;
			pthread_mutex_unlock(&(philo->left_fork->lock));
		}
		if (philo->right_fork->last_eat_id != philo->id && philo->right_fork->catched == -1)
		{
			pthread_mutex_lock(&(philo->right_fork->lock));
			printf("philo_id=%d catched right\n", philo->id);
			philo->right_fork->catched = philo->id;
			pthread_mutex_unlock(&(philo->right_fork->lock));
		}
		if (philo->right_fork->catched == philo->id && philo->left_fork->catched == philo->id)
		{
			pthread_mutex_lock(&(philo->left_fork->lock));
			pthread_mutex_lock(&(philo->right_fork->lock));
			printf("philo_id=%d eat\n", philo->id);
			philo->left_fork->catched = -1;
			philo->left_fork->last_eat_id = philo->id;
			philo->right_fork->catched = -1;
			philo->right_fork->last_eat_id = philo->id;
			philo->eat_count++;
			pthread_mutex_unlock(&(philo->left_fork->lock));
			pthread_mutex_unlock(&(philo->right_fork->lock));
		}
	}
	return (arg);
}

int main (int argc, char **argv)
{
	int			philo_count;
	t_common	common;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	*threads;
	int		i;
	
	if (!(argc == 5 || argc == 6))
		return (1);
	philo_count = atoi(argv[1]);
	common = init_common(argc, argv);
	forks = init_forks(philo_count);
	philos = init_philos(philo_count, &common, forks);
	threads = (pthread_t *)malloc(philo_count * sizeof(pthread_t));
	i = 0;
	while (i < philo_count)
	{
		pthread_create(&(threads[i]), NULL, func, (void *)&(philos[i]));
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	free(forks);
	free(philos);
}