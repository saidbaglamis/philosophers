CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread
RM = rm -rf

NAME = philo
SRC = 	inputchecker.c\
		death.c\
		init.c\
		main.c\
		routine.c\
		time.c\
		utils.c\

${NAME}:
	${CC} ${CFLAGS} ${SRC} -o ${NAME}

all: ${NAME}

clean:

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re