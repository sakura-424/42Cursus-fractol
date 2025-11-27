/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:06:01 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/27 23:14:27 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 800
#define MAX_ITER 100
#define JULIA 1
#define MANDELBROT 0
#define TRUE 1
#define FALSE 0
#define BLACK 0x000000

typedef struct s_complex
{
	double		x;
	double		y;
}				t_complex;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;
typedef struct s_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	long double	zoom;
	long double	shift_x;
	long double	shift_y;
	t_complex	julia;
	int			type;
	int			color_shift;
	int			*iterations;
	int			needs_render;
	int			max_iter;
}				t_vars;

// color.c
void			put_color(t_vars *vars, int x, int y, int color);
int				get_color(int iter, t_vars *vars);

// user_help.c
void			print_usage(void);

// draw_fractol.c
// void draw_fractol(t_vars *vars);
void			calculate_fractol(t_vars *vars);
void			render_fractol(t_vars *vars);

// ft_atof.c
double			ft_atof(char *str);

// events.c
int				keycode(int keycode, t_vars *vars);
int				close_window(t_vars *vars);
int				mouse_hook(int button, int x, int y, t_vars *vars);
int				game_loop(t_vars *vars);
