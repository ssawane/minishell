/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:27:19 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/09 23:51:26 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cell {
	char			*word;
	int				type;
	struct s_cell	*next;
}	t_cell;

typedef struct s_cmd {
	char			*in;
	char			*out;
	char			*stop;
	char			**oper;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell {
	char	*line;
	char	**words;
	char	**envv;
	char	**paths;
	t_cell	*cells;
	t_cmd	*cmds;
	char	*tmp;
}	t_shell;

int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	ft_celladd_back(t_cell **cell, t_cell *new);
t_cell	*ft_cellnew(char *content);
int		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	line_correcting(t_shell *shell);
t_cmd	*cmd_cells_convert(t_shell *shell);
void	main_exec(t_shell *shell);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void	print(t_shell *shell);
void	print2(t_shell *shell);
void	print3(t_shell *shell);

#endif