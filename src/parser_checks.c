/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:48:37 by yfontene          #+#    #+#             */
/*   Updated: 2024/11/01 12:24:11 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../libft/libft.h"

int validate_map_borders(char **map_tab, int height)
{
    int row;
    int last;
	int left;

    if (check_row_border(map_tab, 0, 0) == 0 || check_row_border(map_tab, height - 1, 0) == 0)
        return (0);
    row = 0;
    while (row < height - 1)
    {
        left = 0;
        while (map_tab[row][left] == ' ' && map_tab[row][left] != '\0')
            left++;
        if (map_tab[row][left] != '1')
            return (0);
        last = ft_strlen(map_tab[row]) - 1;
        while (last > 0 && map_tab[row][last] == ' ')
            last--;
        if (map_tab[row][last] != '1')
            return (0);
        row++;
    }
    return (1);
}

int is_valid_player(char cell, int *player_count)
{
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		(*player_count)++;
		if (*player_count > 1)
		{
			printf("Error:\n"MULT_PLAYER"\n");
			return (0);
		}
	}
	return (1);
}

int validate_cell(char **map_tab, int row, int col, int *player_count)
{
	char cell;
	
	cell = map_tab[row][col];
	if (!is_valid_map_char(cell))
	{
		printf("Error:\n"INVALID_CHAR"\n");
		return (0);
	}
	if ((!is_valid_player(cell, player_count)))
		return (0);
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
				return (0);
			col++;
        }
		row++;
    }
    if (player_count != 1)
        return 0;

    return (1);
}


int validate_map(char **map_tab, int height)
{
    if (!validate_map_content(map_tab, height))
        return (0);
    return (1);
}
