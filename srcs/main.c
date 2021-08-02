#include "../includes/philo.h"




int     main(int ac, char **av)
{
  t_table table;

    if (init_data(&table.data, ac, av) == -1)
        return(-1);
    table.philos = init_philos(table.data);
    table.forks = init_forks(table.data);
    g_isDead = false;
    fork_dispatch(&table);
    diner_launcher(&table);
    ft_free_safe(table.forks);
    ft_free_safe(table.philos);
    
    return (0);

}