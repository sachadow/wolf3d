/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:11:13 by sderet            #+#    #+#             */
/*   Updated: 2018/02/22 17:45:39 by sderet           ###   ########.fr       */
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
		while (++a < 3)
			colo[a] = b;
	}
	else
	{
		colo[0] = (img->ang < 180 && c->cot == 1 ? 50 : colo[0] + 0);
		colo[1] = (img->ang < 180 && c->cot == 1 ? 0 : colo[1] + 0);
		colo[1] = (img->ang < 270 && img->ang > 90 && c->cot == 0 ? 60 :
				colo[1] + 0);
		colo[2] = (img->ang < 270 && img->ang > 90 && c->cot == 0 ? 0 :
				colo[2] + 0);
	}
}

void	print_pixelc(t_image *img, t_pos *pos, t_dposd *c, int slice)
{
	int colo[3];
	int a;
	int	y_start;

	pre_ppc(colo, img, c, 1);
	y_start = (WINDOW_Y - slice) / 2;
	a = -1;
	if (c != 0)
	{
		pre_ppc(colo, img, c, 2);
		if (((ABS((int)c->d.x) % BLOC_SIZE >= BLOC_SIZE - (BLOC_SIZE / 10)
				|| ABS((int)c->d.x) % BLOC_SIZE <= (BLOC_SIZE / 10)) &&
				c->cot == 1) || ((ABS((int)c->c.y) % BLOC_SIZE >= BLOC_SIZE
				- (BLOC_SIZE / 10) || ABS((int)c->c.y) % BLOC_SIZE <=
				(BLOC_SIZE / 10)) && c->cot == 0))
			while (++a < 3)
				colo[a] = 40;
		else if (pos->y - y_start < (slice / 10))
			colo[(c->cot == 1 ? 2 : 0)] = 80;
	}
	if (pos->x >= 0 && pos->x < WINDOW_X && pos->y >= 0 && pos->y < WINDOW_Y)
		print_pixel(img, pos, colo);
}
