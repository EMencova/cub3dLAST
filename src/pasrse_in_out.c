/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasrse_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:24:30 by yfontene          #+#    #+#             */
/*   Updated: 2024/11/01 20:06:54 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


char **read_file_cub(const char *filename)
{
	int fd;
	int nbr_line;
	int i;
	char *line;
	char **file;

	nbr_line = count_lines(filename);
	if (nbr_line == -1)
		return (NULL);
	file = malloc(sizeof(char *) * (nbr_line + 1));
	if (!file)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(file);
		return (NULL);
	}
	i = 0;
	while (nbr_line > 0)
	{
		line = get_next_line(fd);
		if (!line)
        	break;
		file[i] = line;
		i++;
		nbr_line--;
	}
	file[i] = NULL;
	close(fd);
	return (file);
}

void free_trimmed(char **file_lines)
{
	int i;

	i = 0;
	while (file_lines[i])
	{
		free(file_lines[i]);
		i++;
	}
	free(file_lines);
}

void load_map(const char *filename, t_game *game)
{
	char **file_lines;
	int i;

	file_lines = read_file_cub(filename);
	if (!file_lines)
	{
		printf("MAP_FILE\n");
		return ;
	}
	game->data.mlx = mlx_init();
    if (!game->data.mlx)
		exit(1);
	parse_map(file_lines, &game->map);
	parse_player(&game->map, game);
	i = 0;
	while (file_lines[i])
	{
		if (ft_strncmp(file_lines[i], "F", 1) == 0)
			game->floor_color = parse_color(file_lines[i], &game->color);
		else if (ft_strncmp(file_lines[i], "C", 1) == 0)
			game->ceiling_color = parse_color(file_lines[i], &game->color);
		else if (ft_strncmp(file_lines[i], "NO", 2) == 0)
            game->texture.north = ft_strtrim(file_lines[i] + 2, " ");
        else if (ft_strncmp(file_lines[i], "SO", 2) == 0)
            game->texture.south = ft_strtrim(file_lines[i] + 2, " ");
        else if (ft_strncmp(file_lines[i], "WE", 2) == 0)
            game->texture.west = ft_strtrim(file_lines[i] + 2, " ");
        else if (ft_strncmp(file_lines[i], "EA", 2) == 0)
            game->texture.east = ft_strtrim(file_lines[i] + 2, " ");
		i++;
	}
	load_textures(game);
	free_file_lines(file_lines);
}