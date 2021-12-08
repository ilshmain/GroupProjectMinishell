NAME			= 	minishell

SRCS			=	./source/pars/safePage.c \
					./source/main.c \
					./source/builts/cd.c \
					./source/builts/echo.c \
					./source/builts/env.c \
					./source/builts/export.c \
					./source/builts/pwd.c \
					./source/builts/exit.c \
					./source/builts/export_utils.c \
					./source/builts/unset.c \
					./source/builts/utils.c \
					./source/logica/logic.c \
					./source/pars/bslshWorkPage.c \
					./source/pars/dollarWorkPage.c \
					./source/pars/error_call.c \
					./source/pars/exec.c \
					./source/pars/preUsers.c \
					./source/pars/quotWorkPage.c \
					./source/pars/redirWorkPage.c \
					./source/pars/servFnc.c \
					./source/pars/servFncII.c \
					./source/pars/ms_libft/ft_isalnum.c  ./source/pars/ms_libft/ft_strchr.c \
					./source/pars/ms_libft/ft_split.c 	 ./source/pars/ms_libft/ft_strdup.c \
					./source/pars/ms_libft/ft_strjoin.c  ./source/pars/ms_libft/ft_strlcat.c \
					./source/pars/ms_libft/ft_strlcpy.c  ./source/pars/ms_libft/ft_strlen.c \
					./source/pars/ms_libft/ft_strncmp.c  ./source/pars/ms_libft/ft_strnstr.c \
					./source/pars/ms_libft/ft_substr.c	 ./source/pars/safePageII.c ./source/pars/safePageIII.c\
					./source/work_pipe/get_next_line.c \
					./source/work_pipe/pipex_bonus.c \
					./source/work_pipe/path.c \
					./source/work_pipe/redirects_utils.c \
					./source/work_pipe/pipex_bonus_utils.c \
					./source/work_pipe/pipex_bonus_utils1.c \
					./source/work_pipe/redirects.c \

OBJS			=	$(patsubst %.c, %.o, $(SRCS))

HEADERS			=	-I./include/ -I.source/Libft/

CC				=	gcc

RM				=	rm -rfv

CFLAGS			=	-Wall -Wextra -Werror

MSH_HRD			=	./include/minishell.h
STRUCT_HRD		=	./include/structs_minishell.h
LIB_HRD			=	./source/Libft/libht.h
LIBS			=	./source/Libft/libft.a
LIB_DIR			=	./source/Libft/
RDL				= 	-lreadline
RDL_MAC			= 	-L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/


all:			$(NAME)

%.o:			%.c $(MSH_HRD) $(STRUCT_HRD)
				$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME):		$(OBJS) ./source/Libft/libft.h
				@make -C $(LIB_DIR)
				@$(CC) $(CFLAGS) -o $(NAME) $(LIBS) $(HEADERS) $(RDL_MAC) $(RDL) $(OBJS)

clean:
				$(MAKE) clean -C ./source/Libft/
				$(RM) $(OBJS)

fclean:			clean
				$(MAKE) fclean -C ./source/Libft/
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re