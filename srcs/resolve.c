#include "libft.h"
#include <stdio.h>

static int  ft_place_block(t_matrix *map, t_matrix *block, unsigned int pos)
{
    int x;
    int y;
    int **tetris;
    int i;
    int j;

    x = pos % map->width;
    y = pos / map->width;
    tetris = block->data;

    if (x + block->width >= map->width ||
        y + block->height >= map->height)
        return (0);
    i = -1;
    while (++i < (int)block->width)
    {
        j = -1;
        while (++j < (int)block->height)
            if (tetris[i][j] != 0 && map->data[x + i][y + j] != 0)
                return (0);
    }

    i = -1;
    while (++i < (int)block->width)
    {
        j = -1;
        while (++j < (int)block->height)
            map->data[x + i][y + j] = tetris[i][j];
    }
    return (1);
}

static int  ft_del_block(t_matrix *map, t_matrix *block, unsigned int pos)
{
    int x;
    int y;
    int **tetris;
    int i;
    int j;

    x = pos % map->width;
    y = pos / map->width;
    tetris = block->data;

/*
    if (x + block->width >= map->width ||
        y + block->height >= map->height)
        return (0);
*/
    i = -1;
    while (++i < (int)block->width)
    {
        j = -1;
        while (++j < (int)block->height)
            map->data[x + i][y + j] = 0;
    }
    return (1);
}

int         ft_resolve_rec(t_matrix *map, t_list *blocks, unsigned int pos)
{
    printf("1 = %p\n", map);
    if (pos > map->width * map->height)
        return (0);
    printf("2\n");
    if (ft_place_block(map, (t_matrix*)blocks->content, pos))
    {
        printf("3\n");
        if (ft_resolve_rec(map, blocks->next, pos + 1))
            return (1);
        else
            ft_del_block(map, (t_matrix*)blocks->content, pos);
            printf("4\n");
    }
    printf("5\n");
    if (ft_resolve_rec(map, blocks, pos + 1))
        return (1);
    printf("6\n");
    return (0);
}

t_matrix    *ft_resolve(t_list *blocks, int iter)
{
    t_matrix    *map;
    int         count_block;
    t_list      *it;
    int         size;

    size = 0;
    it = blocks;
    count_block = 0;
    while (it != NULL)
    {
        count_block++;
        it = it->next;
    }
    while (size * size <= count_block * 4)
        size++;
    size += iter;
    map = ft_matrix_create(size, size);
    if (ft_resolve_rec(map, blocks, 0))
        return (map);
    ft_matrix_free(&map);
    return (ft_resolve(blocks, iter + 1));
}

char        ft_pow_to_char(int  nb)
{
    int i;

    i = 0;
    while (nb != 1)
    {
        nb = nb / 2;
        i++;
    }
    return (i + 'A');
}

void ft_show_soluce(t_matrix *map)
{
    unsigned int x;
    unsigned int y;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->data[x][y] == 0)
                ft_putchar('.');
            else
                ft_putchar(ft_pow_to_char(map->data[x][y]));
            x++;
        }
        y++;
    }
}
