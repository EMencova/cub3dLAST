/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:17:50 by emencova          #+#    #+#             */
/*   Updated: 2024/10/31 15:37:18 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double calculate_perpendicular_distance(t_game *game, int mapX, int mapY, 
                                         double rayDirX, double rayDirY, int stepX, 
                                         int stepY, int side)
{
    double perpWallDist;


    if (side == 1 || side == 2)
    {
        perpWallDist = (mapX - game->player.posX + (1 - stepX) / 2) / rayDirX;
    }
    else
    {
        perpWallDist = (mapY - game->player.posY + (1 - stepY) / 2) / rayDirY;
    }

    return perpWallDist;
}


void calculate_ray_direction(t_game *game, int x, double *rayDirX, double *rayDirY)
{
    double cameraX = 2 * x / (double)WIDTH - 1;
    *rayDirX = game->player.dirX + game->player.planeX * cameraX;
    *rayDirY = game->player.dirY + game->player.planeY * cameraX;
}

