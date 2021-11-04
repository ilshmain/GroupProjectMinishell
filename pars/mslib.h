#ifndef MSLIB_H
#define MSLIB_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>
# include "../include/minishell.h"
# include <fcntl.h>
# include <signal.h>

typedef struct s_cmnd
{
	char			**command_array;
	int 			flg_butil;
	int				flg_pipe;
	int				fd_open;
	int				fd_write;
	int				fd_reWrite;
	char 			**heredoc;
	int				err;
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
int		first_fnc(char **line, t_gnrl **gen, int i);
t_cmnd	*fnc_pars(char *line, int beginOfLine, t_cmnd *commandLine);

char	**ft_splitMS(char const *s, char c);
size_t	ft_strlcatMS(char *dst, const char *src, size_t size);
size_t	ft_strlcpyMS(char *dst, const char *src, size_t size);
size_t	ft_strlenMS(const char *str);
char	*ft_strchrMS(const char *s, int c);
char	*ft_strjoinMS(char const *s1, char const *s2);
void	error_call(char *message);

char	*ft_substrMS(char const *s, unsigned int start, size_t len);
char	*ft_strdupMS(const char *s1);

char	*fnc_quot(char *line, int *i, t_gnrl **gen);
char	*fnc_dquot(char *line, int *i, char **env, t_gnrl **gen);
char	*unionForQuotStr(char *line, int *i, int j);

char	*fnc_bslsh(char *line, int *i,t_gnrl **gen);

char	*fnc_dollar(char *line, int *i, char **env);
char	*dollarAssigment(char *line, int *i, int j, char **env);

int		ft_isalnumMS(int c);
char	*ft_strnstrMS(const char *str1, const char *str2, size_t len);
int		ft_strcmpMS(const char *s1, const char *s2);

void	genInit(t_gnrl **gen);
char	*fncCutTbl(char *str);

char	*preUseFncRedir(char **line, int *i, t_gnrl **gen);
char	*preUseStrJoin(char *str1, char *str2);
char	*preUseFncQuot(char *line, int *i, t_gnrl **gen);
char	*preUseFncDQuot(char **line, int *i, char **env, t_gnrl **gen);
char	*preUseFncDollar(char *line, int *i, char **env);

void	ft_putstr_fdMS(char *s, int fd);
t_cmnd	*ft_lstnewMS(void);
char	*strCutStr(char *inStr, int startOfCut, int endOfCut);
char	**envPrisv(char **envp);
void	butilsProv(t_cmnd **command);

char	*fnc_redir(char **line, int *i, t_gnrl **gen, int ident);
void	fncRedirOpen(char *line, t_cmnd **cmd, char *nameFile);
void	fncRedirReWrite(char *line, t_cmnd **cmd, char *nameFile);
void	fncRedirWrite(char *line, t_cmnd **cmd, char *nameFile);
void	fncRedirHeredoc(t_cmnd **cmd, char *hereDoc);

int		logica(t_gnrl **zik);

void	cdBuilt(t_list *ptr, t_gnrl *zik);
void	echoBuilt(t_gnrl *zik);
void	exportBuilt(t_list *ptr, t_gnrl *zik);
void	unsetBuilt(t_list *ptr, t_gnrl *zik);

void	fncMonitor(t_cmnd *cmd);

//int		check_for_pipes(char const *line);
char	*preUseFncPipe(char *line, int *whereIsPipe, t_cmnd **commandLine);
//void	*signalQuitMS(int get);
//void	exitCtrlD(void);
void	ctrl_c_hook(int sgn);
void    rl_replace_line(const char *buffer, int val);
char	*nameForRedir(char **line, int *nameLen, int *i, t_gnrl **gen);
//char	*ifName(char **line, int *i, t_gnrl **gen);
char	*initLine(char *line);
int		dualArrayLen(char **array);

#endif
