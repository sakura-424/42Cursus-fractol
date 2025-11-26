/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya <skatsuya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:35:21 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/27 03:15:59 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int process_julia_pixel(t_vars *vars, int x, int y);
static int process_mandelbrot_pixel(t_vars *vars, int x, int y);

void calculate_fractol(t_vars *vars)
{
	int x;
	int y;
	int iter;

	iter = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (vars->type == MANDELBROT)
				iter = process_mandelbrot_pixel(vars, x, y);
			else if (vars->type == JULIA)
				iter = process_julia_pixel(vars, x, y);
			vars->iterations[y * WIDTH + x] = iter;
			x++;
		}
		y++;
	}
}

void render_fractol(t_vars *vars)
{
	int x;
	int y;
	int iter;
	int color;
	t_color rgb;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			iter = vars->iterations[y * WIDTH + x];
			if (iter == vars->max_iter)
				color = 0x000000;
			else
			{
				rgb.r = (iter * 5 + vars->color_shift) % 255;
				rgb.g = (iter * 5 + vars->color_shift + 80) % 255;
				rgb.b = (iter * 5 + vars->color_shift + 160) % 255;
                color = (rgb.r << 16) | (rgb.g << 8) | rgb.b;
			}
			put_color(vars, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

static int process_julia_pixel(t_vars *vars, int x, int y)
{
	t_complex z;
	double tmp_x;
	int iter;

	z.x = (((double)x / WIDTH) * 4.0 - 2.0) * vars->zoom + vars->shift_x;
	z.y = (((double)y / HEIGHT) * 4.0 - 2.0) * vars->zoom + vars->shift_y;
	iter = 0;
	while (z.x * z.x + z.y * z.y < 4.0 && iter < vars->max_iter)
	{
		tmp_x = z.x * z.x - z.y * z.y + vars->julia.x;
		z.y = 2.0 * z.x * z.y + vars->julia.y;
		z.x = tmp_x;
		iter++;
	}
	return (iter);
}

static int process_mandelbrot_pixel(t_vars *vars, int x, int y)
{
	t_complex z;
	t_complex c;
	double tmp_x;
	int iter;

	z.x = 0.0;
	z.y = 0.0;
	c.x = (((double)x / WIDTH) * 4.0 - 2.0) * vars->zoom + vars->shift_x;
	c.y = (((double)y / HEIGHT) * 4.0 - 2.0) * vars->zoom + vars->shift_y;
	iter = 0;
	c.q = (c.x - 0.25) * (c.x - 0.25) + c.y * c.y;
    if (c.q * (c.q + (c.x - 0.25)) < 0.25 * c.y * c.y)
        return (vars->max_iter);
    if ((c.x + 1.0) * (c.x + 1.0) + c.y * c.y < 0.0625)
        return (vars->max_iter);
	while (z.x * z.x + z.y * z.y < 4.0 && iter < vars->max_iter)
	{
		tmp_x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0 * z.x * z.y + c.y;
		z.x = tmp_x;
		iter++;
	}
	return (iter);
}
