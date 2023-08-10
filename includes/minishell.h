/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:36:46 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/10 12:06:45 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>

# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"

# define NO_FORKS 1
# define FORKS 2

# define MODE_APPEND 1
# define MODE_READ 2
# define MODE_WRITE 3
# define MODE_HEREDOC 4

typedef struct s_redir{
	char	*name;
	char	mode;
	int		idx;
}				t_redir;

typedef struct s_cmnd{
	char	*cmd;
	char	**args;
	int		in_file;
	int		out_file;
	t_list	*redir;
}				t_cmnd;

typedef struct s_shell{
	t_cmnd	*cmd;
	int		count_cmd;
	t_list	*envp_list;
	int		exit_code;
}				t_shell;

typedef struct s_env{
	char	*name;
	char	*value;
}				t_env;

typedef struct s_substitute{
	char		*output;
	char		*new_output;
	int			output_size;
	int			input_index;
	int			is_quote;
	char		*var_start;
	int			var_len;
	char		*number_str;
	int			number_len;
	const char	*env_value;
	int			env_len;
	char		*var_name;
}				t_substitute;

void	rl_replace_line(const char *text, int clear_undo);

t_list	*ft_init_env(t_shell *shell, char **env);
int		ft_putenv(t_list **is_head, char *name, char *val);
char	*ft_getenv(t_list *is_head, char *i_str);
t_env	**ft_sortenv(t_list **is_envp_list);
t_list	*ft_search_dubname(t_list **is_head, char *name);
char	*get_name_env(char *s);
char	*get_value_env(char *s);

int		ft_env(t_list **is_envp_list);
void	ft_pwd(t_shell *data);
void	ft_unset(t_shell *data, int num_cmd);
void	ft_unset_var_env(t_list **is_envp_list, char *str);
void	ft_export(t_shell *data, int num_cmd);
int		ft_cd(t_shell *d, int num_cmd, char *new_pwd);
void	ft_echo(t_shell *d, int num_cmd);
void	ft_exit(t_shell *data, int num_cmd);

char	*ft_join_env(t_env *env);

int		ft_print_error(t_shell *shell, char *str, int nbr);
int		ft_print_perror(t_shell *shell, const char *str, int nbr);
void	ft_print_err_export(char *str);
char	*permission_error(char *cmd, t_shell *dt);

int		parser(char *line, t_shell *mini);
int		pre_parse(char *line, t_shell *mini);
char	*parse_line(char *line, t_shell *data, int i);

int		is_end(int c);
int		args_counter(t_list *lst);
t_list	*get_tokens(char *line, t_list *token);
void	init_each_command(t_list **lst, t_shell *data, int i);
void	ft_init_file(t_list *lst, t_cmnd *cmd, t_shell *data, int idx);
int		is_builtin(t_shell *data, int num_cmd);
int		execute_builtin(t_shell *data, int num_cmd);
void	ft_free_env(t_list **is_head);

void	free_shell(t_shell *mini);
void	ft_close_fd(int *fd[2], t_shell *data);
int		ft_process_manager(pid_t	*id, t_shell *data, char **envp, int i);
int		ft_redir(t_cmnd *cmd, t_list *lst, int i);
void	ft_dup_fd(int i, int **fd, t_shell *data);
int		ft_executer(t_shell *data);
int		ft_no_file_dir(int fd, char *name);
char	*join_path(char *cmd, char **path, t_shell *dt);
int		set_exit_status(int exit_status);
void	ft_exit_minishell(t_shell *data);

char	**ft_minisplit(char *str);
char	**ft_minifree(char **arr, int i);
int		ft_isnum(char c);

char	*substitute_variables(char	*input, int code, t_list *is_head);

char	*ft_strjoin_export(char const *s1, char const *s2);

t_shell	*parse_quotes_cmds(t_shell *shell);

char	*remove_empty_quotes(char	*str);

#endif