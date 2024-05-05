/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:49:10 by toshi             #+#    #+#             */
/*   Updated: 2024/05/05 20:51:14 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define NO_COUNT	0
// #define PHILOS		4

// typedef struct s_table {
// 	int	die_time;
// 	int	eat_time;
// 	int	sleep_time;
// 	int	each_eat_count;
// 	pthread_mutex_t food_lock;
// 	pthread_mutex_t *fork_lock;
// 	int *forks;
// } t_table;

typedef struct s_common
{
	bool someone_died;
	int	die_time;
	int	eat_time;
	int	sleep_time;
} t_common;

typedef struct s_fork {
	pthread_mutex_t fork_lock;
	int last_eat_id;
} t_fork;

typedef struct s_philo
{
	int id;
	t_time *time;
	int	eat_count;
	t_fork *right_fork;
	t_fork *left_fork;
} t_philo;

void	init_label(int *forks_array, int len);
