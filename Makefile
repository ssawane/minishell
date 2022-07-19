# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 16:28:48 by ssawane           #+#    #+#              #
#    Updated: 2022/07/19 21:17:29 by ssawane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
HEADER	=	includes/minishell.h
CFLAGS	=	-Wall -Wextra -Werror
RLINE	=	-lreadline
RM		=	rm -f
LIBS	=	-L libft -lft
MN_DR	=	src/main/
LFT_DR	=	src/libft_mod/
PRS_DR	=	src/parse/
EXE_DR	=	src/execute/
MAIN	=	minishell signals init
EXECUTE	=	execute paths_exe builtins_p builtins_c ft_pwd ft_export ft_export2 
LIBMOD	=	celllst cmdlst
PARSE	=	cmdtolist fdopen spc_add spc_change parsing quot_corr dollar_corr
SRCS	=	$(addsuffix .c, $(addprefix $(MN_DR), $(MAIN)))\
			$(addsuffix .c, $(addprefix $(PRS_DR), $(PARSE)))\
			$(addsuffix .c, $(addprefix $(EXE_DR), $(EXECUTE)))\
			$(addsuffix .c, $(addprefix $(LFT_DR), $(LIBMOD)))\
			$(addsuffix .c, $(addprefix temp/, temp_print))
OBJ		=	$(SRCS:%.c=%.o)

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			@echo "\n"
			@make -C libft
			@echo "\033[0;32mCompiling minishell..."
			@$(CC) $(LIBS) $(RLINE) $(CFLAGS) $(OBJ) -o $(NAME)
			@echo "\n\033[0;32mDone !"

%.o		:	%.c
			@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $@
			
clean	:	
			@echo "\n\033[0;31mCleaning libft..."
			@make -C libft clean
			@echo "\nRemoving binaries..."
			@$(RM) $(OBJ)
			@echo "\033[0m"

fclean	:	clean
			@echo "\033[0;31mDeleting executable..."
			@make -C libft fclean
			@$(RM) $(NAME)
			@echo "\033[0m"
			
re		:	fclean all

