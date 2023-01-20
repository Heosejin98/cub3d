NAME = cub3d

CC = cc
CFLAGS =  -g

INCLUDES_DIR = includes
LIBS_DIR = libft 
SRCS_DIR = srcs

MLX_DIR 	= mlx
MLX  		= mlx/Makefile
MLX_LIB		= -lmlx -framework OpenGl -framework AppKit -Imlx

# srcs directory
PARSING_DIR = parsing
UTIL_DIR 	= util
ENGINE_DIR = engine

PARSING_SRCS	=	parsing_cub_file.c read_file.c parsing_texture_lines.c \
					parsing_rgb_lines.c parsing_map_lines.c validate_texture_lines.c \
					validate_rgb_lines.c validate_map.c check_needless_lines.c
				
UTIL_SRCS 		=	ft_split_isspace.c ft_free_strs.c ft_free_game.c \
					ft_error.c validate_arg.c ft_arr_to_hex.c

ENGINE_SRCS 	=	raycasting.c user_input.c game_set.c player_set.c raycast_set.c



LIBFT_DIR = libft
LIBFT = libft.a
LIBFT_LIB = -lft

SRCS = $(addprefix $(SRCS_DIR)/, main.c) \
	$(addprefix $(SRCS_DIR)/$(PARSING_DIR)/, $(PARSING_SRCS)) \
	$(addprefix $(SRCS_DIR)/$(UTIL_DIR)/, $(UTIL_SRCS)) \
	$(addprefix $(SRCS_DIR)/$(ENGINE_DIR)/, $(ENGINE_SRCS))

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_DIR) bonus
	make -C $(MLX_DIR)
	@$(CC) $(FLAGS) -I $(INCLUDES_DIR) -L $(LIBFT_DIR) $(LIBFT_LIB) -o $@ $^ $(MLX_LIB)

	
%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

clean :
	rm -rf $(OBJS)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re :
	make fclean
	make all

.PHONY = all clean fclean re