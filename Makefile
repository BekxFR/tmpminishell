
.PHONY : all clean fclean re

NAME := minishell.a
SOFT_NAME := minishell

CC := gcc
FLAGS := -Wall -Wextra -Werror -lreadline -I includes/
SRC_DIR := sources/
OBJ_DIR := objects/
AR := ar rc
RM := rm

BLACK = \033[1;30m
REDBG = \033[30;41m
RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m

SRCS =	basic_env.c \
		builtin.c \
		clean_args.c \
		free_minishell1.c \
		free_minishell2.c \
		ft_cd.c \
		ft_create_env.c \
		ft_echo.c \
		ft_env.c \
		ft_exec.c \
		ft_exit.c \
		ft_export.c \
		ft_fd_init.c \
		ft_fork.c \
		ft_fork_utils.c \
		ft_heredoc.c \
		ft_history.c \
		ft_init_pipe.c \
		ft_parsing.c \
		ft_path_args_tools.c \
		ft_pwd.c \
		ft_signal.c \
		ft_unlink.c \
		ft_unset.c \
		get_args.c \
		get_env_var.c \
		get_env_var_utils.c \
		get_exprt.c \
		get_status.c \
		get_std_redir.c \
		handle_heredoc.c \
		has_quote.c \
		initialize_index.c \
		initialize_var.c \
		is_cmdline_valid.c \
		is_in_quote.c \
		is_redir.c \
		malloc_args.c \
		malloc_cmd.c \
		malloc_redir.c \
		minishell.c \
		minishell_utils2.c \
		minishell_utils.c \
		set_in_cmd.c \
		update_last_env.c \

LIBFT := libs/libft/libft.a
FCLIB := ${MAKE} fclean -C libs/libft

OBJS = $(SRCS:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR),$(OBJS))

OBJF := .cache_exists

all : ${LIBFT} ${NAME} ${SOFT_NAME}

${LIBFT} :
	${MAKE} all -C libs/libft
	cp ${LIBFT} ${NAME}

${NAME} : ${OBJ}
	@echo "${BLUE}###${NC}Update de l'archive ${NAME}${BLUE}###${MAGENTA}"
	${AR} ${NAME} ${OBJ}
	@echo "${NC}"

${OBJ_DIR}%.o : %.c | $(OBJF)
	@echo "${BLUE}###${NC}Creation du fichier ${@:%.c=%.o}${BLUE}###${ORANGE}"
	${CC} ${FLAGS} -c $< -o $@
	@echo "${NC}"

${SOFT_NAME} :
	@echo "${BLUE}###${NC}Creation du fichier ${SOFT_NAME}${BLUE}###${ORANGE}"
	${CC} ${NAME} ${FLAGS} -o ${SOFT_NAME}
	@echo "${NC}"

$(OBJF) :
	@mkdir -p ${OBJ_DIR}

clean : 
	${FCLIB}
	@echo "${RED}###${NC}Nettoyage des fichiers .o${RED}###"
	${RM} -rf ${OBJ_DIR}
	@echo "${GREEN}###${NC}Nettoyage OK${GREEN}###${NC}\n"

fclean : clean
	@echo "${RED}###${NC}Nettoyage d'archives et de Softs${RED}###"
	${RM} -f ${NAME} ${SOFT_NAME}
	@echo "${GREEN}###${NC}Nettoyage OK${GREEN}###${NC}\n"

re : fclean all
