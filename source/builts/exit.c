#include "../../include/minishell.h"

void	level_up_down2(t_list *ptr)
{
	char	*lvl;
	char	*buf;
	int		i;

	lvl = NULL;
	while (ptr)
	{
		if (ft_strncmp("SHLVL=", ptr->str, 6) == 0)
			break ;
		ptr = ptr->next;
	}
	buf = change_ft_strrchr(ptr->str, '=');
	i = ft_atoi(buf);
	i--;
	lvl = ft_strjoin("SHLVL=", ft_itoa(i));
	ptr->str = lvl;
}

int	ms_isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ms_msg(t_list *ptr, char *argv1, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	if (argv1 != NULL)
	{
		ft_putstr_fd(argv1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (argv1 != NULL)
	{
		level_up_down2(ptr);
		exit_code = 255;
		exit(255);
	}
	else
		return (1);
	return (0);
}

static unsigned char	ms_atoi_char(t_list *ptr, char *str)
{
	int				negative;
	int				i;
	long long int	convert;

	negative = 1;
	i = 0;
	convert = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -negative;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		convert = convert * 10 + (str[i++] - '0');
		if (i > 20)
			ms_msg(ptr, str, "numeric argument required");
	}
	if ((convert - 3 >= 9223372036854775807 && negative == -1) \
		|| (convert - 1 >= 9223372036854775807 && negative == 1))
		ms_msg(ptr, str, "numeric argument required");
	return (convert * negative);
}

int	exit_built(char	**str, t_list **ptr)
{
	int	i;

	i = size_two_poineter_mas(str);
	if (i == 1)
	{
		level_up_down2(*ptr);
		exit (exit_code);
	}
	if (ms_isdigit_str(str[1]))
		return (ms_msg((*ptr), str[1], "numeric argument required"));
	if (i > 2)
		return (ms_msg((*ptr), NULL, "too many arguments"));
	if (i == 2)
	{
		exit_code = ms_atoi_char((*ptr), str[1]);
		level_up_down2(*ptr);
		exit(exit_code);
	}
	return (0);
}
