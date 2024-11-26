# include "../includes/cub3d.h"

time_t  get_current_time(void)
{
    struct timeval now_time;

    gettimeofday(&now_time, NULL);
    return(now_time.tv_sec * 1000000 + now_time.tv_usec);
}