/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:29:05 by emencova          #+#    #+#             */
/*   Updated: 2024/10/31 15:20:44 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

int validate_input(t_map *map, char **av)
{
	if (validate_map(map->layout,map->height) == 0)
	{
		printf("ERROR\n"MAP_INVALID"\n");
		return (0);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
    {
        printf("WRONG_EXTENSION\n");
        return (0);
    }
    return (1);
}

void cleanup_game(t_game *game)
{
    if (game->map.layout != NULL)
		free_map(&game->map);
}

int main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	load_map(av[1], &game);
	//printf("ceiling %d and floor %d\n", game.ceiling_color,game.floor_color);
	//init_color(&game,av[1]);
	//get_cell_color(av[1], &game);
	if (!validate_input(&game.map, av))
	{
		cleanup_game(&game);
        return (1);
	}
	game_init(&game);
	cleanup_game(&game);
    return (0);
}


