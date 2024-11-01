/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:04:05 by yfontene          #+#    #+#             */
/*   Updated: 2024/11/01 13:16:05 by yasmine          ###   ########.fr       */
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
    //printf("Map dimensions: height=%d, width=%d\n", map->height, map->width);
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
	/*just for debugging
    printf("Map layout:\n");
    for (j = 0; j < map->height; j++)
    {
        printf("%s\n", map->layout[j]);
    }*/
}
int	parse_rgb(const char *str, t_color *color)
{
    char **rgb_split;
    int r;
    int g;
    int b;
    int rgb;

    rgb_split = ft_split(str, ',');
    if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2])
    {
        printf("Error:\n"COLOR_FORMAT"\n");
        exit(1);
    }
    r = ft_atoi(rgb_split[0]);
    g = ft_atoi(rgb_split[1]);
    b = ft_atoi(rgb_split[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error:\n"COLOR_RANGE"\n");
        free_split(rgb_split);
        exit(1);
    }
    rgb = (r << 16) | (g << 8) | b;
    color->rgb = rgb;
    free_split(rgb_split);
    return (color->rgb);
}

/*int parse_color(const char *line, t_color *color)
{
    char **split;

    split = ft_split(line, ' ');
    if (split[0] && split[1])
    {
        printf("Color: %s\n", split[1]);
        printf("color->rgb: %d\n", color->rgb);
        color->rgb = ft_parse_rgb(split[1], color);  // Usar a nova função de parsing
        //printf("Color RGB: (%d, %d, %d) -> RGB Integer: %d\n", color->r, color->g, color->b, color->rgb);
    }
    
    free_split(split);
    return (color->rgb);
}*/
int parse_color(const char *line, t_color *color)
{
	char **split;

	split = ft_split(line, ' ');
	if (split[0] && split[1])
		color->rgb = parse_rgb(split[1], color);
	free_split(split);
	return (color->rgb);
}

void check_texture_path(void *texture_img, const char *texture_path)
{
	if (!texture_img)
    {
		printf("Erro:\n"WRONG_TEX" <%s>\n", texture_path);
		exit(1);
	}
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
    if (!game->texture.north_img)
        check_texture_path(game->texture.north_img, game->texture.north);
    game->texture.south_img = mlx_xpm_file_to_image(game->data.mlx, game->texture.south, &width, &height);
    if (!game->texture.south_img)
        check_texture_path(game->texture.south_img, game->texture.south);
    game->texture.west_img = mlx_xpm_file_to_image(game->data.mlx, game->texture.west, &width, &height);
    if (!game->texture.west_img)
        check_texture_path(game->texture.west_img, game->texture.west);
    game->texture.east_img = mlx_xpm_file_to_image(game->data.mlx, game->texture.east, &width, &height);
    if (!game->texture.east_img)
    {
        check_texture_path(game->texture.east_img, game->texture.east);
    }
	game->texture.width = width;
	game->texture.height = height;
}

