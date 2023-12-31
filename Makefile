.SILENT:

CFLAGS    = -Wall -Wextra -Werror
NAME      = philo
SRCS = src/main.c \
		src/init_table.c \
		src/utils1.c \
		src/utils2.c \
		src/stop_cond.c \
		src/philo_acts.c \

OBJS := $(SRCS:.c=.o)
CC        = cc -g
RM        = rm -f

RED       = \033[0;91m
GREEN     = \033[1;92m
BLUE      = \033[0;94m

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "${GREEN}Compilation is done!"

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

fclean: clean
	@${RM} ${NAME}
	@echo "${BLUE}Cleaning is done!"

clean:
	@${RM} ${OBJS}

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

.PHONY: all clean fclean re norm .c.o
