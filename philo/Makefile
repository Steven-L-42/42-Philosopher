NAME		=	philo

SRCS_FOLDER	=	srcs/

SRCS_FILES	=	main init utils threads1 threads2

SRCS		=	$(addsuffix .c, $(SRCS_FILES))

OBJS		=	$(addprefix $(SRCS_FOLDER),$(SRCS:.c=.o))

CC			=	CC

FLAGS		=	-Wall -Werror -Wextra

all: $(NAME)

$(NAME):		$(OBJS)
				$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re