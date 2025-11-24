/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya <skatsuya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:14:12 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/25 05:37:19 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void print_help(void)
{
	ft_putstr_fd("1. Usage : ./fractol mandelbrot\n", 1);
	ft_putstr_fd("2. Usage: ./fractol julia <real> <imaginary>\n", 1);
}
