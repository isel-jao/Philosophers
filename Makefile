CC			=	gcc -pthread -I includes/
CFLAGS		=	-Wall -Wextra -Werror 

NAME    	= philo

SRC_DIR		=	./srcs/
OBJ_DIR		=	./objs/

SRC			+=	philo.c 

OBJ			=	$(addprefix $(OBJ_DIR),$(SRC:.c=.o))


RM			=	/bin/rm -f
RM_DIR		=	/bin/rm -rf

$(OBJ_DIR)%.o:$(SRC_DIR)%.c ./includes/*.h
	@$(CC)  -c $< -o $@

all:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJ)
	@$(CC) ${OBJ} -o ${NAME}


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

eclean: clean fclean

re: fclean all

test: all
	@clear
	@./${NAME} 