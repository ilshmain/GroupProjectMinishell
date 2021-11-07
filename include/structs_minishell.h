#ifndef STRUCTS_MINISHELL_H
# define STRUCTS_MINISHELL_H

# include <stdlib.h>
# include "../source/Libft/libft.h"

typedef struct st_pam
{
	int		i;
	int		argc;
	int		fd[2];
	int		file1;
	int		file2;
	int		flag;
}	t_map;

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
	t_map	*pipe;
	t_list  *ptr;
	t_cmnd	*cmd;
	int		errors;
	char	**env;
}	t_gnrl;

#endif