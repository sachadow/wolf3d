/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:53:41 by sderet            #+#    #+#             */
/*   Updated: 2018/02/16 19:30:44 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

double	intersec(t_char ray, t_char player, t_map map, int *cot)
{
	t_pos	mappos;
	t_posd	ddist;
	t_posd	sdist;
	double	walldist;
	t_posd	step;
	int		hit;

	mappos.x = (int)player.pos.x;
	mappos.y = (int)player.pos.y;
	ddist.x = ABS(1 / ray.pos.x);
	ddist.y = ABS(1 / ray.pos.y);
	if (ray.pos.x < 0)
	{
		step.x = -1;
		sdist.x = (player.pos.x - mappos.x) * ddist.x;
	}
	else
	{
		step.x = 1;
		sdist.x = (mappos.x + 1.0 - player.pos.x) * ddist.x;
	}
	if (ray.pos.y < 0)
	{
		step.y = -1;
		sdist.y = (player.pos.y - mappos.y) * ddist.y;
	}
	else
	{
		step.y = 1;
		sdist.y = (mappos.y + 1.0 - player.pos.y) * ddist.y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (sdist.x < sdist.y)
		{
			sdist.x += ddist.x;
			mappos.x += step.x;
			*cot = 0;
		}
		else
		{
			sdist.y += ddist.y;
			mappos.y += step.y;
			*cot = 1;
		}
		if (map.map[(int)mappos.x][(int)mappos.y] != 0)
			hit = 1;
	}
	if (*cot == 0)
		walldist = (mappos.x - player.pos.x + (1 - step.x) / 2) / ray.pos.x;
	else
		walldist = (mappos.y - player.pos.y + (1 - step.y) / 2) / ray.pos.y;
	return (walldist);
}

void	print_slice(t_image *img, int a, int slice, int cot)
{
	int		b;
	int		c;
	t_pos	pos;

	b = 0;
	if (slice >= WINDOW_Y)
		slice = WINDOW_Y - 1;
	else if (slice >= 0)
		b = (slice < WINDOW_Y ? (WINDOW_Y - slice) / 2 : WINDOW_Y - 1);
	else
		slice = 0;
	c = 0;
	while (c < slice)
	{
		pos.x = a;
		pos.y = b;
		if (a >= 0 && b >= 0)
			print_pixelc(img, &pos, cot);
		c++;
		b++;
	}
}

void	clean_map(t_image *img)
{
	t_pos pos;
	int a;
	int b;

	a = 0;
	while (a < WINDOW_Y)
	{
		b = 0;
		while (b < WINDOW_X)
		{
			pos.x = b;
			pos.y = a;
			print_pixelc(img, &pos, -1);
			b++;
		}
		a++;
	}
}

void	raycast(t_char player, t_map map, t_image *img)
{
	int		a;
	int		cot;
	double	distance;
	t_char	ray;
	t_posd	dir;
	t_posd	plane;
	t_posd	camera;

	dir.x = -1;
	dir.y = 0;
	plane.x = 0;
	plane.y = 0.66;
	clean_map(img);
	a = 0;
	while (a < WINDOW_X)
	{
		camera.x = 2 * a / WINDOW_X - 1;
		ray.pos.x = dir.x + plane.x * camera.x;
		ray.pos.y = dir.y + plane.y * camera.y;
		distance = intersec(ray, player, map, &cot);
		map.slice = (int)(WINDOW_Y / distance);
		print_slice(img, a, map.slice, cot);
		a++;
	}
}
