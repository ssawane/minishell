/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:27:19 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/26 12:59:17 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h> //proverit
# include <sys/stat.h> //proverit
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

typedef struct s_shell {
	int		pipes;
	int		close;
	int		pp[2];
	int		**mpp;
	char	*line;
	char	**words;
	char	**envv;
	char	**paths;
	t_cell	*cells;
	t_cmd	*cmds;
}	t_shell;

int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	ft_celladd_back(t_cell **cell, t_cell *new);
t_cell	*ft_cellnew(char *content);
int		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		spaces_adding(t_shell *shell);
t_cmd	*cmd_cells_convert(t_shell *shell);
void	main_exec(t_shell *shell);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	redir_proc(t_cell *cell, t_cmd *cmd);
int		spaces_changing(t_shell *shell);
void	quotes_correcting(t_shell *shell);
int		syntax_error_mes(void);
char	*ft_strdup(const char *s);

void	print(t_shell *shell);
void	print2(t_shell *shell);
void	print3(t_shell *shell);

#endif