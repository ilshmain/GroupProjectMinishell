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
//echo """"""""""              :""

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
			// if ((*gen)->heredoc_struct)
			// 	(*gen)->cmd->heredoc = env((*gen)->heredoc_struct);
//			printf("cmd: cmd_a_1:%s cmd_a_2:%s\n", (*gen)->cmd->command_array[0], (*gen)->cmd->command_array[1]);
			if ((*gen)->cmd != NULL)
				logica(gen);
		}
		(*gen)->env = clear_envp((*gen)->env);
		// if ((*gen)->heredoc_struct)
		// 	clear_hrd(&(*gen)->heredoc_struct);
	}
}

void	clear_hrd(t_list **strct)
{
	t_list	*tmp;

	tmp = (*strct);
	while (tmp->next != NULL)
	{
		free(tmp->str);
		tmp->str = NULL;
		tmp = tmp->next;
		(*strct)->next = NULL;
		free((*strct));
		(*strct) = tmp;
	}
	free(tmp->str);
	(*strct)->next = NULL;
	tmp = NULL;
	free((*strct));
	*strct = NULL;
	strct = NULL;
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
		ffnc_in_cycle(line, &i, gen);
	if ((*gen)->errors != 1)
		pre_use_fnc_pipe(line[0], &i, &(*gen));
	if ((*gen)->cmd == NULL)
		(*gen)->errors = 1;
//	for (int j = 0; (*gen)->cmd->command_array[j]; ++j) {
//		printf("%s\n", (*gen)->cmd->command_array[j]);
//	}
	return ((*gen)->errors);
}

void ffnc_in_cycle(char **line, int *i, t_gnrl **gen)
{
	if (line[0][*i] == '\'')
		line[0] = pre_use_fnc_quot(line[0], i, gen);
	else if (line[0][*i] == '\\')
		line[0] = fnc_bslsh(line[0], i, gen);
	else if (line[0][*i] == '\"')
		line[0] = pre_use_fnc_dquot(line, i, (*gen)->env, gen);
	else if (line[0][*i] == '$')
		line[0] = pre_use_fnc_dollar(line[0], i, (*gen)->env);
	else if (line[0][*i] == '>' || line[0][*i] == '<')
		line[0] = pre_use_fnc_redir(line, i, gen);
	else if (line[0][*i] == '|')
		line[0] = pre_use_fnc_pipe(line[0], i, &(*gen));
	else if (line[0][*i] == '~' && (line[0][(*i) + 1] == ' ' || line[0][(*i) + 1] == '\0'))
		line[0] = get_tilda(line, i);
	else if (!no_one_symbol_in_str(&line[0][*i], ' '))
		line[0] = ft_substr(line[0], 0, *i);
	else if (line[0][*i] == ' ' && line[0][(*i) + 1] == ' ')
		line[0] = space_cut_for_ffnc(line, i);
	else
		(*i)++;
}

char	*get_tilda(char **line, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = getenv("HOME");
	tmp2 = ft_substr_ms(line[0], 0, *i + 1);
	tmp2 = pre_use_str_join(tmp2, tmp);
	tmp = ft_substr_ms(line[0], (*i) + 1, ft_strlen(line[0]) - *i + 1);
	tmp2 = pre_use_str_join(tmp2, tmp);
	free(tmp);
	free(*line);
	return (tmp2);
}

char	*space_cut_for_ffnc(char **line, int *i)
{
	char	*tmp;

	tmp = pre_use_str_join(ft_substr(line[0], 0, *i), &line[0][*i + 1]);
	free(*line);
	return (tmp);
}

char	*pre_use_fnc_pipe(char *line, int *where_is_pipe, t_gnrl **gen)
{
	char	*tmp;
	t_cmnd	*tmp_command_line;

	if_pipe(&(*gen)->cmd, &tmp_command_line, where_is_pipe, line);//
	pu_fnc_pipe_safe_page(line, where_is_pipe, &tmp_command_line, &(*gen)->cmd);//
	tmp = ft_substr_ms(line, 0, *where_is_pipe);
	if (comparison_first_word(tmp, ' ', "echo"))
		tmp_command_line->command_array = fake_split(tmp, ' ');
	else
		tmp_command_line->command_array = ft_split(tmp, ' ');
	butils_prov(&tmp_command_line);
	if ((*gen)->heredoc_struct)//
	{//
		tmp_command_line->heredoc = env((*gen)->heredoc_struct);
		clear_hrd(&(*gen)->heredoc_struct);
	}//
	free(tmp);
	tmp = ft_substr_ms(line, *where_is_pipe + 1,
			ft_strlen_ms(line) - *where_is_pipe);
	if (tmp && ft_strcmp_ms(tmp, "") != 0)
		tmp_command_line->next_list = ft_lstnew_ms();
	*where_is_pipe = 0;
	free(line);
	return (tmp);
}

char	**fake_split(char *str, char sym)
{
	char	**tmp;
	int		i;
	int		j;
	int		qt;

	if (!str)
		return (0);
	i = -1;
	j = 0;
	qt = 0;
//	printf("%s\n", str);
	tmp = (char **)malloc(sizeof (char *) * get_qt_str(str, ' ') + 1);
	while (str[++i])
	{
		if (str[i] == sym && (str[i + 1] != '\0' || qt == 0))
		{
			tmp[qt++] = ft_substr(str, j, i - j);
//			printf("%s\n", tmp[qt - 1]);
			j = i + 1;
			while (str[i] && str[i++] == sym);
		}
	}
	if (str[j] != '\0')
		tmp[qt++] = ft_substr(str, j, i - j);
//	printf("%s\n", tmp[qt - 1]);
	tmp[qt] = NULL;
	return (tmp);
}

int	no_one_symbol_in_str(char *str, char sym)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] != sym)
			return (1);
	return (0);
}

int	get_qt_str(char *str, char sym)
{
	int	i;
	int	qt;

	if (!str || str[0] == '\0')
		return (0);
	qt = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == sym)
			while (str[i])
			{
				i++;
				if (str[i] != sym && str[i] != '\0')
				{
					qt++;
					break;
				}
			}
		i++;
	}
	return (qt);
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