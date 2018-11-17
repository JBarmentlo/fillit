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
#include <fcntl.h>

static void		ft_exit(void)
{
	ft_putstr("error\n");
	exit(0);
}

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
			ft_exit();
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
			ft_exit();
		}
	}
	if (i != 4)
	{
		ft_matrix_free(&block);
		if (len != 0)
			ft_exit();
		return (NULL);
	}
	return (ft_matrix_reduce(&block));
}

static void		ft_clearlist(t_list *ls)
{
	t_list	*temp;

	while (ls != NULL)
	{
		temp = ls->next;
		ft_matrix_free((t_matrix**)(&ls->content));
		free(ls);
		ls = temp;
	}
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

	result = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	while ((block = ft_readblock(fd)) != NULL)
	{
		ft_readline(fd, &line);
		if (line == NULL || ft_strlen(line) != 0 || block == NULL)
		{
			ft_clearlist(result);
			return (NULL);
		}
		ft_lstpushback(&result, ft_lstitem((void*)block, sizeof(t_matrix)));
	}
	close(fd);
	return (result);
}
