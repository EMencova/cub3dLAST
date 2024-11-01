/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:27:45 by yfontene          #+#    #+#             */
/*   Updated: 2024/11/01 22:40:10 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void events_init(t_game *game)
{
    mlx_hook(game->data.win, KeyPress, KeyPressMask, handle_key, game);
    mlx_hook(game->data.win, DestroyNotify, StructureNotifyMask, close_window, game);
}

void free_map(t_map *map)
{
    int i;

    i = 0;
    while (i < map->height)
    {
        free(map->layout[i]);
        i++;
    }
    free(map->layout);
    map->layout = NULL;
}

int close_window(t_game *game)
{
    if (game->map.layout)
        free_map(&game->map);
    if (game->texture.north_img)
    {
        mlx_destroy_image(game->data.mlx, game->texture.north_img);
        game->texture.north_img = NULL;
    }
    if (game->texture.south_img)
    {
        mlx_destroy_image(game->data.mlx, game->texture.south_img);
        game->texture.south_img = NULL;
    }
    if (game->texture.west_img)
    {
        mlx_destroy_image(game->data.mlx, game->texture.west_img);
        game->texture.west_img = NULL;
    }
    if (game->texture.east_img)
    {
        mlx_destroy_image(game->data.mlx, game->texture.east_img);
        game->texture.east_img = NULL;
    }
    if (game->data.win)
    {
        mlx_clear_window(game->data.mlx, game->data.win);
        mlx_destroy_window(game->data.mlx, game->data.win);
    }
    if (game->data.img)
        mlx_destroy_image(game->data.mlx, game->data.img); 
    if (game->data.mlx)
    {
        mlx_destroy_display(game->data.mlx);
        free(game->data.mlx);
    }
    exit(0);
}


int handle_key(int keycode, t_game *game)
{
    if (keycode == XK_Escape)
        close_window(game);
    if (keycode == XK_w)
        move_player(game, 'S');
    if (keycode == XK_a)
        move_player(game, 'W');
    if (keycode == XK_Right)
        rotate_player(game, -game->player.rotSpeed);
    if (keycode == XK_Left)
        rotate_player(game, game->player.rotSpeed);
    if (keycode == XK_s)
        move_player(game, 'N');
    if (keycode == XK_d)
        move_player(game, 'E');
    raycasting(game);
    return (0);
}
