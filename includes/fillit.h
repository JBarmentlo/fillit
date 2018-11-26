/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 12:56:09 by gtaja             #+#    #+#             */
/*   Updated: 2018/11/17 12:56:09 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

t_list	*load_map(char *filename);

/*
** tools.c
*/
void	ft_exit_error(void);
void	ft_clearblocks(t_list *ls);
t_matrix    *ft_resolve(t_list *blocks, int iter);
void ft_show_soluce(t_matrix *map);

#endif
