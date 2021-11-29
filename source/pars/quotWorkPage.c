/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotWorkPage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:59:06 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:59:08 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*fnc_quot(char *line, int *i, t_gnrl **gen)
{
	int	j;

	j = *i;
	while (line[++*i])
	{
		if (line[*i] == '\'')
			break ;
	}
	if (line[*i] == '\0')
	{
		(*gen)->errors = 1;
		*i += 1;
		return (line);
	}
	return (union_for_quot_str(line, i, j));
}

char	*fnc_dquot(char *line, int *i, char **env, t_gnrl **gen)
{
	int	j;

	j = *i;
	while (line[++*i])
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\"' || line[*i + 1] == '$'
				|| line[*i + 1] == '\\'))
			line = fnc_bslsh(line, i, gen);
		if (line[*i] == '$')
			line = pre_use_fnc_dollar(line, i, env);
		if (line[*i] == '\"')
			break ;
	}
	if (line[*i] == '\0')
		(*gen)->errors = 1;
	return (union_for_quot_str(line, i, j));
}

char	*union_for_quot_str(char *line, int *i, int j)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr_ms(line, 0, j);
	tmp2 = ft_substr_ms(line, j + 1, *i - j - 1);
	tmp1 = pre_use_str_join(tmp1, tmp2);
	free (tmp2);
	tmp2 = ft_strdup_ms(line + *i + 1);
	tmp1 = pre_use_str_join(tmp1, tmp2);
	if (ft_strcmp_ms(tmp2, "\0") != 0)
		free(tmp2);
	--*i;
	return (tmp1);
}
