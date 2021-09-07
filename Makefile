CC			=	gcc -pthread -I includes/
CFLAGS		=	-Wall -Wextra -Werror 

NAME    	= philo

SRC_DIR		=	./srcs/
OBJ_DIR		=	./objs/

SRC			+=	libft_functions.c 
SRC			+=	philo.c 
SRC			+=	time.c 
SRC			+=	init.c 
SRC			+=	log.c 
SRC			+=	parse.c 

OBJ			=	$(addprefix $(OBJ_DIR),$(SRC:.c=.o))


RM			=	/bin/rm -f
RM_DIR		=	/bin/rm -rf

$(OBJ_DIR)%.o:$(SRC_DIR)%.c ./includes/*.h
	@$(CC) $(CFLAGS) -c $< -o $@

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
norm:
	norminette ./srcs/ ./includes/