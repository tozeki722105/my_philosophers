/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:49:10 by toshi             #+#    #+#             */
/*   Updated: 2024/05/12 03:42:07 by toshi            ###   ########.fr       */
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

#define NO_COUNT	0
#define RIGHT		1
#define LEFT		0

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
	int	last_eat_id;
} t_fork;

typedef struct s_share {
	pthread_mutex_t lock;
	int				val;
} t_share;

typedef struct s_philo
{
	t_common		*common;
	int				id;
	int				eat_count;
	unsigned long	last_eat_time;
	t_fork			*right_fork;
	t_fork			*left_fork;
} t_philo;

//simulation.c
void *func(void *data);
//simulation_utils.c
void catch_eat_release_sleep(t_philo *philo, t_common *common);
// init.c
t_common init_common(int argc, char **argv);
t_fork *init_forks(int philo_count);
t_philo *init_philos(int philo_count, t_common *common, t_fork *forks);
int *make_last_ead_id_array(int philo_count);
//utils.c
void	usleep_wrap(unsigned long mili_time);
unsigned long	get_time();
bool	is_dead(t_philo *philo, t_common *common);
bool	is_someone_dead(t_common *common);
//utils_libft.c
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
//validate_args.c
bool	validate_args(int argc, char **argv);