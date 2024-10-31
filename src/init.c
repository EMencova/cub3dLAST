/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:24:10 by emencova          #+#    #+#             */
/*   Updated: 2024/10/31 15:57:24 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void player_ns_dir(t_game *game, char dir)
{
    if (dir == 'N')
    {
        game->player.dirX = 0;
        game->player.dirY = -1;
        game->player.planeX = 0.66;
        game->player.planeY = 0;
    }
    else if (dir == 'S')
    {
        game->player.dirX = 0;
        game->player.dirY = 1;
        game->player.planeX = -0.66;
        game->player.planeY = 0;
    }
}

void player_ew_dir(t_game *game, char dir)
{
    if (dir == 'E')
    {
        game->player.dirX = 1;
        game->player.dirY = 0;
        game->player.planeX = 0;
        game->player.planeY = 0.66;
    }
    else if (dir == 'W')
    {
        game->player.dirX = -1;
        game->player.dirY = 0;
        game->player.planeX = 0;
        game->player.planeY = -0.66;
    }
}

void init_player(t_game *game, int x, int y, char direction)
{
    game->player.posX = x;
    game->player.posY = y;

    if (game->map.layout[(int)game->player.posX + 1][(int)(game->player.posY)] == '1' ||
        game->map.layout[(int)game->player.posX - 1][(int)(game->player.posY)] == '1' ||
        game->map.layout[(int)game->player.posX][(int)(game->player.posY) + 1] == '1' ||
        game->map.layout[(int)game->player.posX][(int)(game->player.posY) - 1] == '1')
    {
        game->player.posX += 0.2;
        game->player.posY += 0.2;
    }
    if (direction == 'N' || direction == 'S')
        player_ns_dir(game, direction);
    else if (direction == 'E' || direction == 'W')
        player_ew_dir(game, direction);

    game->player.moveSpeed = MOVE_SPEED;
    game->player.rotSpeed = ROTATE_SPEED;
}

void game_init(t_game *game)
{
    game->data.mlx = mlx_init();
    if (!game->data.mlx)
        exit(1);
    game->data.win = mlx_new_window(game->data.mlx, WIDTH, HEIGHT, "Cub3D");
    if (!game->data.win) {
        mlx_destroy_display(game->data.mlx);
        free(game->data.mlx);
        exit(1);
    }
    game->data.img = mlx_new_image(game->data.mlx, WIDTH, HEIGHT);
    if (!game->data.img) {
        mlx_destroy_window(game->data.mlx, game->data.win);
        mlx_destroy_display(game->data.mlx);
        free(game->data.mlx);
        exit(1);
    }
    game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel,
                                        &game->data.line_length, &game->data.endian);
    render_frame(game);
    raycasting(game);
    events_init(game);
    mlx_loop(game->data.mlx);
}
