/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:58:41 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:58:43 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_call(char *message)
{
	if (message)
		ft_putstr_fd_ms(message, 1);
	exit(g_exit_code);
}
