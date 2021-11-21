#include "../include/minishell.h"

int main(int argc, char const *argv[], char **envp) {
	(void)argc;
	(void)argv;
	char	*line;
	t_gnrl	*gen;

	exit_code = 0;
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
		printf("err: %d\n", tmp->err);
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



