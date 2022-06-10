NAME	=	minishell

SRCS	=	pars_main.c		pars_lib_ut.c		pars_line_corr.c\
			pars_temp.c		pars_cmdtolist.c	exec_main.c\
			
SRCS_B	=	\

HEADER	=	minishell.h
OBJ		=	$(patsubst %.c, %.o, $(SRCS))
OBJ_B	=	$(SRCS_B:%.c=%.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I$(HEADER)
LFLAGS	=	-lreadline

.PHONY	:	all clean fclean re bonus

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(SRCS) $(LFLAGS) -o $(NAME)

%.o		:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus	:
	@make OBJ="$(OBJ_B)" SRCS="$(SRCS_B)" all

clean	:
	@rm -f $(OBJ) $(OBJ_B)

fclean	:	clean
	@$(RM) $(NAME)

re		:	fclean all
