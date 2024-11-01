/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:21:36 by emencova          #+#    #+#             */
/*   Updated: 2024/11/01 22:38:38 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "colors.h"
# include "../libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/keysym.h>
# include <X11/X.h>

# define MEMORY_ERROR "Memory allocation failed"
# define INVALID_AC "Wrong number of arguments."
# define MAP_NAME "Invalid map name."
# define MAP_NOT_OPEN "Failed to open map file"
# define MAP_INVALID "Map validation failed"
# define EMPTY_MAP "Empty map file."
# define WRONG_EXT "Wrong file extension!! must be .cub"
# define MULT_PLAYER "Multiple player positions found in map"
# define NO_PLAYER "No player position found in map"
# define INVALID_CHAR "Invalid character in map"
# define COLOR_RANGE "Color values out of range."
# define COLOR_FORMAT "Color format incorrect."
# define WRONG_TEX "Wrong texture path."

# define TILE_SIZE     64
# define KEY_W         13
# define KEY_A         0
# define KEY_S         1
# define KEY_D         2
# define KEY_LEFT      123
# define KEY_RIGHT     124
# define KEY_ESC       53

# define WIDTH                  800
# define HEIGHT                 800
# define XPM_HEIGHT        64
# define XPM_WIDTH         64

# define MOVE_SPEED     0.1
# define ROTATE_SPEED   0.1
#define COLLISION       0.4


typedef struct s_ray
{
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    int stepX;
    int stepY;
    int side;
    double perpWallDist;
    int drawStart;
    int drawEnd;
}       t_ray;


typedef struct s_color
{
    int rgb;
}               t_color;

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int  bits_per_pixel;
    int  line_length;
    int  endian;
}              t_data;


typedef struct s_map
{
    char **layout;
    int width; 
    int height;
    int player_x;
    int player_y;
  //  char player_dir;
} t_map;

typedef struct s_player
{
    double posX;//Player X position
    double posY;
    double dirX;//Player X direction vector
    double dirY;
    double planeX;//Camera X plane vector (field of view)
    double planeY;//Camera Y plane vector (field of view)
    double moveSpeed;
    double rotSpeed;
}   t_player;

typedef struct s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
    int width;
    int height;
    void *north_img;
    void *south_img;
    void *west_img;
    void *east_img;
}               t_texture;

typedef struct s_game
{
    t_player player;
    int floor_color;
    int ceiling_color;
    t_texture texture;
    t_color color;
    t_map map;
    t_data  data;
}               t_game;


void load_map(const char *filename, t_game *game);
void parse_map(char **file_lines, t_map *map);
void parse_player(t_map *map, t_game *game);
char **read_file_cub(const char *filename);
int validate_player(t_map *map);
int validate_map(char **map_tab, int height);
int count_lines(const char *filename);
void free_file_lines(char **lines);
void free_split(char **split);
int parse_color(const char *line, t_color *color);
void move_y(t_game *game, char direction);
void move_x(t_game *game, char direction);
void move_player(t_game *game, char direction);
void rotate_player(t_game *game, float angle);
int is_valid_map_char(char c);
int check_row_border(char **map_tab, int row, int start);
int close_window(t_game *game);
int handle_key(int keycode, t_game *game);
void	game_init (t_game *game);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void raycasting(t_game *game);
void init_player(t_game *game, int x, int y, char direction);
int validate_input(t_map *map, char **av);
char	*get_next_line(int fd);
void	events_init(t_game *game);
void free_map(t_map *map);
void load_textures(t_game *game);
int get_cell_color(char cell, t_game *game);
void calculate_ray_direction(t_game *game, int x, double *rayDirX, double *rayDirY);
void initialize_dda(t_game *game, double rayDirX, double rayDirY, int *mapX, int *mapY, 
                    double *sideDistX, double *sideDistY, double *deltaDistX, double *deltaDistY, 
                    int *stepX, int *stepY);
double calculate_perpendicular_distance(t_game *game, int mapX, int mapY,
                                         double rayDirX, double rayDirY, int stepX, int stepY, int side);
int render_frame(t_game *game);
void render_player(t_data *data, t_game *game);
void clear_screen(t_data *data);
void draw_scaled_cell(t_data *data, int x, int y, int scale, int color);
void draw_floor_and_ceiling(t_game *game, int x, int drawStart, int drawEnd);
void draw_scene(t_game *game, int x, int drawStart, int drawEnd, int side);
void initialize_dda(t_game *game, double rayDirX, double rayDirY, int *mapX, int *mapY, 
                    double *sideDistX, double *sideDistY, double *deltaDistX, double *deltaDistY, 
                    int *stepX, int *stepY);
int perform_dda(t_game *game, int *mapX, int *mapY, double *sideDistX, double *sideDistY, 
                double deltaDistX, double deltaDistY, int stepX, int stepY);
void draw_vertical_line(t_game *game, int x, int drawStart, int drawEnd, void *texture);



#endif

