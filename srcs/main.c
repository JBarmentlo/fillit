/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:49:09 by gtaja             #+#    #+#             */
/*   Updated: 2018/11/26 15:15:01 by jbarment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

int		main(int argc, char **argv)
{
	t_list		*blocks;
	t_matrix    *map;

	if (argc != 2)
	{
		ft_putstr("usage: fillit description_file\n");
		return (0);
	}
	if (!(blocks = load_map(argv[1])))
		write(1, "error\n", 6);
	/*while (blocks != NULL)
	{
		ft_matrix_show((t_matrix*)blocks->content);
		blocks = blocks->next;
	}*/
	map = ft_resolve(blocks, 0);
	ft_show_soluce(map);
	ft_matrix_free(&map);
	return (0);
}
