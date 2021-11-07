NAME			= 	minishell

SRCS			=	./source/main.c \
					./source/builts/bash.c \
					./source/builts/cd.c \
					./source/builts/echo.c \
					./source/builts/env.c \
					./source/builts/export.c \
					./source/builts/pwd.c \
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
					./source/pars/servFns.c \
					./source/pars/ms_libft/ft_isalnum.c  ./source/pars/ms_libft/ft_strchr.c \
					./source/pars/ms_libft/ft_split.c 	 ./source/pars/ms_libft/ft_strdup.c \
					./source/pars/ms_libft/ft_strjoin.c  ./source/pars/ms_libft/ft_strlcat.c \
					./source/pars/ms_libft/ft_strlcpy.c  ./source/pars/ms_libft/ft_strlen.c \
					./source/pars/ms_libft/ft_strncmp.c  ./source/pars/ms_libft/ft_strnstr.c \
					./source/pars/ms_libft/ft_substr.c \
					./source/work_pipe/get_next_line.c \
					./source/work_pipe/get_next_line_utils.c \
					./source/work_pipe/pipex_bonus.c \
					./source/work_pipe/pipex_bonus_utils.c \
					./source/work_pipe/pipex_bonus_utils1.c \

OBJS			=	$(SRCS:.c=.o)

HEADERS			=	-I./include/ -I.source/Libft/

CC				=	gcc

#BRWRINST		=	brew reinstall readline

RM				=	rm -rfv

CFLAGS			=	-Wall -Wextra -Werror

LIBS			=	./source/Libft/libft.a
RDL				= 	-lreadline
RDL_MAC			= 	-L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/


all:			$(NAME)

%.o:			%.c
				$(CC) $(CFLAGS) -c -g $< -o $@ $(HEADERS)

$(NAME):		$(OBJS) ./include/minishell.h ./include/structs_minishell.h ./source/Libft/libft.h
				cd ./source/Libft/ && $(MAKE)
				#$(BRWRINST)
				$(CC) $(CFLAGS) $(LIBS) $(HEADERS) $(RDL_MAC) $(RDL) $(OBJS) -o $(NAME)

clean:
				$(MAKE) clean -C ./source/Libft/
				$(RM) $(OBJS)
				@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean:			clean
				$(MAKE) fclean -C ./source/Libft/
				$(RM) $(NAME)
				@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:				fclean $(NAME)
				@echo "\033[35;1m\nRemake done\n\033[0m"

.PHONY:			all clean fclean re