/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 18:30:45 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/17 15:19:02 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	m_numeat(t_table *table, int index, char mode, char arg)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->philos[index].muteat);
	if (mode == 'R' && arg == 'N')
		ret = table->philos[index].numEat;
	else if (mode == 'R' && arg == 'E')
		ret = table->philos[index].lastEat;
	else if (mode == 'W' && arg == '+')
		table->philos[index].numEat++;
	else if (mode == 'W' && arg == '-')
		table->philos[index].numEat = -1;
	else if (mode == 'W' && arg == 'D')
		table->philos[index].numEat = -2;
	else if (mode == 'W' && arg == 'E')
		table->philos[index].lastEat = instanttime(table);
	pthread_mutex_unlock(&table->philos[index].muteat);
	return (ret);
}

int	m_isdead(t_table *table, char mode)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->data.mdead);
	if (mode == 'R')
		ret = table->data.isdead;
	else
		table->data.isdead = 1;
	pthread_mutex_unlock(&table->data.mdead);
	return (ret);
}


void	routine(t_table *table, int index)
{
	while (!(m_isdead(table, 'R')))
	{
		if (m_numeat(table, index, 'R', 'N') == table->data.maxEat)
			break ;
		monitor(table, index, "is thinking");
		if_take_one_fork(table, index);
		if_take_two_fork(table, index);
		is_eating(table, index);
		is_sleep(table, index);
	}
	return ;
}

int		the_death(t_table *table, int i)
{
	if ((instanttime(table) - m_numeat(table, i, 'R', 'E')
					> table->data.timeDie && (m_numeat(table, i, 'R', 'N') != table->data.maxEat)))
			{
				if(!(table->data.maxEat != -1 && m_numeat(table, i, 'R', 'N') != table->data.maxEat))
				{
					monitor(table, i, "died");
					return (1);
				}
			}
	return (0);
}