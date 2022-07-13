/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:27:19 by ssawane           #+#    #+#             */
/*   Updated: 2022/07/12 20:56:22 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h> // check
# include <sys/stat.h> // check
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_cell {
	char			*word;
	int				type;
	struct s_cell	*next;
}	t_cell;

typedef struct s_cmd {
	int				in; 
	int				out;
	int				end[2];
	pid_t			child;
	char			**oper;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shl {
	int		i;
	int		exit;
	int		envnum;
	int		pipes;
	int		close;
	int		*pids;
	int		**fdp;
	int		exit_code;
	char	*line;
	char	**words;
	char	**envv;
	char	**paths;
	t_cell	*cells;
	t_cell	*t1;
	t_cmd	*cmds;
}	t_shl;

extern t_shl	shl;

//libft
int		ft_strcmp(const char *s1, const char *s2);
void	ft_celladd_back(t_cell **cell, t_cell *new);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
t_cell	*ft_cellnew(char *content);
t_cmd	*ft_cmdnew(void);

//parsing
t_cmd	*cmd_cells_convert(void);
void	redir_proc(t_cell *cell, t_cmd *cmd);
void	quot_correct(void);
char	*dollar(char *str, int *p, int flag);
char	*add_fromenv(char *str, int k, int *j);
int		spaces_changing(void);
int		spaces_adding(void);
int		syntax_error_mes(void);
int		main_parsing(void);
int		dollar_check(char *word, int i);

//execute
void	main_exe(void);
char	**paths_pars(char **envp);
void	execute(t_cmd *cmd);
void	free_paths(void);
void		isbuildin(t_cmd *cmd);
int		digscheck(char *str);

//signals
void	signals_proc(void);

//temp
void	print(void);
void	print2(void);
void	print3(void);
char	*ft_find_path(t_cmd *tmp);

#endif