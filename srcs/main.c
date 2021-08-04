/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:58:38 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/04 21:07:08 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	destroy(t_table *table)
{
	int	i;

	i = 0;
	if (table->data.elements == 1)
		pthread_detach(table->philos[i].tPhilo);
	while (i < table->data.elements)
	{
		if (table->data.elements)
			pthread_join(table->philos[i].tPhilo, NULL);
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

int	diner_launcher(t_table *table)
{
	int		i;
	t_human	*human;

	i = 0;
	while (i < table->data.elements)
	{
		human = malloc(sizeof(t_human));
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
	destroy(table);
	return (i);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (init_data(&table.data, ac, av))
		return (-1);
	table.philos = init_philos(table.data);
	table.forks = init_forks(table.data);
	g_isDead = false;
	fork_dispatch(&table);
	diner_launcher(&table);
	return (0);
}
