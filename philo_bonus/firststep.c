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

#include "librab.h"

void	init_philo_data(t_p *p)
{
	int	i;

	i = p->num_of_philos;
	while (--i >= 0)
	{
		p->philos[i].id = i;
		p->philos[i].ate = 0;
		p->philos[i].last_meal = 0;
		p->philos[i].connect = p;
	}
}

int	init_sem(t_p *p)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/mealcheck");
	p->meal_check = sem_open("/mealcheck", O_CREAT, S_IRWXU, 1);
	p->forks = sem_open("/forks", O_CREAT, S_IRWXU, p->num_of_philos);
	p->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	if (p->meal_check == SEM_FAILED || p->forks == SEM_FAILED
		|| p->print == SEM_FAILED)
		return (3);
	return (0);
}

int	init_everything(t_p *p, int argc, char **argv)
{
	p->num_of_philos = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->death = 0;
	if (p->num_of_philos < 1 || p->time_to_die < 60 || p->time_to_eat < 60
		|| p->time_to_sleep < 60 || p->num_of_philos > 200)
		return (1);
	if (argc == 6)
		p->n_t_p_m_e = ft_atoi(argv[5]);
	else
		p->n_t_p_m_e = -1;
	init_philo_data(p);
	return (init_sem(p));
}

int	launch(t_p *p)
{
	int	i;

	p->first_time = timestamp();
	i = -1;
	while (++i < p->num_of_philos)
	{
		p->philos[i].pid = fork();
		if (p->philos[i].pid == 0)
			play(&(p->philos[i]));
		usleep(100);
	}
	destroy(p);
	return (0);
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
	launch(&p);
	return (0);
}
