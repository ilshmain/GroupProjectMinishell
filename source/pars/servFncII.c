/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servFncII.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:59:43 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:59:44 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	plw_in_while(t_cmnd **tmp, t_cmnd **tmp2)
{
	if ((*tmp)->err == 1)
	{
		if ((*tmp)->next_list)
			(*tmp2)->next_list = (*tmp)->next_list;
		else
			(*tmp2)->next_list = NULL;
		(*tmp) = (*tmp2)->next_list;
	}
	else
	{
		*tmp2 = *tmp;
		*tmp = (*tmp)->next_list;
	}
}

char	*init_line(char *line)
{
	char	*tmp;

	tmp = ft_strdup(line);
	free(line);
	return (tmp);
}

void	ctrl_c_hook(int sgn)
{
	rl_on_new_line();
	rl_redisplay();
	printf("  \n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sgn;
}

int	dual_array_len(char **array)
{
	int	i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*name_for_redir(char **line, int *name_len, int *i, t_gnrl **gen)
{
	char	*file_name;

	*name_len = *i;
	while ((line[0][*name_len]) && (ft_isalnum_ms(line[0][*name_len]) == 0))
		*name_len += 1;
	line[0] = str_cut_str(*line, *i, *name_len);
	*name_len = *i;
	while ((line[0][*name_len]))
	{
		if (line[0][*name_len] == '\'')
			line[0] = pre_use_fnc_quot(line[0], name_len, gen);
		else if (line[0][*name_len] == '\\')
			line[0] = fnc_bslsh(line[0], name_len, gen);
		else if (line[0][*name_len] == '\"')
			line[0] = pre_use_fnc_dquot(line, name_len, (*gen)->env, gen);
		else if (line[0][*name_len] == '$')
			line[0] = pre_use_fnc_dollar(line[0], name_len, (*gen)->env);
		else if (line[0][*name_len] == '|' || line[0][*name_len] == '<' ||
				line[0][*name_len] == '>' || line[0][*name_len] == ' ')
			break ;
		*name_len += 1;
	}
	file_name = ft_substr(line[0], *i, *name_len - *i);
	return (file_name);
}
