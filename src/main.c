/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:23 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/27 23:38:07 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_vars(t_vars *vars);
static int	parse_args(int argc, char **argv, t_vars *vars);
static void	init_mlx(t_vars *vars);
static int	is_valid_double(char *str);

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_vars(&vars);
	if (parse_args(argc, argv, &vars) == FALSE)
	{
		if (vars.iterations)
			free(vars.iterations);
		print_usage();
		return (1);
	}
	init_mlx(&vars);
	calculate_fractol(&vars);
	render_fractol(&vars);
	mlx_key_hook(vars.win, keycode, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, game_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

static void	init_vars(t_vars *vars)
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
	vars->needs_render = 1;
	vars->max_iter = 100;
	vars->iterations = malloc(sizeof(int *) * WIDTH * HEIGHT);
	if (!vars->iterations)
	{
		perror("Error");
		exit(1);
	}
}

static int	parse_args(int argc, char **argv, t_vars *vars)
{
	if (argc < 2)
		return (FALSE);
	if (!ft_strcmp(argv[1], "julia"))
	{
		if (argc < 4 || !is_valid_double(argv[2]) || !is_valid_double(argv[3]))
			return (FALSE);
		vars->type = JULIA;
		vars->julia.x = ft_atof(argv[2]);
		vars->julia.y = ft_atof(argv[3]);
	}
	else if (!ft_strcmp(argv[1], "mandelbrot"))
		vars->type = MANDELBROT;
	else
		return (FALSE);
	return (TRUE);
}

static void	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		if (vars->iterations)
			free(vars->iterations);
		perror("Error");
		exit(1);
	}
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "fractol");
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
}

static int	is_valid_double(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (FALSE);
		}
		else if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
