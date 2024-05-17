//t_philo	*initialize(int argc, char **argv, t_common **common, t_fork **forks)
//{
//	t_philo *philos;

//	//if (!validate_args(argc, argv))
//	//	return (NULL);
//	if (!initialize_common(argc, argv, common))
//	{
//		//finalize(*common, NULL, NULL, NULL);
//		return (NULL);
//	}
//	if (!initialize_forks((*common)->philo_count, forks))
//	{
//		//finalize(*common, *forks, NULL, NULL);
//		return (NULL);
//	}
//	philos = initialize_philos((*common)->philo_count, *common, *forks);
//	if (!philos)
//	{
//		//finalize(*common, *forks, philos, NULL);
//		return (NULL);
//	}
//	return (philos);
//}



// void	print_init(t_philo *philo)
// {
// 	printf("philo_id=%d;\n", philo->id);
// 	printf("die_time=%d;\n", philo->common->die_time);
// 	printf("eat_time=%d;\n", philo->common->eat_time);
// 	printf("sleep_time=%d;\n", philo->common->sleep_time);
// 	printf("must_eat_count=%d;\n", philo->common->must_eat_count);
// 	printf("eat_count=%d;\n", philo->eat_count);
// 	printf("right_fork.last_eat_id=%d;\n", philo->right_fork->last_eat_id);
// 	printf("left_fork.last_eat_id=%d;\n", philo->left_fork->last_eat_id);
// 	printf("\n\n");
// }

// void print_init_array(t_philo *philos, int philo_count)
// {
// 	size_t i;

// 	i = 0;
// 	while (i < philo_count)
// 	{
// 		print_init(&(philos[i]));
// 		i++;
// 	}
// }



// t_common init_common(int argc, char **argv)
// {
// 	t_common common;

// 	common.die_time = atoi(argv[2]);
// 	common.eat_time = atoi(argv[3]);
// 	common.sleep_time = atoi(argv[4]);
// 	if (argc == 6)
// 		common.must_eat_count = atoi(argv[5]);
// 	else
// 		common.must_eat_count = NO_COUNT;
// 	// if (is_arg_overflow())
// 	pthread_mutex_init((&common.lock), NULL);
// 	common.someone_died = false;
// 	common.start_time = 0;
// 	return (common);
// }



// bool	init_forks(int philo_count, t_fork **forks)
// {
// 	t_fork	*forks_cpy;
// 	int		*last_eat_id_array;
// 	int		i;

// 	forks_cpy = (t_fork *)malloc(philo_count * sizeof(t_fork));
// 	last_eat_id_array = make_last_eat_id_array(philo_count);
// 	i = 0;
// 	while (i < philo_count)
// 	{
// 		pthread_mutex_init(&(forks_cpy[i].lock), NULL);
// 		forks_cpy[i].last_eat_id = last_eat_id_array[i];
// 		i++;
// 	}
// 	free(last_eat_id_array);
// 	*forks = forks_cpy;
// 	return (true);
// }

// t_philo *init_philos(int philo_count, t_common *common, t_fork *forks)
// {
// 	t_philo		*philo_array;
// 	int			i;

// 	philo_array = (t_philo *)malloc(philo_count * sizeof(t_philo));
// 	i = 0;
// 	while (i < philo_count)
// 	{
// 		philo_array[i].common = common;
// 		philo_array[i].id = i + 1;
// 		philo_array[i].eat_count = 0;
// 		philo_array[i].last_eat_time = 0;
// 		if (i == 0)
// 			philo_array[i].right_fork = &(forks[philo_count - 1]);
// 		else
// 			philo_array[i].right_fork = &(forks[i - 1]);
// 		philo_array[i].left_fork = &(forks[i]);
// 		i++;
// 	}
// 	return (philo_array);
// }



// // forkのlast_eat_idとphilo->idが違う かつ catched_id が NO_CATCHEDのとき
// // 後半の条件文は今のアルゴリズムではいらない？？
// bool can_take_fork(t_fork *fork, t_philo *philo)
// {
// 	bool ret;

// 	pthread_mutex_lock(&(fork->lock));
// 	ret = (fork->last_eat_id != philo->id);
// 	pthread_mutex_unlock(&(fork->lock));
// 	return (ret);
// }

// void	take_fork(t_fork *fork, t_common *common, t_philo *philo, int hand_flag)
// {
// 	if (hand_flag == RIGHT)
// 		printf("%10lu %d has taken a right\n", get_time() - common->start_time, philo->id);
// 	else if (hand_flag == LEFT)
// 		printf("%10lu %d has taken a left\n", get_time() - common->start_time, philo->id);
// }

// void	do_eat(t_philo *philo, t_common *common)
// {
// 	philo->last_eat_time = get_time();
// 	printf("%10lu %d is eating\n", philo->last_eat_time - common->start_time, philo->id);
//  	msleep(common->eat_time);
// 	philo->eat_count++;
// }
// void	release_fork(t_fork *fork, t_philo *philo)
// {
// 	pthread_mutex_lock(&(fork->lock));
// 	fork->last_eat_id = philo->id;
// 	pthread_mutex_unlock(&(fork->lock));
// }

// // TODO mutexして、someone_diedを確認し、trueだったら出力しない
// void	do_sleep(t_philo *philo, t_common *common)
// {
// 	printf("%10lu %d is sleeping\n", get_time() - common->start_time, philo->id);
// 	msleep(common->sleep_time);
// }