#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#define WIDTH	400
#define HEIGHT	400

//keycode da numara gelir keysym ile harf gelir ekrana

typedef struct my_data{
    void    *mlx_pointer; //kütüp ile bağlantı
    void    *mlx_window; //window tutan pointer
}mlx_win;

int key(int key_num,mlx_win  *data)
{
    if (key_num == 65307) //esc
    {
        printf("ESC bastim");
        mlx_destroy_window(data->mlx_pointer,data->mlx_window); //data struct pointerı old için -> ile ulaştık
        mlx_destroy_display(data->mlx_pointer);
        free(data->mlx_pointer);
        exit(0);
    }
    else{
        printf("%d bastim\n",key_num);
        fflush(stdout); // anlık çıktı gelsin diye  
    }
    return(0);
}

int main()
{
 
    mlx_win data; //hem bağlantı hem window için pointer var
    data.mlx_pointer = mlx_init();
    if(!(data.mlx_pointer))
    {
        printf("fail");
        return(1);
    }
    data.mlx_window = mlx_new_window(data.mlx_pointer,HEIGHT,WIDTH,"my window");
    mlx_hook(data.mlx_window, 2, 1L<<0, key, &data); //windowpointer,event,mask,fonksyon,fonskiyona gidecek paramtetre
    mlx_loop(data.mlx_pointer);
}