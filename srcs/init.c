/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:01:34 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/16 18:31:46 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	fork_dispatch(s_table *table)
{
	int	p;
	int	f;

	p = 1;
	f = 0;
	table->philos[0].forkRight = &table->forks[table->data.elements - 1 ];
	table->philos[0].forkLeft = &table->forks[0];
	while (p < table->data.elements)
	{
		table->philos[p].forkLeft = &table->forks[f];
		table->philos[p].forkRight = &table->forks[f + 1];
		f++;
		p++;
	}
}

s_philo	*inis_philos(s_data data)
{
	s_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(s_philo) * data.elements);
	if (philos == NULL)
		return (NULL);
	while (i < data.elements)
	{
		philos[i].index = i;
		if (i % 2)
			philos[i].PIO = 'I';
		else
			philos[i].PIO = 'P';
		if (data.maxEat != -1)
			philos[i].numEat = 0;
		pthread_mutex_init(&philos[i].muteat, NULL);
		i++;
	}
	i--;
	return (philos);
}

int	inis_data(s_data *data, int ac, char **av)
{
	if (arg_checker(ac, av))
		return (1);
	data->realtime = realtime();
	data->timeDie = (unsigned long)ft_atoi(av[2]);
	data->timeEat = (unsigned long)ft_atoi(av[3]);
	data->timeSleep = (unsigned long)ft_atoi(av[4]);
	data->elements = ft_atoi(av[1]);
	data->isdead = 0;
	pthread_mutex_init(&data->monitor, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->mdead, NULL);
	if (ac == 6)
		data->maxEat = ft_atoi(av[5]);
	else
		data->maxEat = -1;
	if (data->elements == 1 && ac == 6)
		data->maxEat = -1;
	return (0);
}

pthread_mutex_t	*init_forks(s_data data)
{
	int				i;
	int				ret;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data.elements);
	if(forks == NULL)
		return(NULL);
	while (i < data.elements)
	{
		ret = pthread_mutex_init(&forks[i], NULL);
		if (ret)
			return (NULL);
		i++;
	}
	return (forks);
}