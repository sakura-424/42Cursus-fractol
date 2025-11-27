/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 05:16:11 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/27 22:47:27 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	get_decimal(char *str);

double	ft_atof(char *str)
{
	int		i;
	int		sign;
	double	result;

	i = 0;
	sign = 1.0;
	result = 0.0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		result = result + get_decimal(&str[i + 1]);
	return (result * sign);
}

static double	get_decimal(char *str)
{
	int		i;
	double	result;
	double	div;

	i = 0;
	result = 0.0;
	div = 1.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		div = div * 10.0;
		result = result + (str[i] - '0') / div;
		i++;
	}
	return (result);
}
