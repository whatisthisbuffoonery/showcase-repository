#include "h_minirt.h"

//campus system should be calling this one
void	buf_edit_uint(t_rt *rt, t_color rgb/*no ptr*/, int x, int y)
{
	unsigned int	c[3];
	unsigned int	*buf;
	int				line;

	/*pass x, y, colour from caller*/
	/*skip OOB check*/
	line = rt->line / rt->bypp;
	buf = &rt->ubuf[x + (y * line)];
	c[0] = (unsigned int)(fminf(fmaxf(rgb.r, 0.0f), 1.0f) * 255.0f);
	c[1] = (unsigned int)(fminf(fmaxf(rgb.g, 0.0f), 1.0f) * 255.0f);
	c[2] = (unsigned int)(fminf(fmaxf(rgb.b, 0.0f), 1.0f) * 255.0f);
	*buf = ((c[0] << 16) | (c[1] << 8) | c[2]);
}

void	buf_edit_char(t_rt *rt, t_color rgb/*no ptr*/, int x, int y)
{
	unsigned int	c[3];
	char			*buf;
	int				line;

	line = rt->line;
	buf = &rt->buf[(x * rt->bypp) + (y * line)];
	c[0] = (unsigned int)(fminf(fmaxf(rgb.r, 0.0f), 1.0f) * 255.0f);
	c[1] = (unsigned int)(fminf(fmaxf(rgb.g, 0.0f), 1.0f) * 255.0f);
	c[2] = (unsigned int)(fminf(fmaxf(rgb.b, 0.0f), 1.0f) * 255.0f);
	*(unsigned int *)buf = ((c[0] << 16) | (c[1] << 8) | c[2]);
}
