/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:55:14 by ltreser           #+#    #+#             */
/*   Updated: 2024/02/26 20:33:10 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calculate_fractal(int x, int y, t_data *data)
{
	double	temp;
	float	i;

	data->zx = 0;
	data->zy = 0;
	data->cx = (x - WIDTH / 2) * 4 / (WIDTH * data->zoom);
	data->cy = (y - HEIGHT / 2) * 4 / (HEIGHT * data->zoom);
	i = -1;
	if (data->julia)
	{
		data->cx = data->j_x;
		data->cy = data->j_y;
		data->zx = -(x - WIDTH / 2) * 4 / (WIDTH * data->zoom);
		data->zy = (y - HEIGHT / 2) * 4 / (HEIGHT * data->zoom);
	}
	while ((data->zx * data->zx + data->zy * data->zy) <= 4
		&& i++ < MAX_ITERATIONS)
	{
		temp = data->zx * data->zx - data->zy * data->zy + data->cx;
		data->zy = 2 * data->zx * data->zy + data->cy;
		data->zx = temp;
	}
	return (i);
}

void	render(t_data *data)
{
	data->y = 0;
	while (data->y < HEIGHT)
	{
		data->x = 0;
		while (data->x < WIDTH)
		{
			if (calculate_fractal(data->x, data->y, data) < (MAX_ITERATIONS
					- 200))
				*(unsigned int *)(data->pixel_adress + (data->y * data->line_len
							+ data->x * data->bpp
							/ 8)) = calculate_fractal(data->x, data->y, data)
					* data->color / 10;
			else
				*(unsigned int *)(data->pixel_adress + (data->y * data->line_len
							+ data->x * data->bpp / 8)) = 0xFFF8E1;
			data->x++;
		}
		data->y++;
	}
	mlx_put_image_to_window(data->connection, data->window, data->img, 0, 0);
}

int	argument_error(int ac, char **av, t_data *data)
{
	if (av[1])
		data->window_title = av[1];
	if (2 == ac && ft_strlen(av[1]) == 10 && \
		!ft_strncmp(av[1], "mandelbrot", 10))
	{
		data->julia = 0;
		return (0);
	}
	else if (4 == ac && ft_strlen(av[1]) == 5 && !ft_strncmp(av[1], "julia", 5))
	{
		data->julia = 1;
		data->j_x = atof(av[2]);
		data->j_y = atof(av[3]);
		if (data->j_x > 2 || data->j_x < -2 || data->j_y > 2 || data->j_y < -2)
			return (1);
		return (0);
	}
	else if (2 == ac && ft_strlen(av[1]) == 5 && !ft_strncmp(av[1], "julia", 5))
	{
		data->julia = 1;
		data->j_x = -0.8;
		data->j_y = 0.156;
		return (0);
	}
	return (1);
}

int	init_data(t_data *data)
{
	data->x = 0;
	data->y = 0;
	data->bpp = 24;
	data->line_len = WIDTH * 3;
	data->endian = 0;
	data->zoom = 1;
	data->color = 0xE6E6FA;
	data->connection = mlx_init();
	if (!data->connection)
		return (0);
	data->window = mlx_new_window(data->connection, WIDTH, HEIGHT,
			data->window_title);
	if (!data->window)
		return (mlx_destroy_display(data->connection), free(data->connection),
			0);
	data->img = mlx_new_image(data->connection, WIDTH, HEIGHT);
	if (!data->img)
		return (mlx_destroy_window(data->connection, data->window),
			mlx_destroy_display(data->connection), free(data->connection), 0);
	data->pixel_adress = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (argument_error(ac, av, data))
		return (ft_putstr_fd(ERROR_MESSAGE, 2), free(data), 0);
	if (!init_data(data))
		return (perror("Failed to initialize MLX"), 0);
	render(data);
	mlx_hook(data->window, 17, 0, uninit, data);
	mlx_key_hook(data->window, escape, data);
	mlx_mouse_hook(data->window, zoom, data);
	mlx_loop(data->connection);
	return (0);
}
