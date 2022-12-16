/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:03:07 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/16 17:59:32 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/wait.h>
# include <errno.h>
# include "libs/libft/includes/libft.h"
# include "libs/libft/includes/ft_printf.h"

typedef struct s_minishell
{
	char	*args_line;
	char	**env;
	int		h_fd;
	int		pcmd_line;
	char	**split_path;
	char	*path;
	char	*arg;
	int		**pipex;
	int		exec;
	int		tabexec;
	int		tablen;
	char	*comp;
	int		heredoc_status;
	char	***cmd;
	char	***redir;
	int		fdin;
	int		fdout;
	int		cmdtype;
	char	**heredoc;
	int		status;
	int		*pid;
	int		h_status;
	int		fd_status_in;
	int		fd_status_out;
	int		line;
}	t_m;

typedef struct s_index
{
	int	i;
	int	i1;
	int	i2;
	int	i3;
	int	j;
	int	j1;
	int	j2;
	int	j3;
	int	start;
	int	end;
	int	count;
	int	k;
	int	t;
	int	l;
	int	n;
	int	counter;
	int	len;	
}	t_index;

/* basic_env.c */

char	*remove_wrong_env(char *str, int end, int start);
char	*add_good_env(char *str, int end, int start, char *envp);
char	*basic_env(char *str, char **envp, t_index *i);

/* builtin.c */

int		is_str_digit(char *str);
int		do_builtin(t_m *var, char **cmd);
int		is_env_builtin(char **cmd);

/* clean_args.c */

char	*remove_quote(char *str, int quote, int i);
char	*clear_quote(char *str);
char	***clean_args(char ***cmd);

/* free_minishell1.c */

void	free_error_tripletab(char ***tab, int i);
void	free_doubletab(char **s);
void	free_error_doubletab(char **str, int i);
void	free_tripletab(char ***tab);

/* free_minishell2.c */

int		free_parent(t_m *var);
int		free_child(t_m *var);
int		free_child_heredoc(t_m *var);
void	ft_free_inttab(int **tab);

/* ft_cd.c */

int		find_env_name_line(char *name, char **env);
int		export_env(char *name, char *word, t_m *var);
char	*import_user(char *name, t_m *var);
int		cd_need_path(char **cmd, int len, t_m *var, char *newpath);
int		ft_cd(char **argv, int i, t_m *var);

/* ft_create_env.c */

int		ft_create_env(t_m *var, char **envp);
void	ft_print_env(char **str);
char	*ft_strdup_without_one(const char *src);
int		ft_export_check_args(char *args, int *egalen);
int		ft_export_check_addargs(char *args, int *egalen);

/* ft_echo.c */

int		is_n_option(char *str);
int		ft_echo(char **cmd);

/* ft_env.c */

int		ft_env(char **env);

/* ft_exec.c */

void	ft_execve(char *pcmd, char **option, char **envp, t_m *var);
void	ft_arg_with_path(char *arg, int *cmd, t_m *var);
void	ft_add_arg_totchar(char **str, char *arg, char c);
int		ft_check_access(char *argv, char **split, t_m *var);

/* ft_exit.c */

void	ft_exit(t_m *var, char **cmd);

/* ft_export.c */
void	ft_export(t_m *var, char **cmd);
void	ft_export_with_arg(t_m *var, char **args);
void	ft_export_check_double(t_m *var, char *args, int egalen);
void	ft_export_add(t_m *var, char *args, int type);
void	ft_add_export_check_double(t_m *var, char *args, int egalen);

/* ft_fd_init.c */
int		ft_check_fd_status(char *file, int *fd);
int		ft_append_init_fd(char *file, int *fd);
int		ft_trunc_init_fd(char *file, int *fd);

/* ft_fork_utils.c */

void	ft_close_pipe_fd(t_m *var);
void	ft_init_arg(char *argv, t_m *var);
void	ft_arg_check_fullpath(char *argv, t_m*var);
void	ft_fork_fail(t_m *var);

/* ft_fork.c */

void	ft_do_fork(t_m *var, char *arg, char **targ, int *pid);
void	ft_secur_fd(t_m *var);
void	ft_do_pipe_fork(t_m *var, char *arg, char **targ, int *pid);

/* ft_heredoc */

char	*basic_env_heredoc(char *str, char **envp, t_index *i);
char	*new_env_var_heredoc(char *str, char **envp, t_m *var);
void	ft_heredoc_fd(t_m *var, int n);

/* ft_heredoc */

void	ft_history_init_fd(char *file, int *fd);
void	ft_init_commands_history(t_m *var);

/* ft_init_pipe */

int		ft_init_pipe(t_m *var, int i);
int		ft_init_all_pipe(t_m *var);

/* ft_parsing.c */

