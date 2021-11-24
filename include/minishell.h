#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 1

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include "./structs_minishell.h"
# include "../source/Libft/libft.h"

void	ft_perror_2(char *str);

//utils prototype*****************************
void	ft_perror_shell(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*change_ft_strrchr(const char *s, int c);
//********************************************

//BUILT prototype*****************************
char	*levelUpDown(char *str);
int		initialEnv(char **envp, t_list **ptr, int i);
int		printEnvBuilt(t_list *ptr);
int		pwdBuilt();
int		cdBuilt(t_list *ptr, t_gnrl *zik);
int		echoBuilt(t_gnrl *zik);
int		exportBuilt(t_list *ptr, t_gnrl *zik);
int		unsetBuilt(t_list *ptr, t_gnrl *zik);
int 	builtFunc(t_gnrl *zik, t_list *ptr);
int		logica(t_gnrl **zik);
int 	size_heredoc(char **argv);
int		exit_built(char	**str, t_list **ptr);
int 	checking_validity_string(char *str);
void 	print_error_func(char *str1, char *str2);
int		size_two_poineter_mas(char **argv);
char 	**env(t_list *lst);
//********************************************

void	fncMonitor(t_cmnd *cmd);

//int	check_for_pipes(char const *line);
char	*preUseFncPipe(char *line, int *whereIsPipe, t_cmnd **commandLine);
//void	*signalQuitMS(int get);
//void	exitCtrlD(void);
void	ctrl_c_hook(int sgn);
void    rl_replace_line(const char *buffer, int val);
char	*nameForRedir(char **line, int *nameLen, int *i, t_gnrl **gen);
//char	*ifName(char **line, int *i, t_gnrl **gen);
char	*initLine(char *line);
int		dualArrayLen(char **array);

//KOSTYL prototype*****************************
t_list	*ft_lstlast(t_list *lst);
//********************************************

//PIPE prototype*****************************

int	work_with_pipe(t_gnrl **zik);

char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
int		get_next_line(int fd, char **line);

char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *p1, const char *p2, size_t n);
void	pars_envp(char **envp, char	**first_argv, int i, int k);
//void	pid_parent(t_map *st, char **envp, t_gnrl **zik);
int		pid_children(char **envp, t_gnrl **zik, t_cmnd *start);
void	create_pipe(t_cmnd *cmd);
void	ft_perror(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		CheckRedirect(t_cmnd *cmd);
int		Dup(t_cmnd *cmd);
//********************************************


//**********************************************************************************************************************
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
void	fncRedirOpen(t_cmnd **cmd, char *nameFile);
void	fncRedirReWrite(t_cmnd **cmd, char *nameFile);
void	fncRedirWrite(t_cmnd **cmd, char *nameFile);
void	fncRedirHeredoc(t_cmnd **cmd, char *hereDoc);

void	fncMonitor(t_cmnd *cmd);

char	*pre_use_fnc_pipe(char *line, int *where_is_pipe, t_cmnd **command_line);
void	ctrl_c_hook(int sgn);
void    rl_replace_line(const char *buffer, int val);
char	*nameForRedir(char **line, int *nameLen, int *i, t_gnrl **gen);
char	*initLine(char *line);
int		dualArrayLen(char **array);
void	getHistoryLog(char *line, t_gnrl *gen);
t_cmnd	*preLogicWork(t_cmnd **cmd);
void	pLWinWhile(t_cmnd **tmp, t_cmnd **tmp2);
void	if_pipe(t_cmnd **command_line, t_cmnd **tmp_command_line, int *w_i_p, char *line);
int		if_echo(t_cmnd **cmd_line, char **line, int *w_i_p);
char	*cut_spaces(char *line);
char 	*ret_for_dollar_what(char **line, int j);

#endif