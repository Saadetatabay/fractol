#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#define WIDTH	400
#define HEIGHT	400

int main(){
    void	*mlx_connection; //minilibx kütüphanesiyle bağlantıyı tutacak
	void	*mlx_window; //olusturulacak pencereyi tutacak

	mlx_connection = mlx_init(); //mlx_init bir bağlantı pointeri döner
	if (mlx_connection == NULL)
	{
		printf("fail connection");
		return (1);
	}
	mlx_window = mlx_new_window(mlx_connection,HEIGHT,WIDTH,"window"); //bağlantıyı kullanarak pencere açar
	if (mlx_window == NULL)
	{
		printf("fail to window");
		mlx_destroy_display(mlx_connection);
		free(mlx_connection);
		return(1);
	}
	sleep(5);
	//mlx_loop(mlx_connection); //pencere açık tutulur
	mlx_destroy_window(mlx_connection,mlx_window); //açık olan pencereyi kapatır
	mlx_destroy_display(mlx_connection); //minilbx bağlantısını kapatır
	free(mlx_connection);
}
