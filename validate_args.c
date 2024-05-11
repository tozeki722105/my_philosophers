/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:39:40 by toshi             #+#    #+#             */
/*   Updated: 2024/05/11 20:05:19 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

bool	is_num_only_str(char *str)
{
	size_t len;

	if (*str == '\0')
		return (false);
	len = ft_strlen(str);
	while (*str)
	{
		if (ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	validate_args(int argc, char **argv)
{
	size_t i;

	if (!(argc == 5 || argc == 6))
		return (false);
	i = 0;
	while (i + 1 < argc)
	{
		if (!is_num_only_str(argv[i]))
			return (false);
		i++;
	}
	return (true);
}