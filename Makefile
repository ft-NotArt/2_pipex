# COLORS

GREY			=	\x1b[0m\x1b[38;2;139;143;145m
LIGHT_GREY	=	\x1b[0m\x1b[38;2;174;177;178m
DARK_GREY		=	\x1b[1m\x1b[38;2;83;86;87m

# TARGET

NAME			=	pipex

LIBFT			=	libft.a
LIBFT_DIR		=	libft
LIBFT_PATH		=	$(LIBFT_DIR)/$(LIBFT)

# FLAGS

MAKEFLAGS		+=	-s
CFLAGS			=	-Wall -Werror -Wextra -g -Ilibft -Ilibft/gnl
ARFLAGS			=	rcs

# FILES

FILES			=	pipex							\
					pipex_cmd						\
					pipex_fd						\
					pipex_utils						\
\

SRC				=	$(addsuffix .c, $(FILES))
OBJ				=	$(addsuffix .o, $(FILES))

# RULES

all				:	$(NAME)

$(LIBFT_PATH)	:
					$(MAKE) -C $(LIBFT_DIR) $(LIBFT) -j $$(nproc)

$(NAME)			:	$(OBJ) | $(LIBFT_PATH)
					$(CC) $(CFLAGS) $^ $(LIBFT_PATH) -o $@
					echo -e '$(LIGHT_GREY) \tCompiled$(DARK_GREY) $@'

clean			:
					$(RM) $(OBJ) $(CHECKER_OBJ)
					$(MAKE) -C $(LIBFT_DIR) f$@
					echo -e '$(LIGHT_GREY) \tCleaned$(GREY) $(OBJ) $(CHECKER_OBJ)'

fclean			:	clean
#					$(MAKE) -C $(LIBFT_DIR) $@
					$(RM) $(NAME) $(CHECKER)
					echo -e '$(LIGHT_GREY) \tCleaned$(DARK_GREY) $(NAME)'

re				:	fclean all

.PHONY			=	all clean fclean re
