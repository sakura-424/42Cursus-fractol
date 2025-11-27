/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:43:56 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/27 23:09:45 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_color(t_vars *vars, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * WIDTH + x) * 4;
	*(int *)(vars->addr + offset) = color;
}

int	get_color(int iter, t_vars *vars)
{
	t_color	rgb;

	if (iter == vars->max_iter)
		return (BLACK);
	rgb.r = (iter * 5 + vars->color_shift % 255);
	rgb.g = (iter * 5 + vars->color_shift + 80) % 255;
	rgb.b = (iter * 5 + vars->color_shift + 160) % 255;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
