NAME 		= 	fdf

CC			= 	cc

RM 			= 	rm -f

INC			=	-I includes -I libft -I mlx_linux 

CFLAGS		=	-Wall -Wextra -Werror -g3

LFLAGS		=	-I./libft -lft -L./libft -I./mlx_linux -L./mlx_linux -I./fdf -L./fdf

LIBFT		=	./libft/libft.a

SRCS		=	fdf.c \
				matrix.c \
				drawing.c \
				drawing_utils.c \
				scanning.c \
				events.c \
				settings.c \
				window.c \
				

OBJS		= 	$(SRCS:.c=.o)

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(OUTPUT_OPTION) $(INC)

$(LIBFT):
			$(MAKE) -C $(@D) $(@F)

$(NAME):	$(LIBFT) $(OBJS) 
			$(CC) $(OBJS) $(LFLAGS) $(OUTPUT_OPTION) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)  

clean:
			$(RM) $(OBJS)
			$(RM) ./libft/*.o
		
fclean:		clean
			$(RM) $(NAME) $(LIBFT)

re:			fclean all

.PHONY:		all clean fclean re 