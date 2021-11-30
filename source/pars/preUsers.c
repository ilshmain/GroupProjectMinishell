/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preUsers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:58:57 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:59:00 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*pre_use_fnc_dollar(char *line, int *i, char **env)
{
	char	*tmp;

	tmp = fnc_dollar(line, i, env);
	free (line);
	return (tmp);
}

char	*pre_use_fnc_dquot(char **line, int *i, char **env, t_gnrl **gen)
{
	char	*tmp;

	tmp = fnc_dquot(line, i, env, gen);
	free (*line);
	return (tmp);
}

char	*pre_use_fnc_quot(char *line, int *i, t_gnrl **gen)
{
	char	*tmp;

	tmp = fnc_quot(line, i, gen);
	free (line);
	return (tmp);
}

char	*pre_use_str_join(char *str1, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin_ms(str1, str2);
	free (str1);
	return (tmp);
}

char	*pre_use_fnc_redir(char **line, int *i, t_gnrl **gen)
{
	char	*tmp;

	tmp = ft_strdup(line[0]);
	if (tmp[*i] == '>' && tmp[*i + 1] == '>')
		tmp = fnc_redir(&tmp, i, gen, 1);
	else if (tmp[*i] == '>')
		tmp = fnc_redir(&tmp, i, gen, 2);
	else if (tmp[*i] == '<' && tmp[*i + 1] == '<')
		tmp = fnc_redir(&tmp, i, gen, 3);
	else if (tmp[*i] == '<')
		tmp = fnc_redir(&tmp, i, gen, 4);
	free (*line);
	return (tmp);
}
