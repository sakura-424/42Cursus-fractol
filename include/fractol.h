/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya <skatsuya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:06:01 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/26 15:01:35 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 100
# define JULIA 1
# define MANDELBROT 0
# define TRUE 1
# define FALSE 0

typedef struct s_complex
{
	double  x;
	double  y;
}	t_complex;
typedef struct	s_vars {
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	zoom;
	double	shift_x;
	double	shift_y;
	t_complex	julia;
	int		type;
}				t_vars;

// put_color.c
void put_color(t_vars *vars, int x, int y, int color);

// user_help.c
void print_help(void);

// draw_fractol.c
void draw_fractol(t_vars *vars);

// ft_atof.c
double ft_atof(char *str);

// evenrs.c
int keycode(int keycode, t_vars *vars);
int close_window(t_vars *vars);
int mouse_hook(int button, int x, int y, t_vars *vars);
