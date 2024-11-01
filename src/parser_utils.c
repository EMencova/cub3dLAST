/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:22:20 by yasmine           #+#    #+#             */
/*   Updated: 2024/11/01 12:23:18 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int count_lines(const char *filename)
{
	int fd;
	int count;
	char *line;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf(MAP_NOT_OPEN);
		printf("\n");
		return (-1);
	}
	line = get_next_line(fd);
	while(line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' ||
			c == 'W' || c == ' ');
}

int check_row_border(char **map_tab, int row, int start)
{
    if (!map_tab || !map_tab[row] || !map_tab[row][start])
		return (0);
	while (map_tab[row][start] == ' ')
		start++;
    while (map_tab[row][start])
	{
        if (map_tab[row][start] != '1' && map_tab[row][start] != ' ')
            return (0);
        start++;
    }
    return (1);
}