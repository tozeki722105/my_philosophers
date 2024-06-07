/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:49:10 by toshi             #+#    #+#             */
/*   Updated: 2024/05/20 00:30:52 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define FAIL_EXIT_STATUS		1
# define SUCCESS_EXIT_STATUS	0
# define NO_COUNT				-1
# define ERROR					-1
# define DEFAULT				2
# define DEAD_LINE				9
# define SUCCESS				0

typedef unsigned long	t_ms;

typedef struct s_common
{
	int				philo_count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_count;
	pthread_mutex_t	lock;
	bool			someone_died;
	int				start_flag;
	t_ms			start_time;
	int				created_count;
}	t_common;

typedef struct s_fork {
	pthread_mutex_t	lock;
	int				last_eat_id;
}	t_fork;

typedef struct s_philo
{
	t_common	*common;
	int			id;
	t_ms		last_eat_time;
	int			eat_count;
	t_fork		*right_fork;
	t_fork		*left_fork;
}	t_philo;

//main_utils.c
void	set_null(t_common **common, t_fork **forks, t_philo **philos, \
		pthread_t **threads);
void	finalize(t_common *common, t_fork *forks, t_philo *philos, \
		pthread_t *threads);
void	wait_threads(pthread_t *threads, t_common *common);
bool	validate_args(int argc, char **argv);
//initialize_common.c
bool	initialize_common(int argc, char **argv, t_common **common);
//initialize_philos.c
bool	initialize_philos(int philo_count, t_common *common, t_fork *forks, \
		t_philo **philo);
//initialize_threads_and_simulate.c
bool	initialize_threads_and_simulate(pthread_t **threads, \
		t_common *common, t_philo *philos);
//initialize_forks.c
bool	initialize_forks(int philo_count, t_fork **forks);
//simulate.c
void	*simulate(void *data);
bool	can_start(t_common *common);
void	think(t_philo *philo, t_common *common);
bool	is_eating_finished(t_philo *philo, t_common *common);
//simulate_utils.c
void	msleep(int ms_time, t_philo *philo, t_common *common);
bool	is_dead(t_philo *philo, t_common *common);
bool	is_someone_dead(t_common *common);
bool	can_take_pair_forks(t_philo *philo);
//simulate_utils2.c
void	take_eat_release_sleep(t_philo *philo, t_common *common);
//utils_libft.c
void	ft_putendl(char *s, int fd);
int		ft_isdigit(int c);
//utils.c
t_ms	get_time(void);
void	print_err(char *s);
void	*malloc_wrap(size_t size);
int		mutex_init_wrap(pthread_mutex_t *mutex);
int		pthread_create_wrap(pthread_t *thread, void *(*routine)(void *), \
		void *arg);
//utils2.c
void	destroy_forks_mutex(t_fork *forks, int count);

#endif