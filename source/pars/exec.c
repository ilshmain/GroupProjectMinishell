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

char	**clear_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}
//echo $321
//echo ' """" '
//echo " '''''' "
//echo """"""""""              :""
//echo '"""""""""",         wtf     :""'

void	exefnc(char **line, t_gnrl **gen)
{
	while (1)
	{
		(*gen)->env = env((*gen)->ptr);
		(*gen)->errors = 0;
		*line = readline("minishell$ ");
		if (*line == NULL)
			error_call("exit\n");
		add_history(*line);
		*line = init_line(*line);
		if (first_fnc(line, gen, 0) == 0)
		{
			(*gen)->cmd = pre_logic_work(&(*gen)->cmd);
			if ((*gen)->heredoc_struct)
				(*gen)->cmd->heredoc = env((*gen)->heredoc_struct);
			if ((*gen)->errors == 0 && (*gen)->cmd != NULL)
				logica(gen);
		}
		(*gen)->env = clear_envp((*gen)->env);
//		if ((*gen)->heredoc_struct)
//			clear_envp((*gen)->heredoc_struct);
	}
}

t_cmnd	*pre_logic_work(t_cmnd **cmd)
{
	t_cmnd	*tmp;
	t_cmnd	*tmp2;

	tmp = *cmd;
	tmp2 = *cmd;
	if (tmp->next_list != NULL)
		while (tmp->next_list != NULL)
			plw_in_while(&tmp, &tmp2);
	else if (tmp->next_list == NULL && tmp->err == 1)
		return (NULL);
	return ((*cmd));
}

int	first_fnc(char **line, t_gnrl **gen, int i)
{
	(*gen)->cmd = ft_lstnew_ms();
	if (ft_strcmp_ms(*line, "") == 0)
		return (1);
	while (line[0][i])
	{
		if (line[0][i] == '\'')
			line[0] = pre_use_fnc_quot(line[0], &i, gen);
		else if (line[0][i] == '\\')
			line[0] = fnc_bslsh(line[0], &i, gen);
		else if (line[0][i] == '\"')
			line[0] = pre_use_fnc_dquot(line, &i, (*gen)->env, gen);
		else if (line[0][i] == '$')
			line[0] = pre_use_fnc_dollar(line[0], &i, (*gen)->env);
		else if (line[0][i] == '>' || line[0][i] == '<')
			line[0] = pre_use_fnc_redir(line, &i, gen);
		else if (line[0][i] == '|' || line[0][i] == ';')
			line[0] = pre_use_fnc_pipe(line[0], &i, &(*gen)->cmd);
		else
			i++;
	}
	if ((*gen)->errors != 1)
		pre_use_fnc_pipe(line[0], &i, &(*gen)->cmd);
	if ((*gen)->cmd == NULL)
		(*gen)->errors = 1;
	return ((*gen)->errors);
}

char	*pre_use_fnc_pipe(char *line, int *where_is_pipe, t_cmnd **command_line)
{
	char	*tmp;
	t_cmnd	*tmp_command_line;

	if_pipe(command_line, &tmp_command_line, where_is_pipe, line);
	pu_fnc_pipe_safe_page(line, where_is_pipe, &tmp_command_line, command_line);
	tmp = ft_substr_ms(line, 0, *where_is_pipe);
	tmp_command_line->command_array = ft_split(tmp, ' ');
	butils_prov(&tmp_command_line);
	free(tmp);
	tmp = ft_substr_ms(line, *where_is_pipe + 1,
			ft_strlen_ms(line) - *where_is_pipe);
	if (tmp && ft_strcmp_ms(tmp, "") != 0)
		tmp_command_line->next_list = ft_lstnew_ms();
	*where_is_pipe = 0;
	free(line);
	return (tmp);
}
