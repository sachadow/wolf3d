/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:42:40 by sderet            #+#    #+#             */
/*   Updated: 2018/02/15 18:35:10 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft/libft.h"
#include "wolf.h"
#include "stdlib.h"

int		std_err(int err, t_map *map)
{
	int a;

	if (map->map != NULL)
	{
		a = -1;
		while (map->map[++a] != 0)
			free(map->map[a]);
		free(map->map);
	}
	if (err == 1)
		ft_putendl("usage :	./wolf3d");
	if (err == 2)
	{
		ft_putstr("Error : source file format may be incorrect or ");
		ft_putendl("file doesn't exist.");
	}
	return (1);
}

int		keypress(int keycode, t_bigg *big)
{
	int a;

	ft_putstr("pos x :");
	ft_putnbr(big->player.pos.x);
	ft_putchar('\n');
	ft_putstr("pos y :");
	ft_putnbr(big->player.pos.y);
	ft_putchar('\n');
	ft_putstr("direction :");
	ft_putnbr(big->player.direction);
	ft_putchar('\n');
	if (keycode == 53)
	{
		a = -1;
		while (++a < big->map.hgt)
			free(big->map.map[a]);
		free(big->map.map);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 126)
	{
		big->player.pos.x += cos(RAD(big->player.direction)) * MVT_SPD;
		big->player.pos.y -= sin(RAD(big->player.direction)) * MVT_SPD;
	}
	if (keycode == 125)
	{
		big->player.pos.x -= cos(RAD(big->player.direction)) * MVT_SPD;
		big->player.pos.y += sin(RAD(big->player.direction)) * MVT_SPD;
	}
	if (keycode == 124)
		big->player.direction += TURN_SPD;
	if (keycode == 123)
		big->player.direction -= TURN_SPD;
	if (big->player.direction < 0)
		big->player.direction += 360;
	if (big->player.direction > 360)
		big->player.direction -= 360;
	raycast(big->player, big->map, &(big->img));
	mlx_put_image_to_window(big->mlx.mlx, big->mlx.win, big->mlx.image, 0, 0);
	mlx_loop(big->mlx.mlx);
	return (0);
}

int		mousepress(int button, int x, int y, t_bigg *big)
{
	button += 0;
	x += 0;
	y += 0;
	big += 0;
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
	return(0);
}

int		main()
{
	t_bigg	big;
	int		a;
	int		b;

	if (youpi("map.w3d", &(big.map)) == NULL)
		return (std_err(2, &(big.map)));
	a = 0;
	while (a < big.map.hgt)
	{
		b = 0;
		while (b < big.map.len)
		{
			ft_putnbr(big.map.map[a][b]);
			b++;
		}
		ft_putchar('\n');
		a++;
	}
	big.player.pos.x = 300;
	big.player.pos.y = 300;
	big.player.direction = 0;
	big.map.distance = (WINDOW_X / 4) / (tan(RAD(30)));
	big.mlx.mlx = mlx_init();
	window_creation(&(big.img), &(big.mlx));
	raycast(big.player, big.map, &(big.img));
	mlx_put_image_to_window(big.mlx.mlx, big.mlx.win, big.mlx.image, 0, 0);
	mlx_key_hook(big.mlx.win, &keypress, &big);
	mlx_mouse_hook(big.mlx.win, &mousepress, &big);
	mlx_hook(big.mlx.win, 17, 0, quit_button, &big);
	mlx_loop(big.mlx.mlx);
}
