
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
	char 	***cmd;
	char 	***redir;
	int 	fdin;
	int 	fdout;
	int 	cmdtype;
	char 	**heredoc;
	int 	status;
	int		*pid;
	int		h_status;
	int		fd_status_in;
	int		fd_status_out;
	int		line;
}	t_m;

typedef struct s_index
{
	int i;
	int i1;
	int i2;
	int i3;
	int j;
	int j1;
	int j2;
	int j3;
	int start;
	int end;
	int count;
	int k;
	int t;
	int l;
	int n;
	int counter;
	int len;	
}	t_index;

/* fill_args.c*/

char	**fill_args(char *s, char c, char **s1);
char	***fill_cmd(char ***cmd, char **args, char ***redir);

/* ft_parsing.c */

int		ft_parsing(t_m *var, char **envp, char ****cmd, char ****redir);
int		is_in_quote(char *str, int i);
int		double_pointer_nbr(char *s, char c);
int		ft_triple_pointer_len(char *s);


/* set_in_cmd.c */

int	set_in_cmd(char **args, t_m *var);

/* malloc_redir.c */

int	malloc_redir(char ***redir, char **args, t_m *var);

/* malloc_cmd.c */

int malloc_cmd(char ***cmd, char **args, t_m *var);


/* minishell_utils.c */

char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_tablen(char **tab);
int		ft_intlen(int nbr);
int		ft_strcmplen(char ***redir, char *str);

/* minishell_utils2.c */

void	ft_putdoubletab(char **tab);
void	ft_puttripletab(char ***test);

/* is_cmdline_valid.c */

int		is_cmdline_valid(char *str);

/* clean_quote.c */

char	***clean_args(char ***cmd);
char	*clear_quote(char *str);

/* replace_env_var.c */

void	handle_environment_variables(char **argv, char **envp);

/* is_in_quote.c  */

int		is_in_simple_quote(char *str, int i);
int		is_in_quote(char *str, int i);

/* initialize_index.c */

t_index initialize_index();

/* get_args.c */

int		get_args(char ***args, char *s, char c, t_m *var);

/* malloc_args.c */

int		malloc_args(char *s, char c, char **s1, t_m *var);
int		malloc_simple_pointer(int count, int t, char **s1, t_m *var);
int		double_pointer_nbr(char *s, char c);
int		is_arg(char *s, int i);

/* free_minishell.c */

void	free_error_tripletab(char ***tab, int i);
void	free_doubletab(char **s);
void	free_error_doubletab(char **str, int i);
void	free_tripletab(char ***tab);
int		free_all(t_m *var);

/* get_exprt.c */

int		is_not_in(char *str, char **tab);
char	**sort_envp(char **envp, char **exprt);
int	get_exprt(char **envp);

/* get_env_var.c */

char	*add_status(char *str, int end, int start, char *status);
char	**get_env_var(char **args, char **envp);
char	*new_env_var(char *str, char **envp);
char	*remove_wrong_env(char *str, int end, int start);
char	*add_good_env(char *str, int end, int start, char *envp);
char	*get_env(char *env,  char *envp);

/* get_env_var_utils.c */

int		ft_strlenenv(char *envp);
int		ft_strncmp_env(char *s1, char *s2, int n, int i);
int		is_in_env(char **envp, char *str, int end, int start);

/* ft_export.c */
void	ft_export(t_m *var, char **cmd);
void	ft_export_with_arg(t_m *var, char **args);
void	ft_export_check_double(t_m *var, char *args, int egalen);
void	ft_export_add(t_m *var, char *args, int type);
void	ft_add_export_check_double(t_m *var, char *args, int egalen);

/* ft_env.c */
int		ft_create_env(t_m *var, char **envp);
void	ft_print_env(char **str);
char	*ft_strdup_without_one(const char *src);
int		ft_export_check_args(char *args, int *egalen);
int		ft_export_check_addargs(char *args, int *egalen);

