/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:53:41 by sderet            #+#    #+#             */
/*   Updated: 2018/02/17 18:51:26 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

int		check_wall(t_pos pos, t_map map)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < map.len && pos.y < map.hgt)
		return (map.map[pos.y][pos.x]);
	else
		return (0);
}

t_posd	horiz_intersec(t_char ray, t_map map)
{
	t_posd	a;
	t_posd	b;
	t_posd	c;
	t_pos	d;

	if (ray.direction < 180)
		a.y = (int)(ray.pos.y / BLOC_SIZE) * BLOC_SIZE - 1;
	else
		a.y = (int)(ray.pos.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
	a.x = ray.pos.x + (ray.pos.y - a.y)/(tan(RAD(ray.direction)));
	b.y = (ray.direction > 180 ? BLOC_SIZE : -BLOC_SIZE);
	b.x = (-b.y) / (tan(RAD(ray.direction)));
	c.x = a.x;
	c.y = a.y;
	d.x = c.x / BLOC_SIZE;
	d.y = c.y / BLOC_SIZE;
	while (check_wall(d, map) == 0 && d.x >= 0 && d.y >= 0 && d.x < map.len &&
			d.y < map.hgt)
	{
		c.x += b.x;
		c.y += b.y;
		d.x = c.x / BLOC_SIZE;
		d.y = c.y / BLOC_SIZE;
	}
	return (c);
}

t_posd	vertic_intersec(t_char ray, t_map map)
{
	t_posd	a;
	t_posd	b;
	t_posd	c;
	t_pos	d;

	if (ray.direction > 90 && ray.direction < 270)
		a.x = (int)(ray.pos.x / BLOC_SIZE) * BLOC_SIZE - 1;
	else
		a.x = (int)(ray.pos.x / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
	a.y = ray.pos.y + (ray.pos.x - a.x) * (tan(RAD(ray.direction)));
	b.x = (ray.direction < 270 && ray.direction > 90 ?
			-BLOC_SIZE : BLOC_SIZE);
	b.y = (-b.x) * (tan(RAD(ray.direction)));
	c.x = a.x;
	c.y = a.y;
	d.x = c.x / BLOC_SIZE;
	d.y = c.y / BLOC_SIZE;
	while (check_wall(d, map) == 0 && d.x >= 0 && d.y >= 0 && d.x < map.len &&
			d.y < map.hgt)
	{
		c.x += b.x;
		c.y += b.y;
		d.x = c.x / BLOC_SIZE;
		d.y = c.y / BLOC_SIZE;
	}
	return (c);
}

int		dist(t_char ray, t_posd c, t_posd d, int *cot)
{
	double a;
	double b;

	a = sqrt(pow(ray.pos.x - c.x, 2) + pow(ray.pos.y - c.y, 2));
	b = sqrt(pow(ray.pos.x - d.x, 2) + pow(ray.pos.y - d.y, 2));
	if (ABS(a) < ABS(b))
	{
		*cot = 0;
		return (ABS(a));
	}
	else
	{
		*cot = 1;
		return (ABS(b));
	}
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
	t_pos	pos;
	int		a;
	int		b;

	a = -1;
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
	double	pas;
	int		a;
	int		cot;
	double	distance;
	t_posd	c;
	t_posd	d;
	t_char	ray;

	clean_map(img); 
	ray = player;
	img->ang = player.direction - (FOV / 2);
	if (img->ang < 0)
		img->ang = img->ang + 360;
	pas = (double)FOV / (double)WINDOW_X;
	map.center_x = WINDOW_X / 2;
	map.center_y = WINDOW_Y / 2;
	a = 0;
	while (a < WINDOW_X)
	{
		ray.direction = img->ang;
		c = vertic_intersec(ray, map);
		d = horiz_intersec(ray, map);
		distance = dist(ray, c, d, &cot) * cos(RAD(player.direction -
					img->ang));
		map.slice = ((double)BLOC_SIZE / (double)distance) * map.distance;
		print_slice(img, a, map.slice, cot);
		a++;
		img->ang += pas;
		if (img->ang > 360)
			img->ang = img->ang - 360;
	}
}
