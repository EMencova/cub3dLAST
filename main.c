/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:29:05 by emencova          #+#    #+#             */
/*   Updated: 2024/11/01 12:19:29 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

int validate_input(t_map *map, char **av)
{
	if (validate_map(map->layout,map->height) == 0)
	{
		printf("Error:\n"MAP_INVALID"\n");
		return (0);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
    {
        printf("Error:\n"WRONG_EXT"\n");
        return (0);
    }
    return (1);
}


void cleanup_game(t_game *game)
{
    if (game->map.layout != NULL)
        free_map(&game->map);
    if (game->data.win)
        mlx_destroy_window(game->data.mlx, game->data.win);
    if (game->data.img)
        mlx_destroy_image(game->data.mlx, game->data.img);
    if (game->data.mlx)
    {
        mlx_destroy_display(game->data.mlx);
        free(game->data.mlx);
    }
}

int main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	load_map(av[1], &game);
	if (!validate_input(&game.map, av))
	{
		cleanup_game(&game);
        return (1);
	}
	game_init(&game);
	cleanup_game(&game);
    return (0);
}


