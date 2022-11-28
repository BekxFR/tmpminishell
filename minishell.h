
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
	int		pipex[2];
	int		exec;
	int		tabexec;

	int	tablen;
	char	*comp;
	int	heredoc_status;
	int	fd1;
	int	fd2;
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
	int counter;
	int len;	
}	t_index;

/* fill_args.c*/

char	**fill_args(char *s, char c, char **s1);
char ***fill_cmd(char ***cmd, char **args, char ***redir);
char ***malloc_cmd(char ***cmd, char **args);

/* ft_parsing.c */

char	***ft_parsing(char *s, char **envp);
int	is_in_quote(char *str, int i);
int	double_pointer_nbr(char *s, char c);
char *malloc_simple_pointer(int count, int t, char **s1);
char	**simple_pointer_nbr(char *s, char c, char **s1);
char **get_args(char *s, char c);
int	ft_triple_pointer_len(char *s);
void	set_in_cmd(char ****cmd, char ****redir, char **args, char *s);

/* mathieu_utils.c */

void	ft_putdoubletab(char **tab);
void	ft_puttripletab(char ***test);
int		ft_tablen(char **tab);
int		ft_strcmp(char *s1, char *s2);
int		ft_tabsort_cmp(char **s1, char **s2);
int		ft_tabunsort_cmp(char **tab1, char **tab2);
void	*ft_memcpy_mathieu(void *dest, void *src, size_t n);

/* is_cmdline_valid.c */

int is_cmdline_valid(char *str);

/* clean_quote.c */

char ***clean_args(char ***cmd);

/* replace_env_var.c */

void handle_environment_variables(char **argv, char **envp);

/* is_in_quote.c  */

int is_in_simple_quote(char *str, int i);
int is_in_quote(char *str, int i);

/* initialize_index.c */

t_index initialize_index();

/* malloc_args.c */

char	**simple_pointer_nbr(char *s, char c, char **s1);
char *malloc_simple_pointer(int count, int t, char **s1);
int	double_pointer_nbr(char *s, char c);
char **get_args(char *s, char c);

/* free_minishell.c */

void free_error_tripletab(char ***tab, int i);
void	free_doubletab(char **s);
void	free_error_doubletab(char **str, int i);
void free_tripletab(char ***tab);

/* get_exprt.c */

int is_not_in(char *str, char **tab);
char **sort_envp(char **envp, char **exprt);
char **get_exprt(char **envp);

/* get_env_var.c */

char	**get_env_var(char **args, char **envp);
char	*new_env_var(char *str, char **envp, t_index i);
char *remove_wrong_env(char *str, int end, int start);
char *add_good_env(char *str, int end, int start, char *envp);
char *get_env(char *env,  char *envp);

/* get_env_var_utils.c */

int ft_strlenenv(char *envp);
int	ft_strncmp_env(char *s1, char *s2, int n, int i);
int is_in_env(char **envp, char *str, int end, int start);

/* ft_export.c */
void	ft_exportunset_with_arg(t_m *var, char **args, int soft);
void	ft_export_check_double(t_m *var, char *args, int egalen);
void	ft_export_add(t_m *var, char *args, int type);
int		ft_export_check_args(char *args, int *egalen);

/* ft_env_unset.c */
int		ft_unset_check_args(char *args, int *egalen);
void	ft_unset_remove(t_m *var, int m);
void	ft_unset_check_double(t_m *var, char *args, int egalen);
void	ft_print_env(char **str);
int		ft_env(t_m *var, char **envp);

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
void 	handle_sigint(int sig);
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
void	ft_heredoc_fd(t_m *var, int n, int j);
void	ft_check_heredoc(char *argv, char *stop, t_m *var);

int		ft_export_check_addargs(char *args, int *egalen);
void	ft_add_export_check_double(t_m *var, char *args, int egalen);

#endif
