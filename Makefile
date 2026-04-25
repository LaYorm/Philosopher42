NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c check_init_arg.c init_structure.c clean_free.c routine.c \
		supervisor.c action.c
OBJ_DIR = objs

OBJ = ${SRC:%.c=$(OBJ_DIR)/%.o}

all : ${NAME}

${NAME} : ${OBJ}
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c philosopher.h
			@mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

clean :
			rm -rf $(OBJ_DIR)

fclean : clean
			rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re
