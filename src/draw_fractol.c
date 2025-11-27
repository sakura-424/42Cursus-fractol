/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:35:21 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/27 23:12:20 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			process_julia_pixel(t_vars *vars, int x, int y);
static int			process_mandelbrot_pixel(t_vars *vars, int x, int y);
static t_complex	map_point(int x, int y, t_vars *vars);

void	calculate_fractol(t_vars *vars)
{
	int	x;
	int	y;
	int	iter;

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

void	render_fractol(t_vars *vars)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = get_color(vars->iterations[y * WIDTH + x], vars);
			put_color(vars, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

static int	process_julia_pixel(t_vars *vars, int x, int y)
{
	t_complex	z;
	double		tmp_x;
	int			iter;

	z = map_point(x, y, vars);
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

static int	process_mandelbrot_pixel(t_vars *vars, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		q;
	double		tmp_x;
	int			iter;

	z.x = 0.0;
	z.y = 0.0;
	c = map_point(x, y, vars);
	iter = 0;
	q = (c.x - 0.25) * (c.x - 0.25) + c.y * c.y;
	if (q * (q + (c.x - 0.25)) < 0.25 * c.y * c.y)
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

static t_complex	map_point(int x, int y, t_vars *vars)
{
	t_complex	p;

	p.x = (((double)x / WIDTH) * 4.0 - 2.0) * vars->zoom + vars->shift_x;
	p.y = (((double)y / HEIGHT) * 4.0 - 2.0) * vars->zoom + vars->shift_y;
	return (p);
}
