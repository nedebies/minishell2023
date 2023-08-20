/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:10:28 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/20 11:58:55 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_cmd(t_list *lst, t_shell *mini)
{
	int		i;
	char	*token;

	i = 0;
	while (lst)
	{
		token = lst->content;
		if (!token)
			return (1);
		if (*token == '|')
		{
			i++;
			lst = lst->next;
		}
		else
		{
			init_each_command(&lst, mini, i);
			if (!mini->cmd[i].cmd || !mini->cmd[i].args)
				return (1);
			ft_quote_args(mini);
		}
	}
	return (0);
}

static int	check_tokens(t_list *lst)
{
	char	*token;

	while (lst)
	{
		token = lst->content;
		if (!token)
			return (1);
		if (!ft_strncmp(token, ">>", 2) || !ft_strncmp(token, "<<", 2))
		{
			lst = lst->next;
			token = lst->content;
			if (*token == '|')
				return (0);
		}
		else if (*token == '>' | *token == '<')
		{
			lst = lst->next;
			token = lst->content;
			if (*token == '|')
				return (0);
		}
		else
			lst = lst -> next;
	}
	return (1);
}

static char	*open_pipe(char *line)
{	
	char	*tmp;
	char	*nl;

	tmp = NULL;
	nl = readline(GREEN"\e[1m> \e[m"WHITE);
	while (!ft_strlen(nl))
	{
		free(nl);
		nl = readline("> ");
	}
	tmp = ft_strdup(line);
	if (line)
		free (line);
	if (ft_strlen(nl))
		line = ft_strjoin(tmp, nl);
	if (tmp)
		free (tmp);
	if (nl)
		free (nl);
	if (ft_strlen(line) > 1 && line[ft_strlen(line) - 1] == '|')
		line = open_pipe(line);
	add_history(line);
	return (line);
}
/*
t_shell *parse_quotes_cmds(t_shell *shell)
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i != shell->count_cmd)
	{
		j = -1;
		while (shell->cmd[i].args[++j])
		{
			if (shell->cmd[i].args[j][0] == '\'' && shell->cmd[i].args[j][ft_strlen(shell->cmd[i].args[j]) - 1] == '\'')
			{
				k = -1;
				while (shell->cmd[i].args[j][++k])
					shell->cmd[i].args[j][k] = shell->cmd[i].args[j][k + 1]; 
				shell->cmd[i].args[j][ft_strlen(shell->cmd[i].args[j]) - 1] = '\0';
			}
			if (shell->cmd[i].args[j][0] == '\"' && shell->cmd[i].args[j][ft_strlen(shell->cmd[i].args[j]) - 1] == '\"')
			{
				k = -1;
				while (shell->cmd[i].args[j][++k])
					shell->cmd[i].args[j][k] = shell->cmd[i].args[j][k + 1]; 
				shell->cmd[i].args[j][ft_strlen(shell->cmd[i].args[j]) - 1] = '\0';
			}
		}
	}
	return (shell);
}*/

static int	check_nb_cmd(t_shell *dt)
{
	if (dt->count_cmd == -1)
		return (1);
	if (dt->count_cmd > 400)
	{
		ft_putstr_fd("W3LC0M3-1N-sH3LL: fork: ", 2);
		ft_putendl_fd("Resource temporarily unavailable", 2);
		dt->exit_code = 1;
		return (1);
	}
	return (0);
}

int	parser(char *line, t_shell *shell, t_list *tokens)
{
	if (ft_strlen(line) > 1 && line[ft_strlen(line) - 1] == '|')
		line = open_pipe(line);
	line = parse_line(line, shell);
	if (!line)
		return (1);
	shell->count_cmd = pre_parse(line, shell);
	if (check_nb_cmd(shell))
		return (1);
	tokens = get_tokens(line, tokens);
	if (!check_tokens(tokens))
	{
		ft_lstclear(&tokens, free);
		return (1);
	}
	shell->cmd = malloc(sizeof(t_cmnd) * shell->count_cmd);
	if (!shell->count_cmd)
		return (1);
	ft_memset(shell->cmd, '\0', sizeof(t_cmnd) * shell->count_cmd);
	if (init_cmd(tokens, shell))
	{
		ft_lstclear(&tokens, free);
		return(free_shell(shell));
	}
	ft_lstclear(&tokens, free);;
	return (0);
}
