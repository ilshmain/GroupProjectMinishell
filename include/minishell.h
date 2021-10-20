#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include "../Libft/libft.h"
# include "../pars/mslib.h"

//typedef struct zik_list
//{
//	char			**comand;
//	int				flagPipe;
//	int				flagBuilt;
//	int				fdRead;
//	int				fdWrite;
//	int				fdRewrite;
//	char			**heredoc;
//	struct zik_list	*next;
//}				tzik_list;

//utils prototype*****************************
void	ft_perror(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*change_ft_strrchr(const char *s, int c);
//********************************************

//BUILT prototype*****************************
void	levelUpBash(t_list *ptr);
void	initialEnv(char **envp, t_list **ptr, int i);
void	printEnvBuilt(t_list *ptr);
void	pwdBuilt();

//********************************************


#endif