#include "./pars/mslib.h"

int main(int argc, char const *argv[], char **envp) {
	(void)argc;
	(void)argv;
	char	*line;
	t_gnrl	*gen;

	gen = malloc(sizeof (t_gnrl));
	gen->env = envPrisv(envp);
	initialEnv(envp, &gen->ptr, 0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c_hook);
	exefnc(&line, &gen);
	return 0;
}

void	fncMonitor(t_cmnd *cmd)
{
	t_cmnd *tmp;
	int i = 0;
	int j = 0;

	tmp = cmd;
	while (1)
	{
		i = 0;
		j = 0;
		while (1)
		{
			printf("command_array[%d]: %s\n", i, tmp->command_array[i]);
			i++;
			if (tmp->command_array[i] == NULL)
				break;
		}
		printf("flg_butil: %d\n", tmp->flg_butil);
		printf("flg_pipe: %d\n", tmp->flg_pipe);
		printf("fd_open: %d\n", tmp->fd_open);
		printf("fd_write: %d\n", tmp->fd_write);
		printf("fd_reWrite: %d\n", tmp->fd_reWrite);
		if (tmp->heredoc != NULL)
		while (1)
		{
			printf("heredoc[%d]: %s\n", j, tmp->heredoc[j]);
			j++;
			if (tmp->heredoc[j] == NULL)
				break;
		}
		else
			printf("heredoc is missing");
		if (tmp->nextList == NULL) {
			printf("\nlast list\n\n");
			break;
		}
		printf("\nnext list -->>\n\n");
		tmp = tmp->nextList;
	}
}

//char	*fncCutTbl(char *str)
//{
//	int		startOfStr;
//	int		endOfStr;
//	char	*tmp;
//
//	startOfStr = 0;
//	while (str[startOfStr] && ft_isalnum(str[startOfStr]) == 0)
//		startOfStr++;
//	endOfStr = (int)ft_strlenMS(str);
//	while (endOfStr > startOfStr && ft_isalnum(str[endOfStr - 1]) == 0)
//		endOfStr--;
//	tmp = ft_substr(str, startOfStr, endOfStr - startOfStr);
//	free (str);
//	return (tmp);
//}

//int	ft_double_vlm(char *str, char key)
//{
//	int i;
//	int	qt;
//
//	i = 0;
//	qt = 0;
//	while (str[i])
//	{
//		if (str[i] == key && qt == 0)
//			qt++;
//		else if (str[i] == key && qt == 1)
//			qt--;
//		i++;
//	}
//	if (qt == 0)
//		return (0);
//	else
//		return (1);
//}


