/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:55:05 by toshi             #+#    #+#             */
/*   Updated: 2024/05/06 20:27:04 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_label(int *forks_array, int len)
{
	if (len == 1)
	{
		forks_array[0] = 0;
		return ;
	}
	int i = 0;
	int num = 1;
	if (len == 2)
	{
		forks_array[0] = num;
		forks_array[1] = num;
		return ;
	}
	if (len % 2 != 0)
	{
		while (i + 3 < len)
		{
			forks_array[i] = num;
			forks_array[i + 1] = num;
			num += 2;
			i += 2;
		}
		forks_array[i++] = num++;
		forks_array[i++] = num;
		forks_array[i] = num;
		return ;
	}
	while (i < len)
	{
		forks_array[i] = num;
		forks_array[i + 1] = num;
		num += 2;
		i += 2;
	}
	return ;
}

int *make_last_ead_id_array(int philo_count)
{
	int *array;

	array = (int *)malloc(philo_count * sizeof(int));
	init_label(array, philo_count);
	return (array);
}

// #include "stdio.h"
// #include "stdlib.h"
// int main(int argc, char **argv)
// {
// 	if (argc == 1)
// 	{
// 		printf("error\n");
// 		return ;
// 	}
// 	int len = atoi(argv[1]);
// 	int *forks_array = (int *)calloc(len, sizeof(int));
// 	init_label(forks_array, len);
// 	int i = 0;
// 	while (i < len)
// 	{
// 		printf("%d=%d;\n", i, forks_array[i]);
// 		i++;
// 	}
// }