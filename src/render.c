/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:22:27 by yfontene          #+#    #+#             */
/*   Updated: 2024/11/01 21:52:40 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int render_frame(t_game *game)
{
    clear_screen(&game->data);
    parse_player(&game->map, game);
    render_player(&game->data, game);
    mlx_put_image_to_window(game->data.mlx, game->data.win, game->data.img, 0, 0);
    return (0);
}