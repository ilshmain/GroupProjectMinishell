/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bslshWorkPage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:58:19 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:58:22 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*fnc_bslsh(char *line, int *i, t_gnrl **gen)
{
	char	*tmp1;
	char	*tmp2;

	tmp2 = NULL;
	if (ft_strcmp_ms(line + *i + 1, "\0") == 0)
	{
		(*gen)->errors = 1;
		*i += 1;
		return (line);
	}
	if (*i == 0)
		tmp1 = ft_strdup_ms(line + *i + 1);
	if (*i > 0)
	{
		tmp1 = ft_substr_ms(line, 0, *i);
		tmp2 = ft_strdup_ms(line + *i + 1);
		tmp1 = pre_use_str_join(tmp1, tmp2);
	}
	++(*i);
	free (line);
	if (tmp2)
		free (tmp2);
	return (tmp1);
}
