#include "librab.h"

int	errors(int error)
{
	if (error == 1)
	{
		ft_putstr_fd("ERROR\nWrong arguments", 1);
		return (error);
	}
	if (error == 2)
	{
		ft_putstr_fd("ERROR\nDuring creation of process", 1);
		return (error);
	}
	if (error == 3)
	{
		ft_putstr_fd("ERROR\nSEM FAIL", 1);
		return (error);
	}
	return (0);
}

unsigned long long	timestamp(void)
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
	sem_wait(p->print);
	if (!(p->death))
		printf("%lld %i %s\n", timestamp() - p->first_time, phil + 1, str);
	sem_post(p->print);
	return ;
}
