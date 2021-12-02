/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:54:45 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:54:47 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MINISHELL_H
# define STRUCTS_MINISHELL_H

# include <stdlib.h>
# include "../source/Libft/libft.h"

int	exit_code;

typedef struct sta_pam
{
	int		i;
}	tama_map;

typedef struct s_cmnd
{
	char			**command_array;
	int				flg_butil;
	int				flg_pipe;
	int				fd_open;
	int				fd_write;
	int				fd_re_write;
	char			**heredoc;
	int				err;

	int				fd[2];
	int				in;
	int				out;
	int				pid;
	int				fork;
	struct s_cmnd	*next_list;
}	t_cmnd;

typedef struct s_gnrl
{
	t_list	*ptr;
	t_cmnd	*cmd;
	int		errors;
	char	**env;
	t_list	*heredoc_struct;
}	t_gnrl;

#endif
