#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 1

# include <stdio.h>
# include <unistd.h>
<<<<<<< HEAD
# include "../source/Libft/libft.h"
# include <readline/readline.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include "./structs_minishell.h"

=======
# include <readline/readline.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include "./structs_minishell.h"
# include "../source/Libft/libft.h"
>>>>>>> logic

//utils prototype*****************************
void	ft_perror_shell(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*change_ft_strrchr(const char *s, int c);
//********************************************

//BUILT prototype*****************************
void	levelUpBash(t_list *ptr);
void	initialEnv(char **envp, t_list **ptr, int i);
void	printEnvBuilt(t_list *ptr);
void	pwdBuilt();
<<<<<<< HEAD

t_list	*ft_lstlast(t_list *lst);

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
void	fncRedirOpen(t_cmnd **cmd, char *nameFile);
void	fncRedirReWrite(t_cmnd **cmd, char *nameFile);
void	fncRedirWrite(t_cmnd **cmd, char *nameFile);
void	fncRedirHeredoc(t_cmnd **cmd, char *hereDoc);

int		logica(t_gnrl **zik);

void	cdBuilt(t_list *ptr, t_gnrl *zik);
void	echoBuilt(t_gnrl *zik);
void	exportBuilt(t_list *ptr, t_gnrl *zik);
void	unsetBuilt(t_list *ptr, t_gnrl *zik);
=======
//********************************************
>>>>>>> logic

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
void	pid_children(t_map *st, char **envp, t_gnrl **zik);
void	create_pipe(t_map *st);
void	ft_perror(char *str);
int		ft_strcmp(const char *s1, const char *s2);
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
void	fncRedirOpen(t_cmnd **cmd, char *nameFile);
void	fncRedirReWrite(t_cmnd **cmd, char *nameFile);
void	fncRedirWrite(t_cmnd **cmd, char *nameFile);
void	fncRedirHeredoc(t_cmnd **cmd, char *hereDoc);

int		logica(t_gnrl **zik);

void	cdBuilt(t_list *ptr, t_gnrl *zik);
void	echoBuilt(t_gnrl *zik);
void	exportBuilt(t_list *ptr, t_gnrl *zik);
void	unsetBuilt(t_list *ptr, t_gnrl *zik);

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

#endif