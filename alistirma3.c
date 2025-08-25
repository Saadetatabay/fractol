#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#define WIDTH	400
#define HEIGHT	400

int main()
{
    void    *mlx_connection;
    void    *mlx_window1;
    void    *mlx_window2;

    mlx_connection = mlx_init();
    if (!mlx_connection)
    {
        printf("fail");
        return (1);
    }
    mlx_window1 = mlx_new_window(mlx_connection,WIDTH,HEIGHT,"window2");
    mlx_window2 = mlx_new_window(mlx_connection,WIDTH,HEIGHT,"window1");
    if(!mlx_window1 || !mlx_window2)
    {
        mlx_destroy_display(mlx_connection);
        free(mlx_connection);
        return (1);
    }
    sleep(5);
    //mlx_loop(mlx_connection);
    mlx_destroy_window(mlx_connection, mlx_window1);
    mlx_destroy_display(mlx_connection);
    free(mlx_connection);
}