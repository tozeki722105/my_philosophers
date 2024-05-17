/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:39:40 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 14:10:51 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static bool	is_num_only_str(char *str)
{
	if (*str == '\0')
	{
		print_err("Contains an empty string");
		return (false);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			print_err("Contains a non-numeric value");
			return (false);
		}
		str++;
	}
	return (true);
}

bool	validate_args(int argc, char **argv)
{
	size_t i;

	if (!(argc == 5 || argc == 6))
	{
		print_err("Incorrect number of arguments");
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