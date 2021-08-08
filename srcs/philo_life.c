/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:52:14 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/07 19:27:05 by lucasseha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	if_take_one_fork(t_table *table, int index)
{
	int	ret;

	ret = 0;
	if (g_isDead == true)
		return (-1);
	if (table->philos[index].PIO == 'I')
		ret = pthread_mutex_lock(table->philos[index].forkRight);
	else
		ret = pthread_mutex_lock(table->philos[index].forkLeft);
	if (ret == 0)
		monitor(table, index, "has taken a fork");
	return (ret);
}

int	if_take_two_fork(t_table *table, int index)
{
	int	ret;

	ret = 0;
	if (g_isDead == true)
		return (-1);
	if (table->philos[index].PIO == 'I')
		ret = pthread_mutex_lock(table->philos[index].forkLeft);
	else
		ret = pthread_mutex_lock(table->philos[index].forkRight);
	return (ret);
}

int	is_eating(t_table *table, int index)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				ret;

	ret = 0;
	fork1 = table->philos[index].forkLeft;
	fork2 = table->philos[index].forkRight;
	if (table->data.maxEat != -1)
	{
		if (table->philos[index].numEat == table->data.maxEat)
		{
			table->philos[index].numEat = -1;
			return (0);
		}
		table->philos[index].numEat++;
	}
	monitor(table, index, "is eating");
	table->philos[index].lastEat = instanttime(table);
	safe_sleep(table, 'E');
	ret += pthread_mutex_unlock(fork1);
	ret += pthread_mutex_unlock(fork2);
	return (ret);
}

int	is_sleep(t_table *table, int index)
{
	monitor(table, index, "is sleeping");
	safe_sleep(table, 'S');
	return (0);
}

void	*philo_life(void *tab)
{
	int		index;
	t_human	*human;
	t_table	*table;

	human = tab;
	table = human->table;
	index = human->index;
	ft_free_safe(tab);
	table->philos[index].lastEat = instanttime(table);
	if (table->philos[index].PIO == 'P')
		is_sleep(table, index);
	while (g_isDead == false)
	{
		monitor(table, index, "is thinking");
		if_take_one_fork(table, index);
		if_take_two_fork(table, index);
		is_eating(table, index);
		if (table->philos[index].numEat == -1)
			break ;
		is_sleep(table, index);
	}
	pthread_mutex_unlock(table->philos[index].forkRight);
	pthread_mutex_unlock(table->philos[index].forkLeft);
	return (NULL);
}
