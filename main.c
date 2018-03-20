/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:42:40 by sderet            #+#    #+#             */
/*   Updated: 2018/03/20 14:48:16 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft/libft.h"
#include "wolf.h"
#include "stdlib.h"

int		press_button(int keycode, t_bigg *big)
{
	int a;

	if (keycode == 53)
	{
		a = -1;
		while (++a < big->map.hgt)
			free(big->map.map[a]);
		free(big->map.map);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 126 || keycode == 125)
		big->player.move += (keycode == 126 ? 1 : -1);
	if (keycode == 124 || keycode == 123)
		big->player.turn += (keycode == 124 ? 1 : -1);
	big->player.direction += (big->player.direction < 0 ? 360 : 0);
	big->player.direction -= (big->player.direction > 360 ? 360 : 0);
	return (0);
}

int		rel_button(int keycode, t_bigg *big)
{
	if (keycode == 126 || keycode == 125)
		big->player.move += (keycode == 126 ? -1 : 1);
	if (keycode == 124 || keycode == 123)
		big->player.turn += (keycode == 124 ? -1 : 1);
	return (0);
}

int		quit_button(t_bigg *big)
{
	int a;

	big += 0;
	a = -1;
	while (++a < big->map.hgt)
		free(big->map.map[a]);
	free(big->map.map);
	exit(EXIT_SUCCESS);
	return (0);
}

int		loop(t_bigg *big)
{
	t_pos	c;

	if (big->player.move != 0)
	{
		c.x = big->player.pos.x + (((big->player.move == 1 ? 1 : -1) *
					(cos(RAD(big->player.direction)) * MVT_SPD)));
		c.y = big->player.pos.y + (((big->player.move == 1 ? -1 : 1) *
					(sin(RAD(big->player.direction)) * MVT_SPD)));
		if (c.y / BLOC_SIZE >= 0 && c.y / BLOC_SIZE < big->map.hgt &&
				big->map.map[c.y / BLOC_SIZE][big->player.pos.x / BLOC_SIZE]
				== 0)
			big->player.pos.y = c.y;
		if (c.x / BLOC_SIZE >= 0 && c.x / BLOC_SIZE < big->map.len &&
				big->map.map[big->player.pos.y / BLOC_SIZE][c.x / BLOC_SIZE]
				== 0)
			big->player.pos.x = c.x;
	}
	if (big->player.turn != 0)
		big->player.direction += (big->player.turn == 1 ? TURN_SPD : -TURN_SPD);
	big->player.direction += (big->player.direction < 0 ? 360 : 0);
	big->player.direction -= (big->player.direction > 360 ? 360 : 0);
	raycast(big->player, big->map, &(big->img));
	mlx_put_image_to_window(big->mlx.mlx, big->mlx.win, big->mlx.image, 0, 0);
	return (0);
}

int		main(void)
{
	t_bigg	big;

	if (youpi("map.w3d", &(big.map)) == NULL)
		return (std_err(2, &(big.map)));
	big.player.pos.x = BLOC_SIZE + (BLOC_SIZE / 2);
	big.player.pos.y = BLOC_SIZE + (BLOC_SIZE / 2);
	big.player.direction = 270;
	big.player.move = 0;
	big.player.turn = 0;
	big.map.distance = (WINDOW_X / 2) / (tan(RAD(30)));
	big.mlx.mlx = mlx_init();
	window_creation(&(big.img), &(big.mlx), &big);
	raycast(big.player, big.map, &(big.img));
	mlx_put_image_to_window(big.mlx.mlx, big.mlx.win, big.mlx.image, 0, 0);
	mlx_do_key_autorepeatoff(big.mlx.mlx);
	mlx_hook(big.mlx.win, 2, 0, press_button, &big);
	mlx_hook(big.mlx.win, 17, 0, quit_button, &big);
	mlx_key_hook(big.mlx.win, rel_button, &big);
	mlx_loop_hook(big.mlx.mlx, loop, &big);
	mlx_loop(big.mlx.mlx);
	return (0);
}
