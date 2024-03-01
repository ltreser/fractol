/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:48:59 by ltreser           #+#    #+#             */
/*   Updated: 2024/02/26 20:18:52 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ERROR_MESSAGE \
"Please prompt \n\t\"./fractol mandelbrot\" \
or \n\t\"./fractol julia <value between \
-2 & 2> <value between -2 & 2>\"\n"

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITERATIONS 500
# define MAX_COLOR 0xFFFFFFFF

typedef struct s_data	t_data;

struct					s_data
{
	void				*connection;
	void				*window;
	void				*img;
	char				*pixel_adress;
	int					julia;
	int					x;
	int					y;
	float				j_x;
	float				j_y;
	float				zoom;
	float				color;
	char				*window_title;
	int					bpp;
	int					endian;
	int					line_len;
	double				zx;
	double				zy;
	double				cx;
	double				cy;
};

char					*ft_strchr(const char *s, int c);
int						ft_isdigit(int c);
double					ft_atof(const char *str);
void					putstr(char *str);
int						ft_strncmp(char *s1, char *s2, unsigned int n);
int						calculate_fractal(int x, int y, t_data *data);
void					render(t_data *data);
int						init_data(t_data *data);
int						uninit(t_data *data);
int						click_x(int key, t_data *data);
int						escape(int key, t_data *data);
int						zoom(int key, int x, int y, t_data *data);

#endif
