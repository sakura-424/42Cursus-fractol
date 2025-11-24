/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya <skatsuya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:23 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/25 06:36:58 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void init_vars(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->img = NULL;
	vars->addr = NULL;
	vars->zoom = 1.0;
	vars->shift_x = 0.0;
	vars->shift_y = 0.0;
	vars->julia.x = 0.0;
	vars->julia.y = 0.0;
}

static int parse_args(int argc, char **argv, t_vars *vars)
{
	if (argc < 2)
		return (0);
	if (!ft_strcmp(argv[1], "julia"))
	{
		if (argc < 4)
		{
			print_help();
			return (1);
		}
		vars->type = 1;
		vars->julia.x = ft_atof(argv[2]);
		vars->julia.y = ft_atof(argv[3]);
	}
	else if(!ft_strcmp(argv[1], "mandelbrot"))
		vars->type = 0;
	else
		return (0);
	return (1);
}

static void init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		exit(1);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "fractol");
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
}

int main(int argc, char **argv)
{
	t_vars vars;

	init_vars(&vars);
	if (parse_args(argc, argv, &vars) == 0)
	{
		print_help();
		return (1);
	}
	init_mlx(&vars);
	draw_fractol(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, keycode, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
