NAME		= cub3D

SRCS		= main.c parse.c parse_map.c parse_elements.c utils1.c utils2.c validate.c key_hook.c key_hook_2.c dda.c dda_2.c
OBJS		= $(SRCS:.c=.o)
CC			= gcc -Wall -Werror -Wextra
RM			= rm -rf

LIBFT		= libft/libft.a
LIBFT_DIR = ./libft
LIBMLX = mlx/libmlx.a
LIBMLX_DIR = ./mlx

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	@$(CC) $(OBJS) -o $(NAME) $(LIBFT) $(LIBMLX) -framework OpenGL -framework AppKit

$(LIBFT):
	@make bonus -C $(LIBFT_DIR) --silent

$(LIBMLX):
	@make -C $(LIBMLX_DIR) --silent

clean:
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR) --silent

norme:
	@norminette -R CheckForbiddenSourceHeader *.c *.h

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR) --silent
	@make clean -C $(LIBMLX_DIR) --silent

re:			fclean all

.PHONY:		all clean fclean re