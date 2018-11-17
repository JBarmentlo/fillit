/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:49:09 by gtaja             #+#    #+#             */
/*   Updated: 2018/11/14 15:49:09 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

int		main(int argc, char **argv)
{
	t_list	*map;

	if (argc != 2)
	{
		ft_putstr("usage: fillit description_file\n");
		return (0);
	}
	map = load_map(argv[1]);
	if (map == NULL)
	{
		ft_putstr("error\n");
		return (0);
	}
	while (map != NULL)
	{
		ft_matrix_show((t_matrix*)map->content);
		map = map->next;
	}
	/*
	** Manque encore a verifier si il y a + de 26 (ou 0) tetriminos
	** Max 4 # par tetriminos et qui ce touchent !
	*/
	return (0);
}
