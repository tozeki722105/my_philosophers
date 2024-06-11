/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:10:04 by tozeki            #+#    #+#             */
/*   Updated: 2024/06/11 20:35:04 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_num_only_str(char *str)
{
	if (*str == '\0')
	{
		put_err("Contains an empty string");
		return (false);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			put_err("Contains a non-numeric value");
			return (false);
		}
		str++;
	}
	return (true);
}

bool	validate_args(int argc, char **argv)
{
	int		i;

	if (!(argc == 5 || argc == 6))
	{
		put_err("Incorrect number of arguments");
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_num_only_str(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

// int main(int argc, char **argv)
// {
// 	if (!validate_args(argc, argv))
// 		printf("error\n");
// 	else
// 		printf("ok\n");
// }
