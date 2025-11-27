/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:35:21 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/27 20:47:06 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	process_julia_pixcel(t_vars *vars, int x, int y);
static void	process_mandelbrot_pixcel(t_vars *vars, int x, int y);

void	draw_fractol(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (vars->type == MANDELBROT)
				process_mandelbrot_pixcel(vars, x, y);
			else if (vars->type == JULIA)
				process_julia_pixcel(vars, x, y);
			x++;
		}
		y++;
	}
}

static void	process_julia_pixcel(t_vars *vars, int x, int y)
{
	t_complex	z;
	double		tmp_x;
	int			iter;

	z.x = (((double)x / WIDTH) * 4.0 - 2.0) * vars->zoom + vars->shift_x;
	z.y = (((double)y / HEIGHT) * 4.0 - 2.0) * vars->zoom + vars->shift_y;
	iter = 0;
	while (z.x * z.x + z.y * z.y < 4.0 && iter < MAX_ITER)
	{
		tmp_x = z.x * z.x - z.y * z.y + vars->julia.x;
		z.y = 2.0 * z.x * z.y + vars->julia.y;
		z.x = tmp_x;
		iter++;
	}
	if (iter == MAX_ITER)
		put_color(vars, x, y, 0x000000);
	else
		put_color(vars, x, y, (int)(z.x * z.x * z.y * z.y * 20) << 16);
}

static void	process_mandelbrot_pixcel(t_vars *vars, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		tmp_x;
	int			iter;

	z.x = 0.0;
	z.y = 0.0;
	c.x = (((double)x / WIDTH) * 4.0 - 2.0) * vars->zoom + vars->shift_x;
	c.y = (((double)y / HEIGHT) * 4.0 - 2.0) * vars->zoom + vars->shift_y;
	iter = 0;
	while (z.x * z.x + z.y * z.y < 4.0 && iter < MAX_ITER)
	{
		tmp_x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0 * z.x * z.y + c.y;
		z.x = tmp_x;
		iter++;
	}
	if (iter == MAX_ITER)
		put_color(vars, x, y, 0x000000);
	else
		put_color(vars, x, y, (int)(z.x * z.x * z.y * z.y * 20) << 16);
}
