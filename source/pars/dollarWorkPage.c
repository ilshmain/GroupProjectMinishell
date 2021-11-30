/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarWorkPage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:58:33 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:58:34 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_key_for_fns_dollar(char c)
{
	if (c == '_' || ft_isalnum_ms(c) || c == '?')
		return (1);
	return (0);
}

char	*fnc_dollar(char *line, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = (*i)++;
	while (line[(*i)] && if_key_for_fns_dollar(line[(*i)]))
		(*i)++;
	if (*i == j + 1)
		return (ft_strdup_ms(line));
	if (line[j + 1] == '?' && (line [j + 2] == ' ' || line [j + 2] == '\0'))
		return (ret_for_dollar_what(&line, j));
	tmp = ft_substr_ms(line, 0, j);
	tmp2 = dollar_assigment(line, i, &j, env);
	if (tmp != NULL && tmp2 != NULL)
		tmp = pre_use_str_join(tmp, tmp2);
	tmp2 = NULL;
	if (line[*i] != '\0')
	{
		tmp2 = ft_strdup_ms(line + *i);
		tmp = pre_use_str_join(tmp, tmp2);
	}
	*i = j - 1;
	if (tmp2 != NULL)
		free(tmp2);
	return (tmp);
}

char	*ret_for_dollar_what(char **line, int j)
{
	char	*tmp;

	tmp = ft_substr_ms(*line, 0, ft_strlen_ms(*line)
			- (ft_strlen_ms(*line) - j));
	tmp = pre_use_str_join(tmp, ft_itoa(exit_code));
	return (tmp);
}

char	*dollar_assigment(char *line, int *i, int *j, char **env)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	(void)env;
	tmp = ft_substr_ms(line, *j + 1, *i - *j - 1);
	tmp2 = getenv(tmp);
	*j = *i - ft_strlen_ms(tmp) + ft_strlen_ms(tmp2);
	free (tmp);
	return (tmp2);
}
