#ifndef STRUCTS_MINISHELL_H
# define STRUCTS_MINISHELL_H

# include <stdlib.h>

typedef struct s_cmnd
{
	char			**command_array;
	int 			flg_butil;
	int				flg_pipe;
	int				fd_open;
	int				fd_write;
	int				fd_reWrite;
	char 			**heredoc;
	int				err;
	struct s_cmnd	*nextList;
}	t_cmnd;

typedef struct s_gnrl
{
	t_list  *ptr;
	t_cmnd	*cmd;
	int		errors;
	char	**env;
}	t_gnrl;

#endif