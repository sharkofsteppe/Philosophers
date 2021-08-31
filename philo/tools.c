#include "libra.h"

void	exiter(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_philos && p->philos[i].ate >= p->n_t_p_m_e)
		i++;
	if (i == p->num_of_philos)
	{
		p->fedup = 1;
		printf("everybody is fed up\n");
	}
}

unsigned	long	long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

unsigned long long	time_diff(unsigned long long past, unsigned long long pres)
{
	return (pres - past);
}

void	ft_usleep(unsigned long long time, t_p *p)
{
	long long	i;

	i = timestamp();
	while (p->death != 1)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	print_that(t_p *p, int phil, char *str)
{
	pthread_mutex_lock(&(p->print));
	if (!(p->death))
		printf("%lld %i %s\n", timestamp() - p->first_time, phil + 1, str);
	pthread_mutex_unlock(&(p->print));
	return ;
}
