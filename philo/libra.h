/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <gesperan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:33:16 by gesperan          #+#    #+#             */
/*   Updated: 2021/05/28 16:11:58 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRA_H
# define LIBRA_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					ate;
	int					left_fork;
	int					right_fork;
	unsigned long long	last_meal;
	pthread_t			thread_id;
	struct s_p			*connect;

}					t_philo;

typedef struct s_p
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_t_p_m_e;
	unsigned long long	first_time;
	int					death;
	int					fedup;
	pthread_mutex_t		forks[200];
	pthread_mutex_t		meal;
	pthread_mutex_t		print;
	t_philo				philos[200];

}					t_p;

int					ft_atoi(const char *str);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
unsigned long long	timestamp(void);
void				ft_usleep(unsigned long long time, t_p *p);
unsigned long long	time_diff(unsigned long long past, unsigned long long pres);
void				exiter(t_p *p);
int					launch(t_p *p);
void				*play(void *voidphilo);
void				eatin(t_philo *philo);
void				death_check(t_p *p, t_philo *philo);
void				destroy(t_p *p);
int					init_everything(t_p *p, int argc, char **argv);
int					init_mutexes(t_p *p);
void				init_philo_data(t_p *p);
int					errors(int error);
void				print_that(t_p *p, int phil, char *str);

#endif
