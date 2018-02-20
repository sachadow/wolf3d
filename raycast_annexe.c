/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_annexe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 17:14:55 by sderet            #+#    #+#             */
/*   Updated: 2018/02/20 17:24:16 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		check_wall(t_pos pos, t_map map)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < map.len && pos.y < map.hgt)
		return (map.map[pos.y][pos.x]);
	else
		return (0);
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
			print_pixelc(img, &pos, 0, 0);
			b++;
		}
		a++;
	}
}
