/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 04:29:09 by ltreser           #+#    #+#             */
/*   Updated: 2024/02/25 23:42:22 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	uninit(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->connection, data->img);
	if (data->window)
		mlx_destroy_window(data->connection, data->window);
	if (data->connection)
	{
		mlx_destroy_display(data->connection);
		free(data->connection);
	}
	free(data);
	exit(1);
}

int	escape(int key, t_data *data)
{
	if (key == 65307 || key == 53)
		uninit(data);
	return (0);
}

int	zoom(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 4)
		data->zoom *= 1.1;
	else if (key == 5)
		data->zoom /= 1.1;
	render(data);
	return (0);
}
