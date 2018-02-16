/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:11:13 by sderet            #+#    #+#             */
/*   Updated: 2018/02/16 18:14:29 by sderet           ###   ########.fr       */
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

void	print_pixelc(t_image *img, t_pos *pos, int cot)
{
	int colo[3];
	int a;
	int b;

	b = (cot == -1 ? 0 : 122);
	b = (cot == 1 ? 255 : b + 0);
	a = -1;
	while (++a < 3)
		colo[a] = b;
	print_pixel(img, pos, colo);
}
