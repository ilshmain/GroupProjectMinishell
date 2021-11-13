#include "../../include/minishell.h"

char	*ft_strrchrchange(const char *s, int c)
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

int	pwdBuilt(char **envp)
{
	int		i;
	char	*pwd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			pwd = ft_strrchrchange(envp[i], '=');
		i++;
	}
	write(STDOUT_FILENO, &pwd, ft_strlen(pwd));
	return (1);
}