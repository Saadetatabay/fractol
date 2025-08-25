#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

int main()
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (!mlx)
        return 1;

    win = mlx_new_window(mlx, 200, 100, "RGB Bitleri");

    // Renkler (0xRRGGBB)
    int red   = 0xFF0000; // kırmızı
    int green = 0x00FF00; // yeşil
    int blue  = 0x0000FF; // mavi
    int white = 0xFFFFFF; // beyaz

    // Pikselleri çiz
    mlx_pixel_put(mlx, win, 20, 20, red); // x y koordinatlarına bu bir piksel çizer
    mlx_pixel_put(mlx, win, 60, 20, green);
    mlx_pixel_put(mlx, win, 100, 20, blue);
    mlx_pixel_put(mlx, win, 140, 20, white);

    // Hex değerlerini ekrana yazdır
    printf("Red   = 0x%06X\n", red);
    printf("Green = 0x%06X\n", green);
    printf("Blue  = 0x%06X\n", blue);
    printf("White = 0x%06X\n", white);

    mlx_loop(mlx);
    return 0;
}
