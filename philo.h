/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:49:10 by toshi             #+#    #+#             */
/*   Updated: 2024/05/15 20:07:34 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define NO_COUNT	-1
#define ERROR		-1
#define RIGHT		1
#define LEFT		0

typedef	unsigned long t_ms;

typedef struct s_common
{
	int				philo_count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_count;
	pthread_mutex_t	someone_died_lock;
	bool			someone_died;
	t_ms			common_start;
} t_common;

typedef struct s_fork {
	pthread_mutex_t	lock;
	int				last_eat_id;
} t_fork;

typedef struct s_philo
{
	t_common	*common;
	int			id;
	t_ms		start_time;
	t_ms		last_eat_time;
	int			eat_count;
	t_fork		*right_fork;
	t_fork		*left_fork;
} t_philo;

//simulation.c
void	*simulation(void *data);
//simulation_utils.c
bool	is_dead(t_philo *philo, t_common *common);
bool	can_take_pair_forks(t_philo *philo);
bool	is_finished_eating(t_philo *philo, t_common *common);
void	usleep_wrap(int ms_time);
bool	is_someone_dead(t_common *common);
t_ms	get_time();
void	think(t_philo *philo, t_common *common);
void	take_eat_release_sleep(t_philo *philo, t_common *common);
// init.c
t_philo	*initialize(int argc, char **argv, t_common **common, t_fork **forks);
int *make_last_ead_id_array(int philo_count);
//validate_args.c
bool	validate_args(int argc, char **argv);
//utils.c
//utils_libft.c
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ph_atoi(const char *str);

void	fill_null(t_common **common, t_fork **forks, t_philo **philos, pthread_t **threads);

void	finalize(t_common *common, t_fork *forks, t_philo *philos, pthread_t *threads);

bool	initialize_philos(int philo_count, t_common *common, t_fork *forks, t_philo **philo);
bool	initialize_forks(int philo_count, t_fork **forks);
bool	initialize_common(int argc, char **argv, t_common **common);
