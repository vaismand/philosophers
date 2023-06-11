CFLAGS    = -Wall -Wextra -Werror
NAME      = so_long
NAME_BONUS = so_long_bonus
SRCS := $(wildcard src/*.c)
SRCS_BONUS := $(wildcard src_bonus/*.c)
OBJS := $(SRCS:.c=.o)
OBJS_BONUS := $(SRCS_BONUS:.c=.o)
CC        = gcc -g
RM        = rm -f
LIBFT     = ./lib/libft/libft.a
FT_PRINTF = ./lib/ft_printf/libftprintf.a
MLX_DIR   = ./mlx-linux
MLX_LIB   = $(MLX_DIR)/libmlx.a
MLX_INC   = -I$(MLX_DIR)

RED       = \033[0;91m
GREEN     = \033[1;92m
BLUE      = \033[0;94m

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -s -C ./lib/libft > /dev/null
	@${MAKE} -s -C ./lib/ft_printf > /dev/null
	@${MAKE} -s -C $(MLX_DIR) > /dev/null
	@${CC} ${CFLAGS} ${OBJS} -L$(MLX_DIR) ${MLX_INC} -lmlx -lXext -lX11 -lm -lz -o ${NAME} ${LIBFT} ${FT_PRINTF} > /dev/null
	@echo "${GREEN}Compilation is done!"

${NAME_BONUS}: ${OBJS_BONUS}
	@${MAKE} -s -C ./lib/libft > /dev/null
	@${MAKE} -s -C ./lib/ft_printf > /dev/null
	@${MAKE} -s -C $(MLX_DIR) > /dev/null
	@${CC} ${CFLAGS} ${OBJS_BONUS} -L$(MLX_DIR) ${MLX_INC} -lmlx -lXext -lX11 -lm -lz -o ${NAME_BONUS} ${LIBFT} ${FT_PRINTF} > /dev/null
	@echo "${GREEN}Bonus Compilation is done!"

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${MLX_INC}

fclean: clean
	@${RM} ${NAME}
	@${RM} ${NAME_BONUS}
	@echo "${BLUE}Cleaning is done!"

clean:
	@${MAKE} clean -s -C $(MLX_DIR)
	@${MAKE} clean -s -C ./lib/libft
	@${MAKE} clean -s -C ./lib/ft_printf
	@${RM} ${OBJS}
	@${RM} ${OBJS_BONUS}

re: fclean all

bonus: ${NAME_BONUS}

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

.PHONY: all clean fclean re norm .c.o