/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya <skatsuya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:06:01 by skatsuya          #+#    #+#             */
/*   Updated: 2025/11/23 08:13:52 by skatsuya         ###   ########.fr       */
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
# define julia 1
# define mandelbrot 0

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
	double	julia_cx;
	double	julia_cy;
	int		type;
}				t_vars;
