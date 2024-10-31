/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:04:05 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/31 15:50:45 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../libft/libft.h"


void parse_map(char **file_lines, t_map *map)
{
    int i;
    int j;
	int k;
    int max_width;
	int map_start;

	i = 0;
	max_width = 0;
    while (file_lines[i] && !(file_lines[i][0] == '1' || file_lines[i][0] == '0'))
        i++;
		map_start = i;
    while (file_lines[i] && (file_lines[i][0] == '1' || file_lines[i][0] == '0'))
    {
        int current_width = ft_strlen(file_lines[i]);
        if (current_width > max_width)
            max_width = current_width;
        i++;
    }
    map->height = i - map_start;
    map->width = max_width;
    printf("Map dimensions: height=%d, width=%d\n", map->height, map->width);
    map->layout = malloc(sizeof(char *) * (map->height + 1));
    if (!map->layout)
		return;
	j = 0;
	while(j < map->height)
	{
		map->layout[j] = malloc(sizeof(char) * (map->width + 1));
        if (!map->layout[j])
            return;
		k = 0;
		while (k < map->width)
		{
			if (file_lines[map_start + j][k] != '\0' && file_lines[map_start + j][k] != '\n')
                map->layout[j][k] = file_lines[map_start + j][k];
            else
                map->layout[j][k] = ' ';
			k++;
		}
        map->layout[j][k] = '\0';
		j++;
	}
    map->layout[map->height] = NULL;
	//just for debugging
    printf("Map layout:\n");
    for (j = 0; j < map->height; j++)
    {
        printf("%s\n", map->layout[j]);
    }
}

int parse_color(const char *line, t_color *color)
{
	char **split;

	split = ft_split(line, ' ');
	if (split[0] && split[1])
		color->rgb = ft_atoi(split[1]);
	free_split(split);
	return (color->rgb);
}

void load_textures(t_game *game)
{
	int width;
	int height;
	game->texture.north[ft_strlen(game->texture.north) - 1] = '\0';
	game->texture.south[ft_strlen(game->texture.south) - 1] = '\0';
	game->texture.west[ft_strlen(game->texture.west) - 1] = '\0';
	game->texture.east[ft_strlen(game->texture.east) - 1] = '\0';
    game->texture.north_img = mlx_xpm_file_to_image(game->data.mlx, game->texture.north, &width, &height);
    game->texture.south_img = mlx_xpm_file_to_image(game->data.mlx, game->texture.south, &width, &height);
    game->texture.west_img = mlx_xpm_file_to_image(game->data.mlx, game->texture.west, &width, &height);
    game->texture.east_img = mlx_xpm_file_to_image(game->data.mlx, game->texture.east, &width, &height);
	game->texture.width = width;
	game->texture.height = height;
}

