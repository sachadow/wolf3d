/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:39:48 by sderet            #+#    #+#             */
/*   Updated: 2018/02/20 17:04:46 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int		ft_count(char *str, char c)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (str[a] != 0)
	{
		if (str[a] == c)
			b++;
		a++;
	}
	return (b);
}

char	***sstrsplit(char *gnltab)
{
	char	***split;
	char	**minisplit;
	int		mal_size;
	int		a;

	if (ft_count(gnltab, ' ') < ft_count(gnltab, '\n'))
		return (NULL);
	mal_size = 0;
	if (!(minisplit = ft_strsplit(gnltab, '\n')))
		return (NULL);
	while (minisplit[mal_size] != 0)
		mal_size++;
	split = (char***)malloc(sizeof(char**) * (mal_size + 1));
	split[mal_size] = 0;
	a = 0;
	while (minisplit[a] != 0)
	{
		if (!(split[a] = ft_strsplit(minisplit[a], ' ')))
			return (NULL);
		free(minisplit[a]);
		a++;
	}
	free(minisplit);
	return (split);
}

int		**postab(char ***split, t_map *map)
{
	t_pos	a;
	int		c;
	int		**tab;

	a.x = -1;
	while (split[++a.x] != 0)
		;
	if (!(tab = (int**)malloc(sizeof(int*) * (a.x))))
		return (NULL);
	map->hgt = a.x;
	a.x = -1;
	c = 0;
	while (split[++a.x] != 0)
	{
		a.y = -1;
		while (split[a.x][++a.y] != 0)
			;
		if (!(tab[a.x] = (int*)malloc(sizeof(int) * (a.y))))
			return (NULL);
		c = (c == 0 ? a.y : c + 0);
		map->len = a.y;
		if (a.y != c)
			return (NULL);
	}
	return (tab);
}

void	finaltab(char ***split, t_map *map)
{
	int a;
	int b;

	a = 0;
	while (split[a] != 0)
	{
		b = 0;
		while (split[a][b] != 0)
		{
			map->map[a][b] = ft_atoi(split[a][b]);
			b++;
		}
		a++;
	}
}

void	*youpi(char *filename, t_map *map)
{
	char	*gnl;
	char	***split;
	int		a;
	int		b;

	if ((gnl = genl(filename)) == NULL)
		return (NULL);
	if ((split = sstrsplit(gnl)) == NULL)
		return (NULL);
	if ((map->map = postab(split, map)) == NULL)
		return (NULL);
	finaltab(split, map);
	a = -1;
	while (split[++a] != 0)
	{
		b = -1;
		while (split[a][++b] != 0)
			free(split[a][b]);
		free(split[a]);
	}
	free(split);
	(*gnl != 0 ? (free(gnl)) : (gnl = gnl + 1 - 1));
	return (map);
}
