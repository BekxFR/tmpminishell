
.PHONY : all test bonus norm clean fclean re

NAME := minishell.a
NAME_BONUS := minishell_bonus.a
SOFT_NAME := minishell
SOFT_BONUS := minishell_bonus

CC := gcc
FLAGS := -Wall -Wextra -Werror -lreadline -I includes/
SRC_DIR := sources/
OBJ_DIR := objects/
AR := ar rc
RM := rm
VAL := valgrind --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes
# VAL := valgrind --leak-check=full --track-origins=yes --log-file="LogVal" --show-leak-kinds=all --track-fds=yes

BLACK = \033[1;30m
REDBG = \033[30;41m
RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m

SRCS =	minishell.c	\
		ft_parsing.c \
		minishell_utils.c \
		minishell_utils2.c \
		is_cmdline_valid.c \
		clean_args.c \
		ft_pwd.c \
		set_in_cmd.c \
		is_in_quote.c \
		initialize_index.c \
		get_args.c \
		free_minishell.c  \
		ft_env.c	\
		ft_export.c	\
		ft_unset.c	\
		ft_fork.c	\
		ft_exec.c	\
		ft_path_args_tools.c	\
		ft_fd_init.c	\
		ft_heredoc.c	\
		get_exprt.c \
		get_env_var.c \
		get_env_var_utils.c  \
		get_std_redir.c \
		handle_heredoc.c \
		malloc_redir.c \
		malloc_cmd.c \
		malloc_args.c \
		is_builtin.c \
		ft_cd.c \
		ft_exit.c \
		ft_echo.c \
		ft_export.c \
		ft_unlink.c \
		get_status.c \
		has_quote.c \
		ft_create_env.c \
		update_last_env.c \
		is_redir.c \
		initialize_var.c \

BONUS = \

LIBFT := libs/libft/libft.a
FCLIB := ${MAKE} fclean -C libs/libft

OBJS = $(SRCS:%.c=%.o)
BOBJS = $(BONUS:%.c=%.o)
NORM = $(wildcard *.c) $(wildcard *.h)

OBJ = $(addprefix $(OBJ_DIR),$(OBJS))
BOBJ = $(addprefix $(OBJ_DIR),$(BOBJS))

OBJF := .cache_exists

all : ${LIBFT} ${NAME} ${SOFT_NAME}

${LIBFT} :
	${MAKE} all -C libs/libft
	cp ${LIBFT} ${NAME}

${NAME} : ${OBJ}
	rm -f ${SOFT_NAME}
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

bonus : ${LIBFT} ${BOBJ} ${NAME_BONUS} ${SOFT_BONUS}

${NAME_BONUS} : ${BOBJ}
	@echo "${BLUE}###${NC}Update de l'archive ${NAME_BONUS}${BLUE}###${MAGENTA}"
	${AR} ${NAME_BONUS} ${BOBJ}
	@echo "${NC}"

${SOFT_BONUS} :
	@echo "${BLUE}###${NC}Creation du fichier ${SOFT_BONUS}${BLUE}###${ORANGE}"
	${CC} ${NAME_BONUS} ${LIBFT} ${FLAGS} -o ${SOFT_BONUS} 
	@echo "${NC}"

test : all
	${VAL} ./${SOFT_NAME}
	@echo "${BLUE}###${GREEN}Lecture du fichier .history${BLUE}###${NC}"
	@cat .history
	@echo "${BLUE}###${GREEN}Lecture du fichier Outfile${BLUE}###${NC}"
	@cat test2

test1 : all
	${VAL} env -i ./${SOFT_NAME}
	@echo "${BLUE}###${GREEN}Lecture du fichier .history${BLUE}###${NC}"
	@cat .history
	@echo "${BLUE}###${GREEN}Lecture du fichier Outfile${BLUE}###${NC}"
	@cat test2

test2 : all
	env -i ${VAL} ./${SOFT_NAME}
	@echo "${BLUE}###${GREEN}Lecture du fichier .history${BLUE}###${NC}"
	@cat .history
	@echo "${BLUE}###${GREEN}Lecture du fichier Outfile${BLUE}###${NC}"
	@cat test2

test3 : all
	env -i ${VAL} /usr/bin/env -i ./${SOFT_NAME}
	@echo "${BLUE}###${GREEN}Lecture du fichier .history${BLUE}###${NC}"
	@cat .history
	@echo "${BLUE}###${GREEN}Lecture du fichier Outfile${BLUE}###${NC}"
	@cat test2

my_test:
	${VAL} ./${SOFT_NAME} $(ARGS)
# make ARGS="infile 'touch 87899879' 'dfdsfdsfd TESTEUR' outfile99" my_test

my_test2:
	@echo ${VAL} ./${SOFT_NAME} $*

# testb : bonus
# 	${VAL} ./${SOFT_BONUS}

clean : 
	${FCLIB}
	@echo "${RED}###${NC}Nettoyage des fichiers .o${RED}###"
	${RM} -rf ${OBJ_DIR}
	@echo "${GREEN}###${NC}Nettoyage OK${GREEN}###${NC}\n"

fclean : clean
	@echo "${RED}###${NC}Nettoyage d'archives et de Softs${RED}###"
	${RM} -f ${NAME} ${NAME_BONUS} ${SOFT_NAME} ${SOFT_BONUS}
	@echo "${GREEN}###${NC}Nettoyage OK${GREEN}###${NC}\n"

re : fclean all

norm :
	${MAKE} norm -C libs/libft
	@norminette $(NORM) | grep -v OK! || true
