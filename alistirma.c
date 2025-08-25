#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    void	*mlx_ptr;

    mlx_ptr = mlx_init(); //minilibx kütüp ile bağlantı kurar
	if (mlx_ptr == NULL)
		return (1);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}