/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:58:38 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/16 18:29:23 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	destroy(s_table *table)
{
	int	i;

	i = 0;
	if (table->data.elements == 1)
		pthread_join(table->philos[i].tPhilo, NULL);
	while (i < table->data.elements)
	{
		if (table->data.elements > 1)
			pthread_join(table->philos[i].tPhilo, NULL);
		if(table->data.elements == 1)
			pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->data.monitor);
	pthread_mutex_destroy(&table->data.time);
	ft_free_safe(table->forks);
	ft_free_safe(table->philos);
	return (0);
}

int	arg_checker(int ac, char**av)
{
	int		i;
	int		c;

	i = 1;
	c = 0;
	while (i < ac)
	{
		while (c < (int)ft_strlen(av[i]))
		{
			if (!ft_isdigit(av[i][c]))
			{
				printf("not a good value (only numbers required)\n");
				return (1);
			}
			c++;
		}
		c = 0;
		i++;
	}
	if (ac != 5 && ac != 6)
	{
		printf("must be 4 or 5 arguments. Goodbye\n");
		return (1);
	}
	return (value_checker(ac, av));
}

int	value_checker(int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
		{
			printf("|%s| is not a good value (more than) 0)\n", av[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	diner_launcher(s_table *table)
{
	int		i;
	s_human	*human;

	i = 0;
	table->countmax = 1;
	while (i < table->data.elements)
	{
		human = malloc(sizeof(s_human));
		if(human == NULL)
			return(-1);
		human->index = i;
		human->table = table;
		if ((pthread_create(&table->philos[i].tPhilo, NULL, &philo_life,
					(void*)human)))
		{
			ft_free_safe(human);
			printf("A thread cannot be create\n");
			return (0);
		}
		i++;
	}
	watcher(table);
	m_isdead(table,'W');
	destroy(table);
	ft_free_safe(human);
	return (i);
}

int	main(int ac, char **av)
{
	s_table	*table;

	table = malloc(sizeof(s_table));
	if(table == NULL)
		return(1);
	if (inis_data(&table->data, ac, av))
		return (1);
	table->philos = inis_philos(table->data);
	table->forks = init_forks(table->data);
	if(table->philos == NULL || table->forks == NULL)
		return(1);
	fork_dispatch(table);
	diner_launcher(table);
	free(table);
	return (0);
}
