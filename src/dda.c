/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:14:46 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/31 15:42:26 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void calculate_delta_distance(double rayDirX, double rayDirY, double *deltaDistX, double *deltaDistY)
{
    if (rayDirX == 0)
        *deltaDistX = 1e30;
    else
        *deltaDistX = fabs(1 / rayDirX);

    if (rayDirY == 0)
        *deltaDistY = 1e30;
    else
        *deltaDistY = fabs(1 / rayDirY);
}

void calculate_step_and_side_dist(t_game *game, double rayDirX, double rayDirY, int *mapX, int *mapY, 
                                   double deltaDistX, double deltaDistY, int *stepX, int *stepY, 
                                   double *sideDistX, double *sideDistY)
{
    if (rayDirX < 0)
    {
        *stepX = -1;
        *sideDistX = (game->player.posX - *mapX) * deltaDistX;
    }
    else
    {
        *stepX = 1;
        *sideDistX = (*mapX + 1.0 - game->player.posX) * deltaDistX;
    }

    if (rayDirY < 0)
    {
        *stepY = -1;
        *sideDistY = (game->player.posY - *mapY) * deltaDistY;
    }
    else
    {
        *stepY = 1;
        *sideDistY = (*mapY + 1.0 - game->player.posY) * deltaDistY;
    }
}

void initialize_dda(t_game *game, double rayDirX, double rayDirY, int *mapX, int *mapY, 
                    double *sideDistX, double *sideDistY, double *deltaDistX, double *deltaDistY, 
                    int *stepX, int *stepY)
{
    calculate_delta_distance(rayDirX, rayDirY, deltaDistX, deltaDistY);
    calculate_step_and_side_dist(game, rayDirX, rayDirY, mapX, mapY, 
                                  *deltaDistX, *deltaDistY, stepX, stepY, 
                                  sideDistX, sideDistY);
}

int perform_dda(t_game *game, int *mapX, int *mapY, double *sideDistX, double *sideDistY, 
                double deltaDistX, double deltaDistY, int stepX, int stepY)
{
    int hit;
    int side;
    
    hit = 0;
    side = -1;
    while (hit == 0)
    {
        if (*sideDistX < *sideDistY)
        {
            *sideDistX += deltaDistX;
            *mapX += stepX;
            if (stepX == -1)
                side = 2;
            else
                side = 1;
        }
        else
        {
            *sideDistY += deltaDistY;
            *mapY += stepY;
            if (stepY == -1)
                side = 3;
            else
                side = 4;
        }
        if (game->map.layout[*mapY][*mapX] == '1')
            hit = 1;
    }
    return (side);
}

