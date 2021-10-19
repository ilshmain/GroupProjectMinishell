#ifndef MSLIB_H
#define MSLIB_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>

typedef struct s_cmnd
{
	char	**command_array;
	int		flg_pipe;
	struct s_cmnd	*nextList;
}	t_cmnd;

typedef struct s_gnrl
{
	t_cmnd	*cmd;
	int		errors;
}	t_gnrl;

char	**ft_split(char const *s, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
// void	pars(char *line);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	error_call(char *message);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int		first_fnc(char **line, char **env, t_gnrl **gen);
char	*fnc_quot(char *line, int *i, t_gnrl **gen);
char	*fnc_dquot(char *line, int *i, char **env, t_gnrl **gen);
char	*fnc_bslsh(char *line, int *i,t_gnrl **gen);
char	*fnc_dollar(char *line, int *i, char **env);
char	*unionForQuotStr(char *line, int *i, int j);
int		ft_isalnum(int c);
char	*ft_strnstr(const char *str1, const char *str2, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*dollarAssigment(char *line, int *i, int j, char **env);
char	*preUseStrJoin(char *str1, char *str2);
char	*preUseFncQuot(char *line, int *i, t_gnrl **gen);
char	*preUseFncDQuot(char *line, int *i, char **env, t_gnrl **gen);
char	*preUseFncDollar(char *line, int *i, char **env);
t_cmnd	*fnc_pars(char *line, int beginOfLine, t_cmnd *commandLine);
t_cmnd	*ft_lstnew(void);

#endif
