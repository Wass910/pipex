#include "pipex.h"

int	ft_count_str(char *s1, char *s2)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (s1[i] != '\0' && s1 != NULL)
		i++;
	while (s2[e] != '\0' && s2)
	{
		e++;
		i++;
	}
	i = i + 2;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	j = 0;
	tmp[i] = '/';
	i++;
	while (src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		++j;
	}
	tmp[i++] = '\0';
	return (tmp);
}