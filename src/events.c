/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 06:30:15 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/27 23:14:08 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	keycode(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_window(vars);
	if (keycode == 65361)
		vars->shift_x = vars->shift_x - 0.5 * vars->zoom;
	if (keycode == 65362)
		vars->shift_y = vars->shift_y - 0.5 * vars->zoom;
	if (keycode == 65363)
		vars->shift_x = vars->shift_x + 0.5 * vars->zoom;
	if (keycode == 65364)
		vars->shift_y = vars->shift_y + 0.5 * vars->zoom;
	vars->needs_render = 1;
	return (0);
}

int	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars->iterations);
	exit(0);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		vars->zoom = vars->zoom * 0.9;
		vars->max_iter += 10;
	}
	else if (button == 5)
	{
		vars->zoom = vars->zoom * 1.1;
		vars->max_iter -= 10;
		if (vars->max_iter < 50)
			vars->max_iter = 50;
	}
	if (vars->max_iter > 200)
		vars->max_iter = 200;
	vars->needs_render = 1;
	return (0);
}

int	game_loop(t_vars *vars)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_usec / 1000;
	vars->color_shift = (current_time % 255);
	if (vars->needs_render)
	{
		calculate_fractol(vars);
		vars->needs_render = 0;
	}
	render_fractol(vars);
	return (0);
}
