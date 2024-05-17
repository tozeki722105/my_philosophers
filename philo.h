/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:49:10 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 13:03:59 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

#define NO_COUNT			-1
#define ERROR				-1
#define FAIL_EXIT_STATUS	1
#define SUCCESS_EXIT_STATUS	0
#define DEAD_LINE			9
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

//init.c
bool	initialize_forks(int philo_count, t_fork **forks);
bool	initialize_common(int argc, char **argv, t_common **common);
bool	initialize_philos(int philo_count, t_common *common, t_fork *forks, t_philo **philo);
//simulation_utils.c
bool	is_dead(t_philo *philo, t_common *common);
bool	can_take_pair_forks(t_philo *philo);
bool	is_finished_eating(t_philo *philo, t_common *common);
void	msleep(int ms_time, t_philo *philo, t_common *common);
bool	is_someone_dead(t_common *common);
void	think(t_philo *philo, t_common *common);
void	take_eat_release_sleep(t_philo *philo, t_common *common);
//simulation.c
void	*simulation(void *data);
//utils_libft.c
size_t	ft_strlen(const char *s);
void	ft_putendl(char *s, int fd);
int		ph_atoi(const char *str);
//utils.c
t_ms	get_time();
void	print_err(char *s);
void	*malloc_wrap(size_t size);
int		mutex_init_wrap(pthread_mutex_t *mutex);
void	destroy_forks_mutex(t_fork *forks, int count);
//validate_args.c
bool	validate_args(int argc, char **argv);
