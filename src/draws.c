/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:14:46 by yfontene          #+#    #+#             */
/*   Updated: 2024/11/01 18:16:06 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int get_cell_color(char cell, t_game *game)
{
    int color;
    if (cell == '2')
        color = game->ceiling_color;
    else
        color = game->floor_color;
    return (color);
}


void draw_scaled_cell(t_data *data, int x, int y, int scale, int color)
{
    int i = 0;
    while (i < scale)
    {
        int j = 0;
        while (j < scale)
        {
            my_mlx_pixel_put(data, (x * scale) + j, (y * scale) + i, color);
            j++;
        }
        i++;
    }
}

void draw_floor_and_ceiling(t_game *game, int x, int drawStart, int drawEnd)
{
    int floorColor;
    int ceilingColor;
    int y;

    floorColor = get_cell_color('1', game);
    ceilingColor = get_cell_color('2', game);

    y = 0;
    while (y < drawStart)
    {
        mlx_pixel_put(game->data.mlx, game->data.win, x, y, ceilingColor);
        y++;
    }
    y = drawEnd;
    while (y < HEIGHT)
    {
        mlx_pixel_put(game->data.mlx, game->data.win, x, y, floorColor);
        y++;
    }
}


void draw_vertical_line(t_game *game, int x, int drawStart, int drawEnd, void *texture)
{
    int y;
    int textureX;
    int textureY;
    int color;
    int bpp;
    int size_line;
    char *data_addr;
    int endian;

    data_addr = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
    textureX = (x % game->texture.width);
    y = drawStart;
    while (y <= drawEnd)
    {
        textureY = (y - drawStart) * game->texture.height / (drawEnd - drawStart);  
        if (textureY >= 0 && textureY < game->texture.height) {
            color = *(int *)(data_addr + textureY * size_line + textureX * (bpp / 8));
            
            if (y >= 0 && y < HEIGHT)
                mlx_pixel_put(game->data.mlx, game->data.win, x, y, color);
        }
        y++;
    }
}
/*void draw_vertical_line(t_game *game, int x, int drawStart, int drawEnd, void *texture, double perpWallDist)
{
    int y;
    int textureX;
    int textureY;
    int color;
    int bpp;
    int size_line;
    char *data_addr;
    int endian;
    
    data_addr = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
    textureX = (x % game->texture.width);
    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
    int lineHeight = (int)(HEIGHT / perpWallDist);
    drawStart = HEIGHT / 2 - lineHeight / 2;
    drawEnd = drawStart + lineHeight;
    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
    for (y = drawStart; y <= drawEnd; y++)
    {
        textureY = (y - drawStart) * game->texture.height / lineHeight;
        if (textureY >= 0 && textureY < game->texture.height)
        {
            color = *(int *)(data_addr + textureY * size_line + textureX * (bpp / 8));
            if (y >= 0 && y < HEIGHT)
                mlx_pixel_put(game->data.mlx, game->data.win, x, y, color);
        }
    }
}*/
