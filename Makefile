NAME 		= 	fdf

BONUS		=	fdf_bonus

CC			= 	cc

RM 			= 	rm -f

INC			=	-I includes -I libft -I mlx_linux 

CFLAGS		=	-Wall -Wextra -Werror

LFLAGS		=	-I./libft -lft -L./libft -I./mlx_linux -L./mlx_linux -I./fdf -L./fdf

LIBFT		=	./libft/libft.a

MLX			=	./mlx_linux/libmlx_Linux.a

SRCS		=	init.c \
				fdf.c \
				matrix.c \
				matrix_utils.c \
				drawing.c \
				drawing_utils.c \
				scanning.c \
				events.c \
				destroyer.c \

SRCS_BONUS	=	init.c \
				fdf.c \
				matrix_utils.c \
				drawing.c \
				drawing_utils.c \
				scanning.c \
				events_bonus.c \
				keys_bonus.c \
				destroyer_bonus.c \
				matrix_bonus.c \

OBJS		= 	$(SRCS:.c=.o)

OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

all:		$(NAME)

bonus:		$(BONUS)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(OUTPUT_OPTION) $(INC)

$(LIBFT):
			$(MAKE) -C $(@D) $(@F)

$(MLX):
			$(MAKE) -C $(@D)

$(NAME):	$(LIBFT) $(MLX) $(OBJS) 
			$(CC) $(OBJS) $(LFLAGS) $(OUTPUT_OPTION) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)  

$(BONUS):	$(LIBFT) $(MLX) $(OBJS_BONUS) 
			$(CC) $(OBJS_BONUS) $(LFLAGS) $(OUTPUT_OPTION) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(BONUS)
clean:
			$(RM) $(OBJS) $(OBJS_BONUS)
			$(RM) ./libft/*.o ./mlx_linux/obj/*.o
		
fclean:		clean
			$(RM) $(NAME) $(BONUS) $(LIBFT) $(MLX)

re:			fclean all

.PHONY:		all clean fclean re bonus