int		will_return_nothing(char *str);
int		ft_parsing(t_m *var, char **envp, char ****cmd, char ****redir);
int		is_in_quote(char *str, int i);
int		double_pointer_nbr(char *s, char c);
int		ft_triple_pointer_len(char *s);

/* ft_path_args_tools.c */
void	ft_free_split_exclude_line(char **str, int line);
char	*ft_init_path_var(char **envp);
void	ft_cleanheredoc_fd(char *str, char *buffer, char *comp, int fd1);

/* ft_pwd.c */

int		ft_pwd(void);
int		go_in_builtin(char *str);

/* ft_signal.c */

void	ft_signal(int i);
void	handle_sigint_1(int sig);
void	handle_sigint_2(int sig);
void	handle_sigint_3(int sig);

/* ft_unlink.c */

void	ft_unlink(char ***redir, int i);
void	ft_unlink_all(t_m *var, int i);

/* ft_unset.c */

int		ft_unset_check_args(char *args, int *egalen);
void	ft_unset_remove(t_m *var, int m);
void	ft_unset(t_m *var, char **args);
void	ft_unset_check_double(t_m *var, char *args, int egalen);

/* get_args.c */

int		get_args(char ***args, char *s, char c, t_m *var);
char	**fill_args(char *s, char c, char **s1);

/* get_env_var_utils.c */

int		ft_strlenenv(char *envp);
int		ft_strncmp_env(char *s1, char *s2, int n, int i);
int		is_in_env(char **envp, char *str, int end, int start);
char	*get_env(char *env, char *envp);

/* get_env_var.c */

char	*exception_env(char *str, t_index *i);
char	*add_status(char *str, int end, int start, char *status);
char	**get_env_var(char **args, char **envp);
char	*new_env_var(char *str, char **envp);

/* get_exprt.c */

int		is_not_in(char *str, char **tab);
char	**sort_envp(char **envp, char **exprt);
int		get_exprt(char **envp);

/* get_status.c */

char	*get_status(char *str, int end, int start, char *status);

/* get_std_redir.c */

void	out(char *redir_file, char c, t_m *var);
void	in(char *redir_file, char c, t_m *var);
void	get_std_redir(char **redir, t_m *var);

/* handle_heredoc.c */

int		malloc_heredoc(t_m *var);
char	*get_heredoc(t_m *var, int k);
int		handle_heredoc(t_m *var);
char	*get_heredoc_child(t_m *var, int k);
int		handle_heredoc_child(t_m *var);

/* has_quote.c */

int		has_quote(char *str);

/* initialize_index.c */

t_index	initialize_index(void);

/*t initialize_var.c */

void	initialize_var(t_m *var);

/* is_cmdline_valid.c */

int		is_cmdline_valid(char *str, int argc, char **argv);

/* is_in_quote.c  */

int		is_in_double_quote(char *str, int i);
int		is_in_simple_quote(char *str, int i);
int		is_in_quote(char *str, int i);

/* is_redir.c */

int		is_redir(char **redir);
int		is_redir_out(char **redir);

/* main_utils.c */

void	free_parsing(t_m *var);
int		empty(char ***tab, t_m *var);
void	do_exec(t_m *var);
void	no_args_line(t_m *var);

/* malloc_args.c */

int		malloc_args(char *s, char c, char **s1, t_m *var);
int		malloc_simple_pointer(int count, int t, char **s1, t_m *var);
int		double_pointer_nbr(char *s, char c);
int		is_arg(char *s, int i);

/* malloc_cmd.c */

int		malloc_double_pointer_cmd(char ***tab, int count, \
char **args, t_m *var);
int		malloc_cmd(char ***cmd, char **args, t_m *var);

/* malloc_redir.c */

int		malloc_redir(char ***redir, char **args, t_m *var);
int		malloc_double_pointer_redir(char ***tab, int count, \
char **args, t_m *var);

/* minishell_utils.c */

char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_tablen(char **tab);
int		ft_intlen(int nbr);
int		ft_strcmplen(char ***redir, char *str);

/* minishell_utils2.c */

void	ft_putdoubletab(char **tab);
void	ft_puttripletab(char ***test);
int		ft_puttriplelen(char ***test, t_m *var);
int		ft_puttriplelentab(char ***test);

/* minishell.c */

void	ft_init_heredoc(t_m *var);
void	ft_daddy(t_m *var, int *pid, int nbcmd);
int		ft_exec(t_m *var, char ***args);
void	ft_check_args(int argc);

/* set_in_cmd.c */

int		set_in_cmd(char **args, t_m *var);
char	***fill_cmd(char ***cmd, char **args, char ***redir);

/* replace_env_var.c */

void	handle_environment_variables(char **argv, char **envp);

/* update_last_env.c */

int		update_last_env(t_m *var);

#endif
