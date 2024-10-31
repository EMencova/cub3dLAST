/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:14:46 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/31 15:47:06 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void initialize_ray(t_game *game, int x, double *rayDirX, double *rayDirY, 
                    int *mapX, int *mapY, double *sideDistX, double *sideDistY,
                    double *deltaDistX, double *deltaDistY, int *stepX, int *stepY)
{
    calculate_ray_direction(game, x, rayDirX, rayDirY);
    *mapX = (int)game->player.posX;
    *mapY = (int)game->player.posY;
    
    initialize_dda(game, *rayDirX, *rayDirY, mapX, mapY, sideDistX, sideDistY,
                   deltaDistX, deltaDistY, stepX, stepY);
}

void calculate_draw_positions(double perpWallDist, int *drawStart, int *drawEnd)
{
    int lineHeight;

    lineHeight = (int)(HEIGHT / perpWallDist);
    *drawStart = (-lineHeight / 2 + HEIGHT / 2);
    *drawEnd = (lineHeight / 2 + HEIGHT / 2);
    if (*drawStart < 0)
        *drawStart = 0;
    if (*drawEnd >= HEIGHT)
        *drawEnd = HEIGHT - 1;
}

int perform_raycasting(t_game *game, int x, t_ray *ray)
{
    initialize_ray(game, x, &ray->rayDirX, &ray->rayDirY, 
                   &ray->mapX, &ray->mapY, &ray->sideDistX, 
                   &ray->sideDistY, &ray->deltaDistX, 
                   &ray->deltaDistY, &ray->stepX, &ray->stepY);

    return (perform_dda(game, &ray->mapX, &ray->mapY, 
                       &ray->sideDistX, &ray->sideDistY, 
                       ray->deltaDistX, ray->deltaDistY, 
                       ray->stepX, ray->stepY));
}

void draw_scene(t_game *game, int x, int drawStart, int drawEnd, int side)
{
    if (side == 1)
        draw_vertical_line(game, x, drawStart, drawEnd, game->texture.north_img);
    else if (side == 2)
        draw_vertical_line(game, x, drawStart, drawEnd, game->texture.south_img);
    else if (side == 3)
        draw_vertical_line(game, x, drawStart, drawEnd, game->texture.east_img);
    else if (side == 4)
        draw_vertical_line(game, x, drawStart, drawEnd, game->texture.west_img);
    draw_floor_and_ceiling(game, x, drawStart, drawEnd);
}

void raycasting(t_game *game)
{
    t_ray ray;
    int x = 0;
    while (x < WIDTH)
    {
        ray.side = perform_raycasting(game, x, &ray); 
        ray.perpWallDist = calculate_perpendicular_distance(
            game, ray.mapX, ray.mapY, ray.rayDirX, ray.rayDirY, ray.stepX, ray.stepY, ray.side);
        calculate_draw_positions(ray.perpWallDist, &ray.drawStart, &ray.drawEnd);
        draw_scene(game, x, ray.drawStart, ray.drawEnd, ray.side);
        x++;
    }
}

