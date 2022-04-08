NAME 		= 	fdf

CC			= 	cc

RM 			= 	rm -f

INC			=	-Iincludes -Ilibft -Imlx

CFLAGS		=	-Wall -Wextra -Werror -g3

LFLAGS		=	-I./libft -lft -L./libft -I./mlx -L./mlx 

LIBFT		=	./libft/libft.a

SRCS		=	drawing.c \
				scanning.c \
				events.c \
				window.c \

OBJS		= 	$(SRCS:.c=.o)

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(OUTPUT_OPTION) $(INC)

$(LIBFT):
			$(MAKE) -C $(@D) $(@F)

$(NAME):	$(LIBFT) $(OBJS) 
			$(CC) $(OBJS) $(LFLAGS) $(OUTPUT_OPTION) -fsanitize=address -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)  

clean:
			$(RM) $(OBJS)
			$(RM) ./libft/*.o
		
fclean:		clean
			$(RM) $(NAME) $(LIBFT)

re:			fclean all

.PHONY:		all clean fclean re 