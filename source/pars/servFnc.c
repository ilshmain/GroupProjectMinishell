#include "../../include/minishell.h"

void	ft_putstr_fdMS(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

t_cmnd	*ft_lstnewMS(void)
{
	t_cmnd *tmp;

	tmp = malloc(sizeof (t_cmnd) * 1);
	tmp->command_array = NULL;
	tmp->flg_butil = 0;
	tmp->flg_pipe = 0;
	tmp->fd_re_write = -2;
	tmp->fd_write = -2;
	tmp->fd_open = -2;
	tmp->heredoc = NULL;
	tmp->err = 0;
	tmp->next_list = NULL;
	return (tmp);
}

char *strCutStr(char *inStr, int startOfCut, int endOfCut)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_substrMS(inStr, 0, startOfCut);
	tmp1 = ft_substrMS(inStr, endOfCut, ft_strlen(inStr));
	free (inStr);
	inStr = preUseStrJoin(tmp, tmp1);
	if (tmp1)
		free(tmp1);
	return (inStr);
}

void	butilsProv(t_cmnd **command)
{
	if (ft_strcmp((*command)->command_array[0], "echo") == 0)
		(*command)->flg_butil = 1;
	else if(ft_strcmp((*command)->command_array[0], "cd") == 0)
		(*command)->flg_butil = 1;
	else if(ft_strcmp((*command)->command_array[0], "pwd") == 0)
		(*command)->flg_butil = 1;
	else if(ft_strcmp((*command)->command_array[0], "export") == 0)
		(*command)->flg_butil = 1;
	else if(ft_strcmp((*command)->command_array[0], "unset") == 0)
		(*command)->flg_butil = 1;
	else if(ft_strcmp((*command)->command_array[0], "env") == 0)
		(*command)->flg_butil = 1;
	else if(ft_strcmp((*command)->command_array[0], "exit") == 0)
		(*command)->flg_butil = 1;
}