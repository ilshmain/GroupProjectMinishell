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

add_executable(checkMinishell ${SRC} source/pars/safePage.c)
target_link_libraries (checkMinishell /Users/fmint/shell/source/Libft/libft.a)
#target_link_libraries (checkMinishell /Users/hportife/hportife/mshell/source/Libft/libft.a)