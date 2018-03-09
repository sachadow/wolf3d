/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_head.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:36:53 by sderet            #+#    #+#             */
/*   Updated: 2018/03/09 17:22:17 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>

# define ABS(x) ((x) > 0 ? x : -(x))
# define RAD(x) ((double)(x) / 57.3)
# define WINDOW_X 720
# define WINDOW_Y 480
# define BLOC_SIZE 128
# define FOV 60
# define MVT_SPD 30
# define TURN_SPD 3

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_image
{
	double	ang;
	char	*map;
	char	*sp1;
	char	*sp2;
	char	*sp3;
	char	*sp4;
	int		line_len;
	int		trash;
	int		bpp;
	int		t_len;
	int		endian;
	int		maxx;
	int		maxy;
	int		spritesizex;
	int		spritesizey;
	t_pos	*pos;
}				t_image;

typedef struct	s_mmlx
{
	void *mlx;
	void *win;
	void *image;
	void *sprite1;
	void *sprite2;
	void *sprite3;
	void *sprite4;
}				t_mmlx;

typedef struct	s_dbint
{
	int a;
	int cot;
}				t_dbint;

typedef struct	s_posd
{
	double	x;
	double	y;
}				t_posd;

typedef struct	s_dposd
{
	t_posd	c;
	t_posd	d;
	int		cot;
}				t_dposd;

typedef struct	s_map
{
	int	**map;
	int slice;
	int	center_x;
	int	center_y;
	int	len;
	int	hgt;
	int distance;
}				t_map;

typedef struct	s_char
{
	t_pos	pos;
	double	direction;
}				t_char;

typedef struct	s_bigg
{
	t_image	img;
	t_mmlx	mlx;
	t_char	player;
	t_map	map;
	char	*name;
}				t_bigg;

void			init_big(t_bigg *big);

void			raycast(t_char player, t_map map, t_image *img);

char			*genl(char *filename);

/*
** Function for parsing. Completes the map given as a paraneter.
*/

void			*youpi(char *filename, t_map *map);

/*
**	Prints one pixel on pos in img. Colors are determined by
**	the first 3 ints in col. They are, in order, Blue Green and
**	Red. They range from 0 to 255.
*/
void			print_pixel(t_image *img, t_pos *pos, int *colo);

/*
**	Prints one pixel on pos in img. Color is based on
**	different settings, in order to make a good looking
**	fractol.
*/
void			print_pixelc(t_image *img, t_pos *pos, t_dposd *c, int slice);

/*
**	Creates the image img.
*/
void			window_creation(t_image *img, t_mmlx *mlx, t_bigg *big);

int				std_err(int err, t_map *map);

int				check_wall(t_pos pos, t_map map);

void			clean_map(t_image *img);

#endif
