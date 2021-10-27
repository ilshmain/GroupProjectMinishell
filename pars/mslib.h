#ifndef MSLIB_H
#define MSLIB_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>
# include "../include/minishell.h"
#include <fcntl.h>

typedef struct s_cmnd
{
	char			**command_array;
	int				flg_pipe;
	int				fd_open;
	int				fd_write;
	int				fd_reWrite;
	char 			*heredoc;
	struct s_cmnd	*nextList;
}	t_cmnd;

typedef struct s_gnrl
{
	t_list  *ptr;
	t_cmnd	*cmd;
	int		errors;
	char	**env;
}	t_gnrl;

void	exefnc(char **line, t_gnrl **gen);
char	**ft_splitMS(char const *s, char c);
size_t	ft_strlcatMS(char *dst, const char *src, size_t size);
size_t	ft_strlcpyMS(char *dst, const char *src, size_t size);
size_t	ft_strlenMS(const char *str);
// void	pars(char *line);
char	*ft_strchrMS(const char *s, int c);
char	*ft_strjoinMS(char const *s1, char const *s2);
void	error_call(char *message);
void	ft_putstr_fdMS(char *s, int fd);
char	*ft_substrMS(char const *s, unsigned int start, size_t len);
char	*ft_strdupMS(const char *s1);
int		first_fnc(char **line, char **env, t_gnrl **gen, int i);
char	*fnc_quot(char *line, int *i, t_gnrl **gen);
char	*fnc_dquot(char *line, int *i, char **env, t_gnrl **gen);
char	*fnc_bslsh(char *line, int *i,t_gnrl **gen);
char	*fnc_dollar(char *line, int *i, char **env);
char	*unionForQuotStr(char *line, int *i, int j);
int		ft_isalnumMS(int c);
char	*ft_strnstrMS(const char *str1, const char *str2, size_t len);
int		ft_strcmpMS(const char *s1, const char *s2);
char	*dollarAssigment(char *line, int *i, int j, char **env);
char	*preUseStrJoin(char *str1, char *str2);
char	*preUseFncQuot(char *line, int *i, t_gnrl **gen);
char	*preUseFncDQuot(char *line, int *i, char **env, t_gnrl **gen);
char	*preUseFncDollar(char *line, int *i, char **env);
t_cmnd	*fnc_pars(char *line, int beginOfLine, t_cmnd *commandLine);
t_cmnd	*ft_lstnewMS(void);
void	genInit(t_gnrl **gen);
char	*strCutStr(char *inStr, int startOfCut, int endOfCut);
char	*fncCutTbl(char *str);

char	*preUseFncRedir(char *line, int *i, t_gnrl **gen);
char	*fnc_redir(char *line, int *i, t_gnrl **gen, int ident);
char	*fncRedirOpen(char *line, t_gnrl **gen, char *nameFile);
char	*fncRedirReWrite(char *line, t_gnrl **gen, char *nameFile);
char	*fncRedirWrite(char *line, t_gnrl **gen, char *nameFile);

char	**envPrisv(char **envp);
int		logica(t_gnrl **zik);

void	cdBuilt(t_list *ptr, t_gnrl *zik);
void	echoBuilt(t_gnrl *zik);
void	exportBuilt(t_list *ptr, t_gnrl *zik);
void	unsetBuilt(t_list *ptr, t_gnrl *zik);

#endif
