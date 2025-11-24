/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya <skatsuya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:23 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/25 00:46:58 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

void draw_fractol(t_vars *vars);
int mouse_hook(int button, int x, int y, t_vars *vars);

int keycode(int keycode, t_vars *vars)
{
	if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
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
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

void draw_fractol(t_vars *vars)
{
	int x;
	int y;
	double cx;
	double cy;
	double zx;
	double zy;
	double tmp_x;
	int iter;
	int offset;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		if (vars->type == julia)
			cy = vars->julia_cy;
		else
			cy = (((double)y / HEIGHT) * 4.0 - 2.0) * vars->zoom + vars->shift_y;
		while (x < WIDTH)
		{
			iter = 0;
			if (vars->type == julia)
			{
				zx = (((double)x / WIDTH) * 4.0 - 2.0) * vars->zoom + vars->shift_x;
				zy = (((double)y / HEIGHT) * 4.0 - 2.0) * vars->zoom + vars->shift_y;
			}
			else
			{
				zx = 0.0;
				zy = 0.0;
			}
			if (vars->type == julia)
				cx = vars->julia_cx;
			else
				cx = (((double)x / WIDTH) * 4.0 - 2.0) * vars->zoom + vars->shift_x;
			while (zx * zx + zy * zy < 4.0 && iter < MAX_ITER)
			{
				tmp_x = zx * zx - zy * zy + cx;
				zy = 2.0 * zx * zy + cy;
				zx = tmp_x;
				iter++;
			}
			offset = (y * WIDTH + x) * 4;
			if (iter == MAX_ITER)
				*(int *)(vars->addr + offset) = 0x000000;
			else
				*(int *)(vars->addr + offset) = (int)(zx * zx * zy * zy * 20) << 16;
			x++;
		}
		y++;
	}
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

double ft_atof(char *str)
{
	int i;
	int sign;
	double result;
	double div;

	i = 0;
	sign = 1;
	result = 0.0;
	div = 1.0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		div = div * 10;
		result = result + (str[i] - '0') / div;
		i++;
	}
	return (result * sign);
}

void print_help(void)
{
	ft_putstr_fd("1. Usage : ./fractol mandelbrot\n", 1);
	ft_putstr_fd("2. Usage: ./fractol julia <real> <imaginary>\n", 1);
}

int main(int argc, char **argv)
{
	t_vars vars;
	vars.mlx = mlx_init();
	vars.zoom = 1.0;
	vars.shift_x = 0.0;
	vars.shift_y = 0.0;

	if (argc < 2)
		return (1);
	if (!ft_strcmp(argv[1], "julia"))
	{
		if (argc < 4)
		{
			print_help();
			return (1);
		}
		vars.type = 1;
		vars.julia_cx = ft_atof(argv[2]);
		vars.julia_cy = ft_atof(argv[3]);
	}
	else if(!ft_strcmp(argv[1], "mandelbrot"))
		vars.type = 0;
	else
	{
		print_help();
		return (1);
	}
	vars.win = mlx_new_window(vars.mlx, 800, 800, "fractol");
	vars.img = mlx_new_image(vars.mlx, 800, 800);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);

	draw_fractol(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);

	mlx_key_hook(vars.win, keycode, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
