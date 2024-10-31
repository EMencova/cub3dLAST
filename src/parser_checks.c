/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:48:37 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/31 15:51:42 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../libft/libft.h"

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
	printf("inside check row border\n");
    if (!map_tab || !map_tab[row] || !map_tab[row][start])
	{
		printf("inside if check row border\n");
		return (0);
	}
	while (map_tab[row][start] == ' ')
	{
		start++;
		printf("firt while in row)border");
	}
    while (map_tab[row][start])
	{
        if (map_tab[row][start] != '1' && map_tab[row][start] != ' ')
            return (0);
        start++;
		printf("start %d\n", start);
    }
    return (1);
}

int validate_map_borders(char **map_tab, int height)
{
    int row;
    int last;

    printf("inside validate map borders\n");
    if (check_row_border(map_tab, 0, 0) == 0 || check_row_border(map_tab, height - 1, 0) == 0)
    {
        printf("check row border inside validate_map_borders\n");//debbug
        return (0);
    }
    row = 0;
    while (row < height - 1)
    {
        printf("inside while validate map borders\n");
		int left;
        
        left = 0;
        while (map_tab[row][left] == ' ' && map_tab[row][left] != '\0')
            left++;
        if (map_tab[row][left] != '1')
        {
            printf("Error in row %d: left border is not '1'\n", row);
            return (0);
        }
        last = ft_strlen(map_tab[row]) - 1;
        while (last > 0 && map_tab[row][last] == ' ')
            last--;
        if (map_tab[row][last] != '1')
        {
            printf("Error in row %d: right border is not '1' (right: %c)\n", row, map_tab[row][last]);//debuug
            return (0);
        }
        
        row++;
    }
    return (1);
}

int is_valid_player(char cell, int *player_count)
{
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		(*player_count)++;
		printf("Player count incremented: %d\n", *player_count);
		if (*player_count > 1)
			return (0);
		printf("player count %d\n", *player_count);
	}
	return (1);
}

int validate_cell(char **map_tab, int row, int col, int *player_count)
{
	char cell;
	
	cell = map_tab[row][col];
	if (!is_valid_map_char(cell))
	{
		printf("Invalid map character: '%c'\n", cell);
    	return (0);
	}
	if ((!is_valid_player(cell, player_count)))
	{
		printf("Error: Expected exactly one player, found %d\n", *player_count);
		return (0);
	}
	return (1);
}

int validate_map_content(char **map_tab, int height)
{
    int player_count;
    int width;
	size_t row;
	size_t col;
	
	player_count = 0;
	row = 0;
	while (row < (size_t)height)
    {
        width = ft_strlen(map_tab[row]);
		col = 0;
		while (col < (size_t)width - 1)
        {
            if (!validate_cell(map_tab, row, col, &player_count))
			{
				printf("error in validate cell\n");
				return (0);
			}
			col++;
        }
		row++;
    }
    if (player_count != 1)
    {
        printf("Error: Expected exactly one player, found %d\n", player_count);
        return 0;
    }
    return (1);
}


int validate_map(char **map_tab, int height)
{
    if (!validate_map_content(map_tab, height))
        return (0);
    return (1);
}
