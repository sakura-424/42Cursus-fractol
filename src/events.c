/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya <skatsuya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 06:30:15 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/25 06:30:33 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int keycode(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_window(vars);
	if (keycode == 123)
		vars->shift_x = vars->shift_x - 0.5 * vars->zoom;
	if (keycode == 126)
		vars->shift_y = vars->shift_y - 0.5 * vars->zoom;
	if (keycode == 124)
		vars->shift_x = vars->shift_x + 0.5 * vars->zoom;
	if (keycode == 125)
		vars->shift_y = vars->shift_y + 0.5 * vars->zoom;
	draw_fractol(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	printf("Pressed key: %d\n", keycode);
	return (0);
}

int close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	// free(vars->mlx);
	exit(0);
	return (0);
}

int mouse_hook(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 4)
		vars->zoom = vars->zoom * 0.9;
	else if (button == 5)
		vars->zoom = vars->zoom * 1.1;
	draw_fractol(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}
