NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

OBJ_DIR = objs/
SRC_DIR = sources/
INC_DIR = include/

SRC_FILES = main.c check_init_arg.c init_structure.c clean_free.c routine.c \
		supervisor.c action.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all : ${NAME}

${NAME} : ${OBJS}
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

clean :
			rm -rf $(OBJ_DIR)

fclean : clean
			rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re
