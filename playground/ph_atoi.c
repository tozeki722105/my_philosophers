/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:20:52 by tozeki            #+#    #+#             */
/*   Updated: 2024/06/11 20:12:48 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

// 数値だけの文字列限定、自然数限定のatoi
// 数字以外を含んだ文字列(+/-含む)は事前にハジく必要あり
int		atoi_natural(const char *str)
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

 int main(int argc, char **argv)
 {
 	if (argc < 2)
 		return (1);
 	printf("%d\n", atoi_natural(argv[1]));
 }