/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:52:14 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/16 18:27:37 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	if_take_one_fork(s_table *table, int index)
{
	int	ret;

	ret = 0;
	if (table->data.elements == 1)
		return (ret);
	if (m_isdead(table, 'R'))
		return (-1);
	if (table->philos[index].PIO == 'I')
		ret = pthread_mutex_lock(table->philos[index].forkRight);
	else
		ret = pthread_mutex_lock(table->philos[index].forkLeft);
	if (ret == 0)
		monitor(table, index, "has taken a fork");
	return (ret);
}

int	if_take_two_fork(s_table *table, int index)
{
	int	ret;

	ret = 0;
	if (table->data.elements == 1)
		return (ret);
	if (m_isdead(table, 'R'))
		return (-1);
	if (table->philos[index].PIO == 'I')
		ret = pthread_mutex_lock(table->philos[index].forkLeft);
	else
		ret = pthread_mutex_lock(table->philos[index].forkRight);
	if (ret == 0)
		monitor(table, index, "has taken a fork");
	return (ret);
}

int	is_eating(s_table *table, int index)
{
	int ret;

	ret = 0;
	if(table->data.elements == 1)
		return(ret);
	if (table->data.maxEat != -1)
	{
		if (table->philos[index].numEat == table->data.maxEat)
		{
			m_numeat(table,index, 'W', '-');
			return (0);
		}
		m_numeat(table,index,'W','+');
	}
	monitor(table, index, "is eating");
	m_numeat(table,index, 'W', 'E');
	safe_sleep(table, 'E');
	pthread_mutex_unlock(table->philos[index].forkLeft);
	pthread_mutex_unlock(table->philos[index].forkRight);
	return (ret);
}

int	is_sleep(s_table *table, int index)
{
	monitor(table, index, "is sleeping");
	safe_sleep(table, 'S');
	return (0);
}

void	*philo_life(void *tab)
{
	int		index;
	s_human	*human;
	s_table	*table;

	human = tab;
	table = human->table;
	index = human->index;
	ft_free_safe(human);
	m_numeat(table,index, 'W', 'E');
	if (table->philos[index].PIO == 'P')
		is_sleep(table, index);
	while (!(m_isdead(table, 'R')))
	{
		monitor(table, index, "is thinking");
		if_take_one_fork(table, index);
		if_take_two_fork(table, index);
		is_eating(table, index);
		if (m_numeat(table,index,'R', 'N') == -1)
			break ;
		is_sleep(table, index);
	}
	pthread_mutex_unlock(table->philos[index].forkRight);
	pthread_mutex_unlock(table->philos[index].forkLeft);
	return (NULL);
}
