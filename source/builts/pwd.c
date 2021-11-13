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
	(void)envp;
	char	pwd[1000];

	getcwd(pwd, 1000);
	write(STDOUT_FILENO, &pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (1);
}