SRC = start_pars.c special_characters.c main.c built_stuct.c redirection.c \
utils.c utils_two.c legible_struct.c last_legible_struct.c utils_three.c \
minishell_operator.c build_cmd.c env_list_to_str.c ft_exec.c \
exe_errors.c utils_free.c our_env.c our_pwd.c our_echo.c \
exe_builtin.c our_unset.c our_cd.c pipex_utils.c \
pipex_more_utils.c pipex.c dollar_swap.c \
our_exit.c is_redir.c treat_redir.c \
is_redir_multi.c our_cd_utils.c \
GNL_join.c here_doc_single.c \
our_export.c our_exprint.c \
here_doc_multi_utils.c \
dollar_swap_deluxe.c \
GNL.c utils_four.c \
nested_command.c \
is_redir_bis.c \
strjoinmod.c \
treat_redir_bis.c

CC = gcc  -g

HEADER = mini_shell.h

OBJ = $(SRC:%.c=./.build/%.o)

NAME = mini_shell

RM = rm -rf

LIBC = ar -rc

PRINTF = cd ./libft && make

CFLAGS = -Wall -Wextra -Werror 
CFLAGS =

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
