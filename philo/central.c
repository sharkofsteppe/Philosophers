/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:41:57 by gesperan          #+#    #+#             */
/*   Updated: 2021/07/09 16:42:00 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libra.h"

void	destroy(t_p *p)
{
	int	i;

	i = -1;
	while (++i < p->num_of_philos)
		pthread_detach(p->philos[i].thread_id);
	i = -1;
	while (++i < p->num_of_philos)
		pthread_mutex_destroy(&(p->forks[i]));
	pthread_mutex_destroy(&(p->print));
	pthread_mutex_destroy(&(p->meal));
}

void	death_check(t_p *p, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < p->num_of_philos && p->death != 1)
		{
			pthread_mutex_lock(&(p->meal));
			if (time_diff(philo[i].last_meal, timestamp())
				> (unsigned long long)p->time_to_die)
			{
				print_that(p, i, "is dead");
				p->death = 1;
			}
			pthread_mutex_unlock(&(p->meal));
			usleep(100);
		}
		if (p->n_t_p_m_e != -1)
			exiter(p);
		if (p->fedup == 1 || p->death == 1)
			break ;
	}
}

void	eatin(t_philo *philo)
{
	t_p	*p;

	p = philo->connect;
	pthread_mutex_lock(&(p->forks[philo->left_fork]));
	print_that(p, philo->id, "has taken a fork");
	pthread_mutex_lock(&(p->forks[philo->right_fork]));
	print_that(p, philo->id, "has taken a fork");
	pthread_mutex_lock(&(p->meal));
	print_that(p, philo->id, "is eating");
	pthread_mutex_unlock(&(p->meal));
	philo->last_meal = timestamp();
	ft_usleep(p->time_to_eat, p);
	philo->ate += 1;
	pthread_mutex_unlock(&(p->forks[philo->left_fork]));
	pthread_mutex_unlock(&(p->forks[philo->right_fork]));
}

void	*play(void *voidphilo)
{
	t_philo	*philo;
	t_p		*p;

	philo = (t_philo *)voidphilo;
	p = philo->connect;
	if (philo->id % 2)
		usleep(20000);
	while (p->death != 1)
	{
		eatin(philo);
		if (p->fedup == 1)
			break ;
		print_that(p, philo->id, "is sleeping");
		ft_usleep(p->time_to_sleep, p);
		print_that(p, philo->id, "is thinking");
	}
	return (NULL);
}

int	launch(t_p *p)
{
	int	i;

	p->first_time = timestamp();
	i = 0;
	while (i < p->num_of_philos)
	{
		if (pthread_create(&(p->philos[i].thread_id),
				NULL, play, &(p->philos[i])))
			return (3);
		p->philos[i].last_meal = timestamp();
		i++;
	}
	death_check(p, p->philos);
	destroy(p);
	return (0);
}
