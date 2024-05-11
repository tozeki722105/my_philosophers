/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:49:10 by toshi             #+#    #+#             */
/*   Updated: 2024/05/11 02:49:21 by toshi            ###   ########.fr       */
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
#define NO_CATCHED		0
#define MILLISECONDS	1000
#define LEFT		0
#define RIGHT		1
#define SLEEP_BASE	10000


typedef struct s_common
{
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_count;
	pthread_mutex_t someone_died_lock;
	bool	someone_died;
	pthread_mutex_t end_philos_count_lock;
	int		end_philos_count;
	unsigned long	common_start;
} t_common;

typedef struct s_fork {
	pthread_mutex_t	lock;
	int	catched_id;
	int	last_eat_id;
} t_fork;

typedef struct s_philo
{
	t_common		*common;
	int				id;
	int				eat_count;
	unsigned long	last_eat_time;
	unsigned long	start;
	t_fork			*right_fork;
	t_fork			*left_fork;
} t_philo;

void		init_label(int *forks_array, int len);
int			*make_last_ead_id_array(int philo_count);

t_common	init_common(int argc, char **argv);
t_fork		*init_forks(int philo_count);
t_philo		*init_philos(int philo_count, t_common *common, t_fork *forks);
void	print_init(t_philo *philo);
void print_init_array(t_philo *philos, int philo_count);

unsigned long	get_time();
void	do_eat(t_philo *philo, t_common *common);
void	do_sleep(t_philo *philo, t_common *common);
void	catch_fork(t_fork *fork, t_common *common, t_philo *philo, int hand_flag);
void	release_fork(t_fork *fork, t_philo *philo);
void	eat_release_sleep(t_philo *philo, t_common *common);
bool	is_dead(t_philo *philo, t_common *common);

void	*terminate(t_common *common);
bool can_catch_fork(t_fork *fork, t_philo *philo);