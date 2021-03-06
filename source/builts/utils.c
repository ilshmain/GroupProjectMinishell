/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:32:42 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:32:44 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// unset and export BUILT*****************************
int	checking_validity_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '=')
		i++;
	if (i == (int)ft_strlen(str))
		return (-1);
	if (ft_isalpha(str[i]) != 0)
	{
		while (str[i])
		{
			if (ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0)
				return (1);
			i++;
		}
	}
	else
		return (-1);
	return (0);
}

void	print_error_func(char *str1, char *str2)
{
	char	*print_error;

	g_exit_code = 1;
	print_error = ft_strjoin(str1, str2);
	ft_putstr_fd(print_error, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(print_error);
	print_error = NULL;
}

//****************************************************

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1)
		return (1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*change_ft_strrchr(const char *s, int c)
{
	int	k;
	int	a;

	k = 0;
	a = 0;
	while (s[a])
		a++;
	while (k < a + 1)
	{
		if (s[k] == (char)c)
		{
			while (s[k] != s[a])
				a--;
			return ((char *)s + (a + 1));
		}
		k++;
	}
	return (0);
}

void	print_error(char *str, char *str1)
{
	ft_putstr_fd("minishell$: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
}
