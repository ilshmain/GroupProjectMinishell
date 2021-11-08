cmake_minimum_required(VERSION 3.20)
project(checkMinishell C)

#set(CMAKE_C_FLAGS "-L/Users/hportife/.brew/Cellar/readline/8.1.1/lib/ -lreadline")
set(CMAKE_C_FLAGS "-L/Users/fmint/.brew/Cellar/readline/8.1.1/lib/ -lreadline")

set(CMAKE_C_STANDARD 99)

include_directories(source/Libft/libft.a)
FILE(GLOB SRC
        "source/logica/logic.c"
        "source/builts/*.c"
        "source/work_pipe/*.c"
        "source/*.c"
        "source/pars/*.c"
        "source/pars/ms_libft/*.c")

add_executable(checkMinishell ${SRC})
target_link_libraries (checkMinishell /Users/fmint/shell/source/Libft/libft.a)

#add_executable(checkMinishell ${BUILTS_FILES} ${SOURCE_FILES} ${PARS_FILES} ${PIPE_FILES})cmake_minimum_required(VERSION 3.20)
#project(checkMinishell C)
#
##set(CMAKE_C_FLAGS "-L/Users/hportife/.brew/Cellar/readline/8.1.1/lib/ -lreadline")
#set(CMAKE_C_FLAGS "-L/Users/fmint/.brew/Cellar/readline/8.1.1/lib/ -lreadline")
#
#set(CMAKE_C_STANDARD 99)
#
#set(BUILTS_FILES
#        source/builts/bash.c
#        source/builts/cd.c
#        source/builts/echo.c
#        source/builts/env.c
#        source/builts/export.c
#        source/builts/pwd.c
#        source/builts/unset.c
#        source/builts/utils.c
#        include/minishell.h
#        include/structs_minishell.h)
#
#set(PIPE_FILES
#        source/work_pipe/get_next_line.c
#        source/work_pipe/get_next_line_utils.c
#        source/work_pipe/pipex_bonus.c
#        source/work_pipe/pipex_bonus_utils.c
#        source/work_pipe/pipex_bonus_utils1.c)
#
#set(SOURCE_FILES
#        source/Libft/ft_strtrim.c source/Libft/ft_strjoin.c source/Libft/ft_substr.c
#        source/Libft/ft_calloc.c source/Libft/ft_strdup.c source/Libft/ft_atoi.c
#        source/Libft/ft_bzero.c source/Libft/ft_isalnum.c source/Libft/ft_isalpha.c
#        source/Libft/ft_isascii.c source/Libft/ft_isdigit.c source/Libft/ft_isprint.c
#        source/Libft/ft_split.c source/Libft/ft_putnbr_fd.c source/Libft/ft_putendl_fd.c
#        source/Libft/ft_putstr_fd.c source/Libft/ft_putchar_fd.c source/Libft/ft_memccpy.c
#        source/Libft/ft_memchr.c source/Libft/ft_memcmp.c source/Libft/ft_memcpy.c
#        source/Libft/ft_memmove.c source/Libft/ft_memset.c source/Libft/ft_strchr.c
#        source/Libft/ft_strmapi.c source/Libft/ft_itoa.c source/Libft/ft_strlcat.c
#        source/Libft/ft_strlcpy.c source/Libft/ft_strlen.c source/Libft/ft_strncmp.c
#        source/Libft/ft_lstnew.c source/Libft/ft_lstadd_front.c source/Libft/ft_lstsize.c
#        source/Libft/ft_lstlast.c source/Libft/ft_lstadd_back.c
#        source/Libft/ft_strnstr.c source/Libft/ft_strrchr.c source/Libft/ft_tolower.c source/Libft/ft_toupper.c source/Libft/libft.h)
#
#set(PARS_FILES
#        source/pars/error_call.c
#        source/pars/ms_libft/ft_isalnum.c
#        source/pars/ms_libft/ft_split.c
#        source/pars/ms_libft/ft_strchr.c
#        source/pars/ms_libft/ft_strdup.c
#        source/pars/ms_libft/ft_strjoin.c
#        source/pars/ms_libft/ft_strlcat.c
#        source/pars/ms_libft/ft_strlcpy.c
#        source/pars/ms_libft/ft_strlen.c
#        source/pars/ms_libft/ft_strncmp.c
#        source/pars/ms_libft/ft_strnstr.c
#        source/pars/ms_libft/ft_substr.c
#        source/logica/logic.c
#        source/main.c source/pars/preUsers.c source/pars/quotWorkPage.c source/pars/dollarWorkPage.c source/pars/redirWorkPage.c source/pars/servFns.c source/pars/exec.c source/pars/bslshWorkPage.c)
#
#add_executable(checkMinishell ${BUILTS_FILES} ${SOURCE_FILES} ${PARS_FILES} ${PIPE_FILES})