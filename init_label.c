/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:55:05 by toshi             #+#    #+#             */
/*   Updated: 2024/05/05 17:50:39 by toshi            ###   ########.fr       */
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
	if (len == 2)
	{
		forks_array[0] = 2;
		forks_array[1] = 2;
		return ;
	}
	int i = 0;
	int num = 2;
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

// #include "stdio.h"
// #include "stdlib.h"
// int main(int argc, char **argv)
// {
// 	// printf("aaa\n");
// 	int len = atoi(argv[1]);
// 	// int len = atoi("10");
// 	int *forks_array = (int *)calloc(len, sizeof(int));
// 	init_label(forks_array, len);
// 	int i = 0;
// 	while (i < len)
// 	{
// 		printf("%d=%d;\n", i, forks_array[i]);
// 		i++;
// 	}
// }