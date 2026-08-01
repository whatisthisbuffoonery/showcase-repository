#include "h_mlx.h"

int usage(char **v)
{
    ft_printf("Usage: %s [.fdf file]", v[0]);
    if (perspective_flag("-p"))
        ft_putstr(" [-p (optional flag)]");
    write(1, "\n", 1);
    return (1);
}
