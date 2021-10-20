cmake_minimum_required(VERSION 3.20)
project(checkMinishell C)

set(CMAKE_C_STANDARD 99)

set(BUILTS_FILES
        builts/bash.c
        builts/cd.c
        builts/echo.c
        builts/env.c
        builts/export.c
        builts/pwd.c
        builts/unset.c
        builts/utils.c
        include/minishell.h)

set(SOURCE_FILES
        Libft/ft_strtrim.c 	    Libft/ft_strjoin.c	    Libft/ft_substr.c
        Libft/ft_calloc.c	    Libft/ft_strdup.c	    Libft/ft_atoi.c
        Libft/ft_bzero.c	    Libft/ft_isalnum.c	    Libft/ft_isalpha.c
        Libft/ft_isascii.c	    Libft/ft_isdigit.c	    Libft/ft_isprint.c
        Libft/ft_split.c	    Libft/ft_putnbr_fd.c	Libft/ft_putendl_fd.c
        Libft/ft_putstr_fd.c    Libft/ft_putchar_fd.c   Libft/ft_memccpy.c
        Libft/ft_memchr.c	    Libft/ft_memcmp.c		Libft/ft_memcpy.c
        Libft/ft_memmove.c 	    Libft/ft_memset.c 	    Libft/ft_strchr.c
        Libft/ft_strmapi.c 	    Libft/ft_itoa.c 	    Libft/ft_strlcat.c
        Libft/ft_strlcpy.c 	    Libft/ft_strlen.c 	    Libft/ft_strncmp.c
        Libft/ft_lstnew.c	    Libft/ft_lstadd_front.c	Libft/ft_lstsize.c
        Libft/ft_lstlast.c	    Libft/ft_lstadd_back.c
        Libft/ft_strnstr.c 	    Libft/ft_strrchr.c 	    Libft/ft_tolower.c	Libft/ft_toupper.c Libft/libft.h)

set(PARS_FILES
        pars/error_call.c
        pars/ft_isalnum.c
        pars/ft_split.c
        pars/ft_strchr.c
        pars/ft_strdup.c
        pars/ft_strjoin.c
        pars/ft_strlcat.c
        pars/ft_strlcpy.c
        pars/ft_strlen.c
        pars/ft_strncmp.c
        pars/ft_strnstr.c
        pars/ft_substr.c
        pars/mslib.h
        logic.c
        main.c)

add_executable(checkMinishell ${BUILTS_FILES} ${SOURCE_FILES} ${PARS_FILES})