.SILENT:

CFLAGS    = -Wall -Wextra -Werror
NAME      = philosophers
SRCS = src/main.c \
		src/init_table.c \
		src/check_utils.c \
		src/philo_acts.c \

OBJS := $(SRCS:.c=.o)
CC        = cc -g
RM        = rm -f
LIBFT     = ./lib/libft/libft.a

RED       = \033[0;91m
GREEN     = \033[1;92m
BLUE      = \033[0;94m

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -s -C ./lib/libft
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFT}
	@echo "${GREEN}Compilation is done!"

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

fclean: clean
	@${RM} ${NAME}
	@echo "${BLUE}Cleaning is done!"

clean:
	@${MAKE} clean -s -C ./lib/libft
	@${RM} ${OBJS}

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

.PHONY: all clean fclean re norm .c.o
