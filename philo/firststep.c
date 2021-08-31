/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firststep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:19:40 by gesperan          #+#    #+#             */
/*   Updated: 2021/06/06 13:19:42 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libra.h"

int	errors(int error)
{
	if (error == 1)
	{
		ft_putstr_fd("ERROR\nWrong arguments\n", 1);
		return (error);
	}
	if (error == 2)
	{
		ft_putstr_fd("ERROR\nMutex initialization\n", 1);
		return (error);
	}
	if (error == 3)
	{
		ft_putstr_fd("ERROR\nThread creation\n", 1);
		return (error);
	}
	return (0);
}

void	init_philo_data(t_p *p)
{
	int	i;

	i = p->num_of_philos;
	while (--i >= 0)
	{
		p->philos[i].id = i;
		p->philos[i].ate = 0;
		p->philos[i].left_fork = i;
		p->philos[i].right_fork = (i + 1) % p->num_of_philos;
		p->philos[i].last_meal = 0;
		p->philos[i].connect = p;
	}
}

int	init_mutexes(t_p *p)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(p->meal), NULL))
		return (2);
	if (pthread_mutex_init(&(p->print), NULL))
		return (2);
	while (i < p->num_of_philos)
	{
		if (pthread_mutex_init(&(p->forks[i]), NULL))
			return (2);
		i++;
	}
	return (0);
}

int	init_everything(t_p *p, int argc, char **argv)
{
	p->num_of_philos = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->death = 0;
	p->fedup = 0;
	if (p->num_of_philos < 1 || p->time_to_die < 60 || p->time_to_eat < 60
		|| p->time_to_sleep < 60 || p->num_of_philos > 200)
		return (1);
	if (argc == 6)
		p->n_t_p_m_e = ft_atoi(argv[5]);
	else
		p->n_t_p_m_e = -1;
	init_philo_data(p);
	return (init_mutexes(p));
}

int	main(int argc, char **argv)
{
	int	ret;
	t_p	p;

	ret = 0;
	if (argc < 5 || argc > 6)
		return (errors(1));
	ret = init_everything(&p, argc, argv);
	if (ret)
		return (errors(ret));
	ret = launch(&p);
	if (ret)
		return (errors(ret));
	return (0);
}
