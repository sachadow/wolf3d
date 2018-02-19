/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:11:13 by sderet            #+#    #+#             */
/*   Updated: 2018/02/19 18:02:25 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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

void	print_pixelc(t_image *img, t_pos *pos, int cot, t_dposd *c)
{
	int colo[3];
	int a;
	int b;

	b = (cot == -1 ? 0 : 122);
	b = (cot == 1 ? 255 : b + 0);
	a = -1;
	while (++a < 3)
		colo[a] = b;
	a = -1;
	if (cot == 1)
	{
		if (img->ang < 180)
		{
			colo[0] = 50;
			colo[1] = 0;
		}
		if (ABS((int)c->d.x) % BLOC_SIZE >= BLOC_SIZE - (BLOC_SIZE / 10)
				|| ABS((int)c->d.x) % BLOC_SIZE <= (BLOC_SIZE / 10))
			while (++a < 3)
				colo[a] = 40;
	}
	if (cot == 0)
	{
		if (img->ang < 270 && img->ang > 90)
		{
			colo[1] = 60;
			colo[2] = 0;
		}
		if (ABS((int)c->c.y) % BLOC_SIZE >= BLOC_SIZE - (BLOC_SIZE / 10)
				|| ABS((int)c->c.y) % BLOC_SIZE <= (BLOC_SIZE / 10))
			while (++a < 3)
				colo[a] = 40;
	}
	if (pos->x >= 0 && pos->x < WINDOW_X && pos->y >= 0 && pos->y < WINDOW_Y)
		print_pixel(img, pos, colo);
}
