# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 13:15:17 by yfontene          #+#    #+#              #
#    Updated: 2024/11/01 12:25:12 by yasmine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN				=	\033[0;32m
RED					=	\033[0;31m
YELLOW				=	\033[0;33m
MAGENTA				=	\033[0;35m
CYAN				=	\033[0;36m
END					=	\033[0m


NAME = cub3d
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -f
MLX_DIR = minilibx-linux/
LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRCS=					main.c\
						./src/free.c\
						./src/parser.c\
						./src/parser_checks.c\
						./src/pasrse_in_out.c\
						./src/parser_utils.c\
						./src/render.c\
						./src/cmds.c\
						./src/moves.c\
						./src/map_raycast.c\
						./src/get_next_line.c\
						./src/get_next_line_utils.c\
						./src/player.c\
						./src/window_utils.c\
						./src/math.c\
						./src/init.c\
						./src/draws.c\
						./src/dda.c\
						
						
						
						
OBJS=					$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3D succesfully compiled! ✅$(END)"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
	
$(MLX):
	@make -sC $(MLX_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	@$(RM) $(OBJS) 
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
	@echo "$(RED)Cub3D deleted! 🚮$(END)"

re: fclean all

.PHONY: all clean fclean re
