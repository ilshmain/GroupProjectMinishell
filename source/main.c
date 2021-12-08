/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:57:09 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:57:12 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sig_noninter_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exit_code = 130;
}

void	sign(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, &ctrl_c_hook);
}

void	exefnc(char **line, t_gnrl **gen)
{
	while (1)
	{
		sign();
		(*gen)->env = env((*gen)->ptr);
		(*gen)->errors = 0;
		*line = readline("minishell$ ");
		if (*line == NULL)
			error_call("exit\n");
		if (*line[0] != '\0')
			add_history(*line);
		*line = init_line(*line);
		if (first_fnc(line, gen, 0) == 0)
		{
			(*gen)->cmd = pre_logic_work(&(*gen)->cmd);
			signal(SIGINT, sig_noninter_ctrl_c);
			if ((*gen)->cmd != NULL)
				logica(gen);
		}
		else
			lstclear(&(*gen)->cmd);
		sign();
		(*gen)->env = clear_envp((*gen)->env);
	}
}

int	main(int argc, char const *argv[], char **envp)
{
	char	*line;
	t_gnrl	*gen;

	(void)argc;
	(void)argv;
	g_exit_code = 0;
	gen = malloc(sizeof (t_gnrl));
	gen->heredoc_struct = NULL;
	initial_env(envp, &gen->ptr, 0);
	exefnc(&line, &gen);
}
