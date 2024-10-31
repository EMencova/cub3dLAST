/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:42:39 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/28 23:06:47 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int can_move_to(t_game *game, int x, int y)
{
    char tile;
    
    tile = game->map.layout[y][x];
    return (tile == '0' || tile == 'S' || tile == 'N' || tile == 'E' || tile == 'W');
}

void move_y(t_game *game, char direction)
{
    double moveSpeed;
    
    moveSpeed = game->player.moveSpeed;  
    if (direction == 'N')
    {
        if (can_move_to(game, (int)(game->player.posX - game->player.dirX * moveSpeed), (int)game->player.posY))
            game->player.posX -= game->player.dirX * moveSpeed;

        if (can_move_to(game, (int)game->player.posX, (int)(game->player.posY - game->player.dirY * moveSpeed)))
            game->player.posY -= game->player.dirY * moveSpeed;
    }
    else if (direction == 'S')
    {
        if (can_move_to(game, (int)(game->player.posX + game->player.dirX * moveSpeed), (int)game->player.posY))
            game->player.posX += game->player.dirX * moveSpeed;

        if (can_move_to(game, (int)game->player.posX, (int)(game->player.posY + game->player.dirY * moveSpeed)))
            game->player.posY += game->player.dirY * moveSpeed;
    }
}

void move_x(t_game *game, char direction)
{
    double moveSpeed;
    
    moveSpeed = game->player.moveSpeed;
    if (direction == 'E')
    {
        if (can_move_to(game, (int)(game->player.posX - game->player.dirY * moveSpeed), (int)game->player.posY))
            game->player.posX -= game->player.dirY * moveSpeed;

        if (can_move_to(game, (int)game->player.posX, (int)(game->player.posY + game->player.dirX * moveSpeed)))
            game->player.posY += game->player.dirX * moveSpeed;
    }
    else if (direction == 'W')
    {
        if (can_move_to(game, (int)(game->player.posX + game->player.dirY * moveSpeed), (int)game->player.posY))
            game->player.posX += game->player.dirY * moveSpeed;

        if (can_move_to(game, (int)game->player.posX, (int)(game->player.posY - game->player.dirX * moveSpeed)))
            game->player.posY -= game->player.dirX * moveSpeed;
    }
}

void move_player(t_game *game, char direction)
{
	if (direction == 'N')
		move_y(game, direction);  
    else if (direction == 'S')
		move_y(game, direction);
	else if (direction == 'W')
		move_x(game, direction);
	else if (direction == 'E')
		move_x(game, direction);
}

void rotate_player(t_game *game, float angle)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = game->player.dirX;
    game->player.dirX = game->player.dirX * cos(angle) + game->player.dirY * sin(angle);
    game->player.dirY = -oldDirX * sin(angle) + game->player.dirY * cos(angle);
    oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * cos(angle) + game->player.planeY * sin(angle);
    game->player.planeY = -oldPlaneX * sin(angle) + game->player.planeY * cos(angle);
    raycasting(game);
}