/* ft_unset.c */
void	ft_unset(t_m *var, char **args);
void	ft_unset_check_double(t_m *var, char *args, int egalen);
void	ft_unset_remove(t_m *var, int m);
int		ft_unset_check_args(char *args, int *egalen);

/* ft_fork.c */
void	ft_do_fork(t_m *var, char *arg, char **targ, int *pid);
void	ft_do_pipe_fork(t_m *var, char *arg, char **targ, int *pid);
void	ft_init_arg(char *argv, t_m *var);
void	ft_arg_check_fullpath(char *argv, t_m*var);
void	ft_fork_fail(t_m *var);

/* ft_exec.c */
void	ft_execve(char *pcmd, char **option, char **envp, t_m *var);
void	ft_arg_with_path(char *arg, int *cmd);
void	ft_add_arg_totchar(char **str, char *arg, char c);
int		ft_check_access(char *argv, char **split);

/* ft_path_args_tools.c */
void	ft_free_split_exclude_line(char **str, int line);
char	*ft_init_path_var(char **envp);
void	ft_cleanheredoc_fd(char *str, char *buffer, char *comp, int fd1);

/* minishell.c */
void	ft_history_init_fd(char *file, int *fd);
void	ft_init_commands_history(t_m *var);
void	ft_print_split(char **str);
void 	handle_sigint_1(int sig);
void	ft_free_split(char **str);
void	ft_daddy(t_m *var, int *pid, int nbcmd);
int		ft_exec(t_m *var, char ***args);
int		ft_puttriplelen(char ***test, t_m *var);

/* ft_fd_init.c */
int		ft_check_fd_status(char *file, int *fd);
int		ft_append_init_fd(char *file, int *fd);
int		ft_trunc_init_fd(char *file, int *fd);

/* ft_heredoc */
int		ft_eof_find(char *str, char *comp, int i, t_m *var);
void	ft_write_here_sign(char c);
void	ft_write_here_sign(char c);
void	ft_heredoc_fd(t_m *var, int n);
void	ft_check_heredoc(char *argv, char *stop, t_m *var);




/* connect_std.c */

int		is_redir(char **redir);
int		is_redir_in(char **redir);
int		is_redir_out(char **redir);
void	out(char *redir_file, char c, t_m *var);
void 	in(char *redir_file, char c, t_m *var);
void    get_std_redir(char **redir, t_m *var);

/* handle_heredoc.c */

char	**malloc_heredoc(t_m *var);
char	**get_heredoc_filename(char **heredoc, int i);
char	*get_heredoc(t_m *var, int k);
int		handle_heredoc(t_m *var);

/* is_builtin.c */

int is_str_digit(char *str);
int do_builtin(t_m *var, char **cmd);
int is_env_builtin(char **cmd);

/* ft_cd.c */

int	export_env(char *name, char *word, t_m *var);
int ft_cd(char **argv, int i, t_m *var);

/* ft_exit.c */

void ft_exit(t_m *var, char **cmd);

/* ft_echo.c */

int	is_n_option(char *str);
int	ft_echo(char **cmd);

/* ft_pwd.c */

int	ft_pwd(void);
int	go_in_builtin(char *str);

/* ft_unlink.c */

void	ft_unlink(char ***redir, int i);

/* ft_env */

int ft_env(char **env);

/* get_status.c */

/* is_redir.c */

int	is_redir_out(char **redir);
int	is_redir(char **redir);


char	*get_status(char *str, int end, int start, char *status);

/* has_quote.c */

int		has_quote(char *str);
void	handle_sigint_2(int sig);
void	ft_fd_init(t_m *var);
void	ft_pipe_read_write(t_m *var);
void	ft_signal(int i);

/* update_last_env.c */

int update_last_env(t_m *var);
char	*get_heredoc_child(t_m *var, int k);
int	handle_heredoc_child(t_m *var);
void	handle_sigint_3(int sig);
void	ft_unlink_all(t_m *var, int i);

/*t initialize_var.c */

void	initialize_var(t_m *var);

#endif
