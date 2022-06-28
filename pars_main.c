/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/06/26 00:49:18 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	argc_check(int ac, char **av)
{
	if (ac != 1 || av[1] != NULL)
	{
		printf("%s\n", "error about file or directory");
		return (0);
	}
	return (1);
}

int	close_term_check(char *line)
{
	if (!(ft_strcmp(line, "exit")))
		return (0);
	return (1);
}

t_cell	*cell_words_convert(t_shell *shell)
{
	int		i;
	t_cell	*nodes;
	t_cell	*unit;

	i = 1;
	nodes = ft_cellnew(shell->words[0]);
	while (shell->words[i])
	{
		unit = ft_cellnew(shell->words[i]);
		ft_celladd_back(&nodes, unit);
		i++;
	}
	i = -1;
	while (shell->words[++i])
		free(shell->words[i]);
	free(shell->words);
	shell->words = NULL;
	return (nodes);
}

int	syntax_errors_check(t_shell *shell)
{
	t_cell	*tmp;

	tmp = shell->cells;
	while (tmp)
	{
		if (tmp->type == 2 && !ft_strcmp(tmp->word, "<"))
			if (tmp->next->type == 2 && !ft_strcmp(tmp->next->word, ">"))
				tmp = tmp->next;
		if (tmp->type == 2)
			if (!tmp->next || tmp->next->type == 2 || tmp->next->type == 3)
				return(syntax_error_mes());
		if (tmp->type == 3)
			if (!tmp->next || tmp->next->type == 3)
				return(syntax_error_mes());
		tmp = tmp->next;
	}
	return (0);
}

void	adding_history(t_shell *shell)
{
	int	fd;

	add_history(shell->line);
	fd = open("history.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell: cannot open history file");
		exit(0);
	}
	write(fd, shell->line, ft_strlen(shell->line));
	write(fd, "\n", 1);
	close(fd);
}

int	main_parsing(t_shell *shell)
{
	adding_history(shell);
	if (spaces_adding(shell) || spaces_changing(shell))
		return (1);
	shell->words = ft_split(shell->line, '\n');
	shell->cells = cell_words_convert(shell);
	if (syntax_errors_check(shell))
		return(1);
	quotes_correcting(shell);
	shell->cmds = cmd_cells_convert(shell);
	if (shell->close == 1)
		return (1);
	return (0);
}

void	ft_free(t_shell *shell)
{
	int		i;
	t_cell	*tmp;
	t_cmd	*tmp2; 

	i = -1;
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->cmds)
	{

		while (shell->cmds)
		{
			tmp2 = shell->cmds;
			if (shell->cmds->oper)
			{
				i = -1;
				while(shell->cmds->oper[++i])
					free(shell->cmds->oper[i]);
				free(shell->cmds->oper);
			}
			shell->cmds = shell->cmds->next;
			free(tmp2);
		}
		shell->cmds = NULL;
	}
	if (shell->cells)
	{
		while (shell->cells)
		{
			free(shell->cells->word);
			shell->cells->word = NULL;
			tmp = shell->cells;
			shell->cells = shell->cells->next;
			free(tmp);
		}
		shell->cells = NULL;
	}
}

int	isempty_line(char *line)
{
	int	i;

	i = 0;
	if (!ft_strcmp(line, "\0"))
		return (1);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

void	shell_initialization(t_shell *shell, char **envp)
{
	shell->envv = envp;
	shell->line = NULL;
	shell->words = NULL;
	shell->cells = NULL;
	shell->cmds = NULL;
	shell->close = 0;
	shell->mpp = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	shell_initialization(&shell, envp);
	if (argc_check(ac, av))
	{
		while (close_term_check(shell.line = readline("minishell>$ ")))
		{
			if (!isempty_line(shell.line) && !main_parsing(&shell))
			{
				main_exec(&shell);
				// print(&shell);
				// print2(&shell);
				// print3(&shell);
				print3(&shell);
			}
			ft_free(&shell);
			if (shell.close == 1)
				exit (0);
			// print(&shell);
			// print2(&shell);
			// print3(&shell);
		}
	}
	return (0);
}