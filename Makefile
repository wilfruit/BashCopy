SRC = main.c \
parsing/start_pars.c parsing/special_characters.c \
parsing/built_stuct.c parsing/redirection.c \
project_utils/utils.c project_utils/utils_two.c \
parsing/legible_struct.c parsing/last_legible_struct.c \
project_utils/utils_three.c \
execution/minishell_operator.c init/build_cmd.c \
init/env_list_to_str.c execution/ft_exec.c \
execution/exe_errors.c project_utils/utils_free.c \
builtins/our_env.c builtins/our_pwd.c builtins/our_echo.c \
builtins/exe_builtin.c builtins/our_unset.c \
builtins/our_cd.c redirections/pipex_utils.c \
redirections/pipex_more_utils.c redirections/pipex.c \
init/dollar_swap.c \
builtins/our_exit.c redirections/is_redir.c \
redirections/treat_redir.c \
redirections/is_redir_multi.c builtins/our_cd_utils.c \
redirections/GNL_join.c redirections/here_doc_single.c \
builtins/our_export.c builtins/our_exprint.c \
redirections/here_doc_multi_utils.c \
init/dollar_swap_deluxe.c \
redirections/GNL.c project_utils/utils_four.c \
init/nested_command.c \
redirections/is_redir_bis.c \
project_utils/utils_five.c \
redirections/treat_redir_bis.c \
project_utils/utils_six.c \
project_utils/utils.seven.c

CC = gcc  -g

HEADER = mini_shell.h

OBJ = $(SRC:%./.c=./.build/%.o)

NAME = mini_shell

RM = rm -rf

LIBC = ar -rc

PRINTF = cd ./libft && make

CFLAGS = -Wall -Wextra -Werror 

# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m

./.build/%.o : %.c
	@$(CC) ${CFLAGS} -I. -o $@ -c $?
	@printf "${B_MAGENTA}Compilling $? ...\n${NONE}"

all :	
	@mkdir -p .build
	@make ${NAME}

${NAME} : $(OBJ)
	${PRINTF}
	${CC} -o ${NAME} ${OBJ} -lreadline ./libft/libft.a
	@printf "${B_GREEN}==>{${NAME}} LINKED SUCCESFULLY<==${NONE}\n"

clean :
	@${RM} .build
	@cd ./libft && make clean
	@printf "${B_RED}XX{${NAME}} CLEANED SUCCESFULLY XX${NONE}\n"

fclean :	clean
	@${RM} ${NAME}
	@cd ./libft && make fclean
	@printf "${B_RED}XX{${NAME}} FCLEAN SUCCESFULL XX${NONE}\n"

re :	fclean all
