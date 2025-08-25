#include "ft_fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	while (i < n)
	{
		c1 = (unsigned char)*(s1 + i);
		c2 = (unsigned char)*(s2 + i);
		if (c1 != c2)
			return (c1 - c2);
		if (c1 == '\0')
			return (0);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		write(fd, (s + i), 1);
		i++;
	}
}
