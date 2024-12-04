# include "../includes/cub3d_bonus.h"

time_t  get_current_time(void)
{
    struct timeval now_time;

    gettimeofday(&now_time, NULL);
    return(now_time.tv_sec * 1000000 + now_time.tv_usec);
}

double len_2pt(t_vector *v1, t_vector *v2)
{
    double  sqr;
    double x1;
    double y1;
    double x2;
    double y2;

    x1 = v1->x;
    y1 = v1->y;
    x2 = v2->x;
    y2 = v2->y;
    sqr = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return (sqr);
}

int color_range(int color_element)
{
    if (color_element > 255)
    {
        return (255);
    }
    if (color_element < 0)
    {
        return (0);
    }
    return (color_element);
}