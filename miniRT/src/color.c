#include "h_minirt.h"

t_color	color_add(t_color a, t_color b)
{
	return((t_color) {a.r + b.r, a.g + b.g, a.b + b.b});
}

t_color	color_mul(t_color a, t_color b)
{
	return((t_color) {a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color	color_scale(t_color a, double b)
{
	return((t_color) {a.r * b, a.g * b, a.b * b});
}
