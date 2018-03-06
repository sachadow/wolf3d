/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_crea.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 16:05:17 by sderet            #+#    #+#             */
/*   Updated: 2018/03/06 18:26:59 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "minilibx/mlx.h"
#include <stdlib.h>
#include <fcntl.h>

void	window_creation(t_image *img, t_mmlx *mlx, t_bigg *big)
{
	big += 0;
	img->maxx = WINDOW_X;
	img->maxy = WINDOW_Y;
	mlx->win = mlx_new_window(mlx->mlx, img->maxx, img->maxy, "Wolf3D");
	mlx->image = mlx_new_image(mlx->mlx, img->maxx, img->maxy);
	mlx->sprite1 = mlx_xpm_file_to_image(mlx->mlx, "m.xpm", &img->spritesizex,
			&img->spritesizey);
	mlx->sprite2 = mlx_xpm_file_to_image(mlx->mlx, "m.xpm", &img->spritesizex,
			&img->spritesizey);
	mlx->sprite3 = mlx_xpm_file_to_image(mlx->mlx, "m.xpm", &img->spritesizex,
			&img->spritesizey);
	mlx->sprite4 = mlx_xpm_file_to_image(mlx->mlx, "m.xpm", &img->spritesizex,
			&img->spritesizey);
	if (mlx->image == NULL || mlx->sprite1 == NULL || mlx->sprite2 == NULL ||
			mlx->sprite3 == NULL || mlx->sprite4 == NULL)
	{
		std_err(2, 0);
		exit(EXIT_FAILURE);
	}
	img->map = mlx_get_data_addr(mlx->image,
			&img->bpp, &img->line_len, &img->endian);
	img->sp1 = mlx_get_data_addr(mlx->sprite1,
			&img->bpp, &img->trash, &img->endian);
	img->sp2 = mlx_get_data_addr(mlx->sprite2,
			&img->bpp, &img->trash, &img->endian);
	img->sp3 = mlx_get_data_addr(mlx->sprite3,
			&img->bpp, &img->trash, &img->endian);
	img->sp4 = mlx_get_data_addr(mlx->sprite4,
			&img->bpp, &img->trash, &img->endian);
}
