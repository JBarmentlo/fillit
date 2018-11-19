/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:51:00 by gtaja             #+#    #+#             */
/*   Updated: 2018/11/19 10:51:00 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

void	ft_clearblocks(t_list *ls)
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
