/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:41:50 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/02 16:07:38 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	set_input_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	signal_handler2(int signo)
{
	if (signo == SIGINT)
		ft_putendl_fd("", 1);
}

/*
Boucle infinie qui affiche le prompt et attend l'input de l'utilisateur
*/
static void	ft_prompt(int ac, t_shell *shell)
{
	char	*str;

	str = NULL;
	while (ac > 0)
	{
		set_input_signals();
		str = readline(GREEN"\e[1mW3LC0M3-1N-sH3LL> \e[m"WHITE);
		str = ft_strtrim(str, " ");
		signal(SIGINT, &signal_handler2);
		if (!str)
		{
			ft_putendl_fd("exit", 1);
			ft_exit_minishell(shell);
		}
		if (ft_strlen(str))
		{
			if (!parser(str, shell))
			{
				ft_executer(shell);
				free_shell(shell);
			}
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)av;
	shell.exit_code = 0;
	if (ac > 1)
	{
		ft_putendl_fd("No arguments allowed", 1);
		exit (127);
	}
	shell.envp_list = ft_init_env(&shell, envp);
	if (!shell.envp_list)
		return (0);
	shell.exit_code = 0;
	ft_prompt(ac, &shell);
	return (0);
}
