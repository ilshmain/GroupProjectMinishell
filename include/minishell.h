/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:49:30 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:49:34 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//utils prototype*****************************
void	ft_perror_shell(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*change_ft_strrchr(const char *s, int c);
//********************************************

//BUILT prototype*****************************
char	**clear_envp(char **envp);
char	*level_up_down(char *str);
void	check_heredoc(char **argv, t_cmnd *cmd);
int		initial_env(char **envp, t_list **ptr, int i);
int		print_env_built(t_list *ptr);
int		pwd_built(void);
int		cd_built(t_list *ptr, t_gnrl *zik, int i);
int		echo_built(t_gnrl *zik, int i, int k);
int		export_built(t_list *ptr, t_gnrl *zik);
int		unset_built(t_list *ptr, t_gnrl *zik);
int		built_func(t_gnrl *zik, t_list *ptr);
int		logica(t_gnrl **zik);
int		size_heredoc(char **argv);
int		exit_built(char	**str, t_list **ptr);
int		checking_validity_string(char *str);
void	print_error_func(char *str1, char *str2);
int		size_two_poineter_mas(char **argv);
char	**env(t_list *lst);

void	ft_lstdel(t_list *lst);
void	add_export(t_list **ptr, char *str);
//********************************************

void	fncMonitor(t_cmnd *cmd);

//char	*pre_use_fnc_pipe(char *line, int *whereIsPipe, t_cmnd **commandLine);
void	ctrl_c_hook(int sgn);
void	rl_replace_line(const char *buffer, int val);
char	*name_for_redir(char **line, int *nameLen, int *i, t_gnrl **gen);
char	*init_line(char *line);
int		dual_array_len(char **array);

//KOSTYL prototype*****************************
t_list	*ft_lstlast(t_list *lst);
//********************************************

//PIPE prototype*****************************

int		work_with_pipe(t_gnrl **zik);

char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
void	dop_func_export(t_list *ptr, t_gnrl *zik);
int		get_next_line(int fd, char **line);

char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *p1, const char *p2, size_t n);
void	pars_envp(char **envp, char	**first_argv, int i, int k);
int		pid_children(t_gnrl **zik, t_cmnd *start);
void	create_pipe(t_cmnd *cmd);
void	ft_perror(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		check_redirect(t_cmnd *cmd);
int		dup_relize(t_cmnd *cmd);
//********************************************

//**********************************************
void	exefnc(char **line, t_gnrl **gen);
int		first_fnc(char **line, t_gnrl **gen, int i);
t_cmnd	*fnc_pars(char *line, int beginOfLine, t_cmnd *commandLine);

char	**ft_split_ms(char const *s, char c);
size_t	ft_strlcat_ms(char *dst, const char *src, size_t size);
size_t	ft_strlcpy_ms(char *dst, const char *src, size_t size);
size_t	ft_strlen_ms(const char *str);
char	*ft_strchr_ms(const char *s, int c);
char	*ft_strjoin_ms(char const *s1, char const *s2);
void	error_call(char *message);

char	*ft_substr_ms(char const *s, unsigned int start, size_t len);
char	*ft_strdup_ms(const char *s1);

char	*fnc_quot(char *line, int *i, t_gnrl **gen);
char	*fnc_dquot(char **line, int *i, char **env, t_gnrl **gen);
char	*union_for_quot_str(char *line, int *i, int j);

char	*fnc_bslsh(char *line, int *i, t_gnrl **gen);

char	*fnc_dollar(char *line, int *i, char **env);
char	*dollar_assigment(char *line, int *i, int *j, char **env);

int		ft_isalnum_ms(int c);
char	*ft_strnstr_ms(const char *str1, const char *str2, size_t len);
int		ft_strcmp_ms(const char *s1, const char *s2);

char	*pre_use_fnc_redir(char **line, int *i, t_gnrl **gen);
char	*pre_use_str_join(char *str1, char *str2);
char	*pre_use_fnc_quot(char *line, int *i, t_gnrl **gen);
char	*pre_use_fnc_dquot(char **line, int *i, char **env, t_gnrl **gen);
char	*pre_use_fnc_dollar(char *line, int *i, char **env);

void	ft_putstr_fd_ms(char *s, int fd);
t_cmnd	*ft_lstnew_ms(void);
char	*str_cut_str(char *inStr, int startOfCut, int endOfCut);
char	**envPrisv(char **envp);
void	butils_prov(t_cmnd **command);

char	*fnc_redir(char **line, int *i, t_gnrl **gen, int ident);
void	fnc_redir_open(t_cmnd **cmd, char *nameFile);
void	fnc_redir_re_write(t_cmnd **cmd, char *nameFile);
void	fnc_redir_write(t_cmnd **cmd, char *nameFile);
void	fnc_redir_heredoc(t_list **heredoc_struct, char **add_heredoc,
			int *fd_in_work);

char	*pre_use_fnc_pipe(char *line, int *where_is_pipe, t_gnrl **gen);
void	ctrl_c_hook(int sgn);
void	rl_replace_line(const char *buffer, int val);
char	*name_for_redir(char **line, int *nameLen, int *i, t_gnrl **gen);
char	*init_line(char *line);
int		dual_array_len(char **array);
t_cmnd	*pre_logic_work(t_cmnd **cmd);
void	plw_in_while(t_cmnd **tmp, t_cmnd **tmp2);
void	if_pipe(t_cmnd **command_line, t_cmnd **tmp_command_line,
			int *w_i_p, char *line);
int		if_echo(t_cmnd **cmd_line, char **line, int *w_i_p);
char	*cut_spaces(char *line);
char	*ret_for_dollar_what(char **line, int j);
char	*pre_use_substr(char *s, unsigned int start, size_t len);
void	pu_fnc_pipe_safe_page(char *line, int *where_is_pipe,
			t_cmnd **tmp_command_line, t_cmnd **command_line);
char	*our_getenv(char *key, char **env);
int		fd_closer(int fd);
void	clear_hrd(t_list **strct);
int		comparison_first_word(char *str, char delimiter, char *compr_word);
int		get_qt_str(char *str, char sym);
char	**fake_split(char *str, char sym);
void	ffnc_in_cycle(char **line, int *i, t_gnrl **gen);
char	*space_cut_for_ffnc(char **line, int *i);
int		no_one_symbol_in_str(char *str, char sym);
char	*get_tilda(char **line, int *i);
void	bin_dir_check(char **cmd);
void	lstclear(t_cmnd **lst);
void	sign(void);

#endif
