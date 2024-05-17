/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:54:57 by toshi             #+#    #+#             */
/*   Updated: 2024/05/17 14:12:53 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putendl(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

// 数値だけの文字列限定、自然数限定のatoi
// 数字以外を含んだ文字列(+/-含む)は事前にハジく必要あり
int		atoi_for_natural(const char *str)
{
	int	num;

	num = 0;
	while (*str)
	{	
		if (num > (INT_MAX / 10)
			|| (num == (INT_MAX / 10) && (*str - '0') > (INT_MAX % 10)))
			return (-1);
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}

// int main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (1);
// 	printf("%d\n", atoi_for_natural(argv[1]));
// }
