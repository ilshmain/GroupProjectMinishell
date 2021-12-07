/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:30:51 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:30:57 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_built(void)
{
	char	pwd[1024];

	g_exit_code = 0;
	getcwd(pwd, 1024);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (1);
}
