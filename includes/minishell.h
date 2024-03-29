/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:27:19 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/08 17:08:41 by ssawane          ###   ########.fr       */
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
	int				pfd[2];
	char			**oper;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shl {
	int		i;
	int		echo;
	int		exit;
	int		envnum;
	int		pipes;
	int		close;
	int		exit_code;
	int		*pids;
	char	*line;
	char	*hist_path;
	char	**words;
	char	**envv;
	char	**expenv;
	char	**paths;
	t_cell	*cells;
	t_cell	*t1;
	t_cmd	*cmds;
}	t_shl;

extern t_shl	g_b;

t_cell	*ft_cellnew(char *content);
t_cmd	*ft_cmdnew(void);
void	ft_celladd_back(t_cell **cell, t_cell *new);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *s1, char *s2);

void	shell_init(char **envp);

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
int		pointer(int t);

void	main_exe(void);
void	execute(t_cmd *cmd);
void	pipes_check(void);
void	free_paths(void);
void	builtins_parent(void);
void	builtins_child(t_cmd *cmd);
void	finish_free(void);
int		digscheck(char *str);
void	ft_pwd(void);
void	ft_check_builtin(int *fd);
void	unset_pr(void);
void	export_pr(void);
void	ft_print(char **env);
int		ft_masslen(char **str);
int		ft_export_check(char *str);
void	expenv_sort(void);
void	ft_cd(void);
void	add_toenv(char *str, int j);
void	add_toexpenv(char *str, int j);

void	signals_proc(void);
void	inside_pr(int signum);
void	echo_sig(int sig);

char	*digitfirst(char *str, int k, int *j);
void	tilda_proc(void);
void	local_expenv(void);

#endif