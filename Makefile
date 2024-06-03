# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023\12\03 17:33:31 by oscarmathot       #+#    #+#              #
#    Updated: 2024\06\03 17:49:12 by oscarmathot      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------
#VARIABLES

NAME 	:= cub3d
SRC 	:= main.c helpers.c read_map.c file_checks.c initialize.c map_checks.c raycast.c utils.c \
			mlx.c player.c mouse.c texture.c player_helper.c filedata.c check_helper.c cnf.c \
			edge_verification.c map_checks_helper.c mlx_helper.c stack.c mlx_walls.c rgba.c \
			texture_init.c raycast_utils.c raycast_process.c raycast_handle_casses.c \
			free_helpers.c cub3d_split.c safe_checking.c safe_checking_help.c
SUBDIR	:= srcs\
SRCS	:= $(addprefix $(SUBDIR),$(SRC))
OBJ 	:= $(SRCS:.c=.o)
LIBFT_A	:= lib\libft\libft.a
MLX42_A	:= lib\MLX42\build\libmlx42.a
CMP		:= gcc
LDFLAGS = -mconsole -Wl,-e,mainCRTStartup
FLAGS 	:= -Werror -Wall -Wextra -g -Iinclude -lglfw3 -lopengl32 -lgdi32 #-fsanitize=address

#---------------------------------
#FORMATTING AND FUN

RED		:= \033[31m
GREEN 	:= \033[32m
YELLOW	:= \033[33m
BLUE	:= \033[38;5;87m
MAGENTA := \033[35m
CYAN	:= \033[36m
RESET	:= \033[0m

#---------------------------------
#RULES

all	: $(NAME)
		@echo "$(GREEN)Project built successfully !$(RESET)"
		@echo "$(BLUE)Usage: .\cub3d <map>$(RESET)"

$(NAME) : $(OBJ) $(LIBFT_A) $(MLX42_A) cub3d.h
		@echo "$(CYAN)Creating the executable...$(RESET)"
		$(CMP) $(OBJ) $(LIBFT_A) $(MLX42_A) $(FLAGS) $(OSFLAGS) $(LDFLAGS) -o $(NAME)

%.o : %.c cub3d.h
		@echo "$(CYAN)Compiling...$(RESET) $<"
		$(CMP) -c $(FLAGS) -o $@ $<

$(LIBFT_A) :
		@echo "$(BLUE)Building libft library...$(RESET)\n"
		make -C lib\libft

$(MLX42_A) :
		@echo "$(YELLOW)Building MLX42 library...$(RESET)"
		(cd .\lib\MLX42 && cmake -B build)
		(cd .\lib\MLX42 && cmake --build build -j4)

clean :
		@rm $(OBJ) .\lib\libft\libft.a
		@echo "$(GREEN)Cleaned up the artifacts !$(RESET)"

fclean :
		@rm $(NAME) $(OBJ)
		@echo "$(MAGENTA)Cleaned up executable !$(RESET)"

hardclean :
		@make fclean
		cd .\lib\libft
		make clean
		make fclean
		cd ..
		cd .\lib\MLX42 
		rm build
		@echo "$(MAGENTA)Cleaned up all built files!$(RESET)"

re : fclean all

.PHONY : clean fclean re hardclean
