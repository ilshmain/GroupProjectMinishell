#include "../../include/minishell.h"

void	ft_perror(char *str)
{
	perror(str);
	return ;
}

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