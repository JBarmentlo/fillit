/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 12:56:56 by gtaja             #+#    #+#             */
/*   Updated: 2018/11/17 12:56:56 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdio.h>

static int		ft_fill_block_line(t_matrix *block, char *line, int y)
{
	unsigned int x;

	x = 0;
	while (x < block->width)
	{
		if (line[x] == '.')
			block->data[x][y] = 0;
		else if (line[x] == '#')
			block->data[x][y] = 1;
		else
			ft_exit_error();
		x++;
	}
	return (1);
}

static t_matrix	*ft_readblock(int fd)
{
	t_matrix	*block;
	int			i;
	char		*line;
	int			len;

	i = -1;
	if (!(block = ft_matrix_create(4, 4)))
		return (NULL);
	while (++i < 4 && (len = ft_readline(fd, &line)) > 0)
	{
		if (ft_strlen(line) != 4 || !ft_fill_block_line(block, line, i))
		{
			free(line);
			ft_matrix_free(&block);
			ft_exit_error();
		}
	}
	if (i != 4)
	{
		ft_matrix_free(&block);
		if (len != 0)
			ft_exit_error();
		return (NULL);
	}
	return (ft_matrix_reduce(&block));
}

static t_list	*ft_clearlist(t_list *ls, void **ptr1, void **ptr2)
{
	ft_clearblocks(ls);
	ft_memdel(ptr1);
	ft_memdel(ptr2);
	ft_exit_error();
	return (NULL);
}

static int		is_valid_block(t_matrix *block)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	count;

	if (!(count = 0) && block == NULL)
		return (0);
	x = 0;
	while (x < block->width)
	{
		y = 0;
		while (y < block->height)
		{
			if (block->data[x][y] == 1)
			{
				if ((++count) && (x == 0 || block->data[x - 1][y] != 1)
					&& (y == 0 || block->data[x][y - 1] != 1)
					&& (x == block->width - 1 || block->data[x + 1][y] != 1)
					&& (y == block->height - 1 || block->data[x][y + 1] != 1))
					return (0);
			}
			y++;
		}
		x++;
	}
	return (count == 4);
}

/*
** Retourne une t_list avec un content de type t_matrix
*/

t_list			*load_map(char *filename)
{
	int			fd;
	t_list		*result;
	t_matrix	*block;
	char		*line;
	int			count;

	result = NULL;
	count = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	while ((block = ft_readblock(fd)) != NULL)
	{
		ft_readline(fd, &line);
		if (line == NULL || ft_strlen(line) != 0 || !is_valid_block(block))
			return (ft_clearlist(result, (void**)(&line), (void**)(&block)));
		ft_memdel((void**)(&line));
		ft_lstpushback(&result, ft_lstitem((void*)block, sizeof(t_matrix)));
		count++;
	}
	close(fd);
	if (count > 26 || count <= 0)
		return (ft_clearlist(result, NULL, NULL));
	return (result);
}
