/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:49:10 by toshi             #+#    #+#             */
/*   Updated: 2024/05/07 16:49:40 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

#define NO_COUNT	0

typedef struct s_common
{
	pthread_mutex_t test;
	bool	someone_died;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_count;
} t_common;

typedef struct s_fork {
	pthread_mutex_t	lock;
	int 			catched;
	int				last_eat_id;
} t_fork;

typedef struct s_philo
{
	t_common	*common;
	int			id;
	int			eat_count;
	t_fork		*right_fork;
	t_fork		*left_fork;
} t_philo;

void		init_label(int *forks_array, int len);
int			*make_last_ead_id_array(int philo_count);

t_common	init_common(int argc, char **argv);
t_fork		*init_forks(int philo_count);
t_philo		*init_philos(int philo_count, t_common *common, t_fork *forks);
void	print_init(t_philo *philo);
void print_init_array(t_philo *philos, int philo_count);
