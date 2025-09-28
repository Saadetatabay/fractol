/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:29:07 by satabay           #+#    #+#             */
/*   Updated: 2025/09/27 15:32:30 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

double	scale(double num, double new_min, double new_max, double old_max)
{
	return (((num - 0) * (new_max - new_min) / (old_max - 0)) + new_min);
}

void	mandel_vs_julia(int x, int y, t_fractal *fractol)
{
	if (!ft_strncmp(fractol->name, "mandelbrot", 10))
	{
		fractol -> z.real_x = 0;
		fractol -> z.imaginary_y = 0;
		fractol -> c.real_x = scale(x, -2, 2, 0, WIDTH) * fractol -> zomm_in + fractol -> a;
		fractol -> c.imaginary_y = scale(y, 2, -2, 0, HEIGHT) * fractol->zomm_in + fractol->b;
	}
	else
	{
		fractol -> z.real_x = scale(x, -2, 2, 0, WIDTH) * fractol -> zomm_in + fractol -> a;
		fractol -> z.imaginary_y = scale(y, 2, -2, 0, HEIGHT) * fractol -> zomm_in + fractol -> b;
		fractol -> c.real_x = fractol -> julia_r;
		fractol -> c.imaginary_y = fractol -> julia_i;
	}
}

void	params_error(void)
{
	write(2, "wrong params", 12);
	write(2, "valid params are:\n", 18);
	write(2, "./fractol Mandelbrot\n./fractol Julia <real> <imaginary>\n", 57);
}
