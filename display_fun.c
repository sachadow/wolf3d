/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:11:13 by sderet            #+#    #+#             */
/*   Updated: 2018/03/06 18:14:43 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>

void	print_pixel(t_image *img, t_pos *pos, int *colo)
{
	int		a;

	a = 0;
	while (a < 3)
	{
		img->map[(((int)pos->x * 4) + a) +
			((int)pos->y * img->line_len)] = (char)colo[a];
		a++;
	}
	img->map[(((int)pos->x * 4) + a) +
		((int)pos->y * img->line_len)] = (char)0;
}

void	pre_ppc(int *colo, t_image *img, t_dposd *c, int mode)
{
	int a;
	int b;

	if (mode == 1)
	{
		b = (c == 0 ? 0 : 122);
		b = (c != 0 && c->cot == 1 ? 255 : b + 0);
		a = -1;
		img += 0;
		while (++a < 3)
			colo[a] = b;
	}
}

void	print_pixelc(t_image *img, t_pos *pos, t_dposd *c, int slice)
{
	int colo[3];
	int a;
	int	res;
	int	y_start;

	pre_ppc(colo, img, c, 1);
	y_start = (WINDOW_Y - slice) / 2;
	a = -1;
	if (c != 0)
	{
		a = -1;
		while (++a < 3)
		{
			if (c->cot == 1)
				res = (int)((((int)(((double)((int)c->d.x %
					BLOC_SIZE) / BLOC_SIZE) * img->spritesizex) * 4) + a) +
					((int)(((double)((int)pos->y - y_start) /
					slice) * img->spritesizey) * img->trash));
			if (c->cot == 0)
				res = (int)((((int)(((double)((int)c->c.y %
					BLOC_SIZE) / BLOC_SIZE) * img->spritesizex) * 4) + a) +
					((int)(((double)((int)pos->y - y_start) /
					slice) * img->spritesizey) * img->trash));
			if (c->cot == 1 && img->ang < 180)
				colo[a] = (int)(img->sp1[res]);
			else if (c->cot == 1)
				colo[a] = (int)(img->sp2[res]);
			else if (c->cot == 0 && img->ang < 270 && img->ang > 90)
				colo[a] = (int)(img->sp3[res]);
			else
				colo[a] = (int)(img->sp4[res]);
		}
		a = -1;
		if (((ABS((int)c->d.x) % BLOC_SIZE >= BLOC_SIZE - (BLOC_SIZE / 20)
				|| ABS((int)c->d.x) % BLOC_SIZE <= (BLOC_SIZE / 20)) &&
				c->cot == 1) || ((ABS((int)c->c.y) % BLOC_SIZE >= BLOC_SIZE
				- (BLOC_SIZE / 20) || ABS((int)c->c.y) % BLOC_SIZE <=
				(BLOC_SIZE / 20)) && c->cot == 0))
			while (++a < 3)
				colo[a] = 40;
	}
	if (pos->x >= 0 && pos->x < WINDOW_X && pos->y >= 0 && pos->y < WINDOW_Y)
		print_pixel(img, pos, colo);
}
