/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:00:16 by emencova          #+#    #+#             */
/*   Updated: 2024/10/29 23:14:09 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void parse_player(t_map *map, t_game *game)
{
    int y;
    int x;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->layout[y][x] == 'N' || map->layout[y][x] == 'S' || 
                map->layout[y][x] == 'E' || map->layout[y][x] == 'W')
            {
                init_player(game, x, y, map->layout[y][x]); 
                return;
            }
            x++;
        }
        y++;
    }
}

void render_player(t_data *data, t_game *game)
{
    int scale;
    int playerX;
    int playerY;
    int i;
    int j;

    scale = 20;
    playerX = (int)(game->player.posX * scale);
    playerY = (int)(game->player.posY * scale);
    i = -scale / 2;  
    while (i < scale / 2)
    {
        j = -scale / 2;
        while (j < scale / 2) 
        {
            if (i * i + j * j <= (scale / 2) * (scale / 2))
                my_mlx_pixel_put(data, playerX + i, playerY + j, 0x00FF00);
            j++;
        }
        i++;
    }
}
