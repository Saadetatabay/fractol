/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:26:07 by satabay           #+#    #+#             */
/*   Updated: 2025/09/27 17:45:27 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	my_close(t_fractal *fractol)
{
	mlx_destroy_image(fractol -> mlx_conn, fractol -> img.img_ptr);
	mlx_destroy_window(fractol -> mlx_conn, fractol -> mlx_wind);
	mlx_destroy_display(fractol -> mlx_conn);
	free(fractol -> mlx_conn);
	//free(fractol);
	exit(0);
	return (0);
}

int key(int keysym,t_fractal *fractol)
{
	if (keysym == 65307)
	{
		mlx_destroy_image(fractol -> mlx_conn, fractol -> img.img_ptr);
		mlx_destroy_window(fractol -> mlx_conn, fractol -> mlx_wind);
		mlx_destroy_display(fractol -> mlx_conn);
		free(fractol -> mlx_conn);
		exit(0);
		return (0);
	}
	else if (keysym == XK_Right)
		fractol -> a += 0.5;
	else if (keysym == XK_Left)
		fractol -> a += -0.5;
	else if (keysym == XK_Up)
		fractol -> b += 0.5;
	else if (keysym == XK_Down)
		fractol -> b -= 0.5;
	else if (keysym == XK_4)
		fractol -> zomm_in *= 0.95;
	else if (keysym == XK_minus)
		fractol -> zomm_in *= 1.05;    
	draw(fractol);
	return (0);
}

void    event_init(t_fractal *farcatl)
{
	mlx_hook(farcatl->mlx_wind, 2, 1L << 0, key, farcatl); //keypress
	//mlx_hook(farcatl->mlx_wind,4,1L<<2,mouse,farcatl); //button press
	mlx_hook(farcatl -> mlx_wind, 17, 1L << 17, my_close, farcatl); //destroy notify
}

double ft_atof(const char *str)
{
	double	result;
	double	result1;
	int	i;
	int sign;

	result = 0.0;
	result1 = 0.0;
	int	temp;
	int j;
	temp = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while(str[i] && str[i]!='.')
	{
		result*=10;
		result += str[i] - '0';
		i++;	
	}
	if(str[i] == '.')
		i++;
	j = 0;
	while(str[i])
	{
		temp = str[i] - '0';
		result1 = result1 * 10 + temp ;
		i++;
		j++;
	}
	while (j--)
	{
		result1 *= 0.1;
	}
	
	return(result + result1);
}