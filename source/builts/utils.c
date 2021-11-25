#include "../../include/minishell.h"

// unset and export BUILT*****************************
int	checking_validity_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_error_func(char *str1, char *str2)
{
	char	*print_error;

	exit_code = 1;
	print_error = ft_strjoin(str1, str2);
	ft_putstr_fd(print_error, STDOUT_FILENO);
	ft_putstr_fd(": not a valid identifier", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
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
