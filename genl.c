/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_crea.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 16:05:17 by sderet            #+#    #+#             */
/*   Updated: 2018/02/06 16:09:39 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "minilibx/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		gnl_lite(int fd, char **line)
{
	int		rd;
	char	buff[BUFF_SIZE + 1];

	if ((rd = read(fd, buff, BUFF_SIZE)) == -1)
		return (-1);
	*line = ft_strjoin(buff, "");
	(*line)[rd] = '\0';
	return (rd);
}

char	*genl(char *filename)
{
	int		fd;
	int		err;
	char	*tmp;
	char	*tab;
	char	*line;

	tab = "";
	if (!(fd = open(filename, O_RDONLY)))
		return (NULL);
	while ((err = gnl_lite(fd, &line)) > 0)
	{
		tmp = tab;
		tab = ft_strjoin(tab, line);
		(*tmp != 0 ? (free(tmp)) : (tmp = tmp + 1 - 1));
		(*line != 0 ? (free(line)) : (line = line + 1 - 1));
	}
	free(line);
	if (*tab != '\0' && tab[ft_strlen(tab) - 1] != '\n')
	{
		tmp = tab;
		tab = ft_strjoin(tab, "\n");
		(*tmp != 0 ? (free(tmp)) : (tmp = tmp + 1 - 1));
	}
	return ((err != 0 ? NULL : tab));
}
