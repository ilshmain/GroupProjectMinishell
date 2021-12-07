/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:58:50 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:58:51 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*pre_use_substr(char *s, unsigned int start, size_t len)
{
	char	*tmp;

	tmp = ft_substr_ms(s, start, len);
	free(s);
	return (tmp);
}

void	if_pipe(t_cmnd **command_line, t_cmnd **tmp_command_line,
				int *w_i_p, char *line)
{
	(*tmp_command_line) = *command_line;
	if ((*tmp_command_line)->next_list != NULL)
		while ((*tmp_command_line)->next_list != NULL)
			(*tmp_command_line) = (*tmp_command_line)->next_list;
	if (line[*w_i_p] == '|')
		(*tmp_command_line)->flg_pipe = 1;
	if ((*tmp_command_line)->command_array != NULL)
	{
		(*tmp_command_line)->next_list = ft_lstnew_ms();
		(*tmp_command_line)->flg_pipe = 1;
		(*tmp_command_line) = (*tmp_command_line)->next_list;
	}
}

char	*cut_spaces(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] == ' ')
		i++;
	tmp = ft_substr_ms(line, i, ft_strlen(line) - i);
	i = ft_strlen_ms(tmp) - 1;
	while (tmp[i] == ' ')
		i--;
	free(line);
	line = ft_substr_ms(tmp, 0, i + 1);
	free(tmp);
	return (line);
}

void	pu_fnc_pipe_safe_page(char *line, int *where_is_pipe,
				t_cmnd **tmp_command_line, t_cmnd **command_line)
{
	if (line[*where_is_pipe] == '|')
		(*command_line)->flg_pipe = 1;
	(*tmp_command_line) = *command_line;
	if ((*tmp_command_line)->next_list != NULL)
		while ((*tmp_command_line)->next_list != NULL)
			(*tmp_command_line) = (*tmp_command_line)->next_list;
	if ((*tmp_command_line)->command_array != NULL)
	{
		(*tmp_command_line)->next_list = ft_lstnew_ms();
		(*tmp_command_line)->flg_pipe = 1;
		(*tmp_command_line) = (*tmp_command_line)->next_list;
	}
}

int	comparison_first_word(char *str, char delimiter, char *compr_word)
{
	char	*ret_word;
	int		i;

	i = 0;
	while (str[i] && str[i] != delimiter)
		i++;
	ret_word = ft_substr(str, 0, i);
	if (ft_strcmp(ret_word, compr_word) == 0)
	{
		free(ret_word);
		return (1);
	}
	free(ret_word);
	return (0);
}
