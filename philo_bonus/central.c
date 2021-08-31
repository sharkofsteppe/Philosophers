/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 18:08:30 by gesperan          #+#    #+#             */
/*   Updated: 2021/07/09 18:08:43 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librab.h"

void	destroy(t_p *p)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < p->num_of_philos)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < p->num_of_philos)
				kill(p->philos[i].pid, SIGKILL);
			break ;
		}
	}
	sem_close(p->forks);
	sem_close(p->meal_check);
	sem_close(p->print);
}

void	eatin(t_philo *philo)
{
	t_p	*p;

	p = philo->connect;
	sem_wait(p->forks);
	print_that(p, philo->id, "has taken a fork");
	sem_wait(p->forks);
	print_that(p, philo->id, "has taken a fork");
	sem_wait(p->meal_check);
	print_that(p, philo->id, "is eating");
	sem_post(p->meal_check);
	philo->last_meal = timestamp();
	ft_usleep(p->time_to_eat, p);
	philo->ate += 1;
	sem_post(p->forks);
	sem_post(p->forks);
}

void	cycler(t_p *p, t_philo *philo, int i)
{
	sem_wait(p->meal_check);
	if (time_diff(philo->last_meal, timestamp())
		> (unsigned long long)p->time_to_die)
	{
		print_that(p, i, "is dead");
		p->death = 1;
		exit(1);
	}
	sem_post(p->meal_check);
	usleep(1000);
}

void	*death_check(void *voidphilo)
{
	t_philo	*philo;
	t_p		*p;
	int		i;

	philo = (t_philo *)voidphilo;
	p = philo->connect;
	while (1)
	{
		i = -1;
		while (++i < p->num_of_philos && p->death != 1)
		{
			cycler(p, philo, i);
		}
		if (p->death == 1 || (philo->ate >= p->n_t_p_m_e && p->n_t_p_m_e != -1))
			break ;
	}
	return (NULL);
}

void	play(void *voidphilo)
{
	t_philo	*philo;
	t_p		*p;

	philo = (t_philo *)voidphilo;
	p = philo->connect;
	philo->last_meal = timestamp();
	pthread_create(&(philo->death_check), NULL, death_check, voidphilo);
	if (philo->id % 2)
		usleep(20000);
	while (p->death != 1)
	{
		eatin(philo);
		if (philo->ate >= p->n_t_p_m_e && p->n_t_p_m_e != -1)
			break ;
		print_that(p, philo->id, "is sleeping");
		ft_usleep(p->time_to_sleep, p);
		print_that(p, philo->id, "is thinking");
	}
	pthread_join(philo->death_check, NULL);
	if (p->death)
		exit(1);
	exit(0);
}
