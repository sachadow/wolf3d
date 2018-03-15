/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_crea.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 16:05:17 by sderet            #+#    #+#             */
/*   Updated: 2018/03/15 17:31:38 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "minilibx/mlx.h"
#include <stdlib.h>
#include <fcntl.h>

int		win_crea_plus(t_image *img, t_mmlx *mlx)
{
	int a;

	img->map = mlx_get_data_addr(mlx->image,
			&img->bpp, &img->line_len, &img->endian);
	img->sp1 = mlx_get_data_addr(mlx->sprite1,
			&img->bpp, &img->trash, &img->endian);
	a = img->trash;
	img->sp2 = mlx_get_data_addr(mlx->sprite2,
			&img->bpp, &img->trash, &img->endian);
	if (a != img->trash)
		return (0);
	img->sp3 = mlx_get_data_addr(mlx->sprite3,
			&img->bpp, &img->trash, &img->endian);
	if (a != img->trash)
		return (0);
	img->sp4 = mlx_get_data_addr(mlx->sprite4,
			&img->bpp, &img->trash, &img->endian);
	if (a != img->trash)
		return (0);
	return (1);
}

int		win_crea_minus(t_image *img, t_mmlx *mlx)
{
	int a;
	int b;

	mlx->sprite1 = mlx_xpm_file_to_image(mlx->mlx, "images/gg.xpm",
			&img->spritesizex, &img->spritesizey);
	a = img->spritesizex;
	b = img->spritesizey;
	mlx->sprite2 = mlx_xpm_file_to_image(mlx->mlx, "images/fe.xpm",
			&img->spritesizex, &img->spritesizey);
	if (b < img->spritesizey)
		img->spritesizex = a;
	mlx->sprite3 = mlx_xpm_file_to_image(mlx->mlx, "images/la.xpm",
			&img->spritesizex, &img->spritesizey);
	if (b < img->spritesizey)
		img->spritesizex = a;
	mlx->sprite4 = mlx_xpm_file_to_image(mlx->mlx, "images/nm.xpm",
			&img->spritesizex, &img->spritesizey);
	if (b < img->spritesizey)
		img->spritesizex = a;
	return (1);
}

void	window_creation(t_image *img, t_mmlx *mlx, t_bigg *big)
{
	big += 0;
	img->maxx = WINDOW_X;
	img->maxy = WINDOW_Y;
	mlx->win = mlx_new_window(mlx->mlx, img->maxx, img->maxy, "Wolf3D");
	mlx->image = mlx_new_image(mlx->mlx, img->maxx, img->maxy);
	if (win_crea_minus(img, mlx) == 0)
	{
		std_err(2, 0);
		exit(EXIT_FAILURE);
	}
	if (mlx->image == NULL || mlx->sprite1 == NULL || mlx->sprite2 == NULL ||
			mlx->sprite3 == NULL || mlx->sprite4 == NULL)
	{
		std_err(2, 0);
		exit(EXIT_FAILURE);
	}
	if (win_crea_plus(img, mlx) == 0)
	{
		std_err(2, 0);
		exit(EXIT_FAILURE);
	}
}
