/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:12:30 by toshi             #+#    #+#             */
/*   Updated: 2024/05/05 19:38:19 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	init(int argc, char **argv, int philo_num)
{
	t_table	table;

	table.die_time = atoi(argv[2]);
	table.eat_time = atoi(argv[3]);
	table.sleep_time = atoi(argv[4]);
	if (argc == 6)
		table.each_eat_count = atoi(argv[5]);
	else
		table.each_eat_count = NO_COUNT;
	pthread_mutex_init(&(table.food_lock), NULL);
	table.fork_lock = (pthread_mutex_t *)malloc(philo_num * sizeof(pthread_mutex_t));
	for (int i = 0; i < philo_num; i++)
		pthread_mutex_init(&(table.fork_lock[i]), NULL);
	table.forks = (int *)malloc(philo_num * sizeof(int));
	init_label(table.forks, philo_num);
	return (table);
}

void print_init(t_table table, int philo_num)
{
	printf("die_time=%d;\n", table.die_time);
	printf("eat_time=%d;\n", table.eat_time);
	printf("sleep_time=%d;\n", table.sleep_time);
	printf("each_eat_count=%d;\n", table.each_eat_count);
	for (int i = 0; i < philo_num; i++)
		printf("%d=%d;\n", i, table.forks[i]);
}

int main (int argc, char **argv)
{
	t_table		table;
	int			philo_num;
	pthread_t	*philo;
	
	if (!(argc == 5 || argc == 6))
		return (1);
	philo_num = atoi(argv[1]);
	table = init(argc, argv, philo_num);
	philo = (pthread_t *)malloc(philo_num * sizeof(pthread_t));
	for (int i = 0; i < philo_num; i++)
		pthread_create(&(philo[i]), NULL, func, (void *)i);
	for (int i = 0; i < philo_num; i++)
		pthread_join(&(philo[i]), NULL);
}