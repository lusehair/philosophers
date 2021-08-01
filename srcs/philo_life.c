#include "../includes/philo.h"

int     is_sleep(t_table *table, int index)
{
    table->philos[index].state = 'A';
    printf("%ld ms Philo %d is sleeping\n", instanttime(table), index + 1);
    safe_sleep(table, 'S');
    //printf("%ld ms Philo %d is thinkng\n",instanttime(table), index + 1 );
    table->philos[index].state = 'A';
    return(0);
}

/*
// check si des philos sont morts, si oui alors il unlock son mutex et le destroy si non il renvoie index;
// si le thread appellant est lui même mort, alors il affiche le message de sa mort. 
*/ 


void    philo_end_eat(t_table *table, int index)
{
        if(table->philos[index].state == 'E')
        {
            pthread_mutex_unlock(table->philos[index].forkLeft);
            pthread_mutex_unlock(table->philos[index].forkRight);
            //pthread_mutex_destroy(table->philos[index].forkLeft);
            //pthread_mutex_destroy(table->philos[index].forkRight);
        }
}


int     philo_dead(t_table *table, int index)
{
    int i; 
    //char state;

    i = 0; 
    //if(table->philos[index].state == 'D')
    monitor(table,index,'D');   
    while(i < table->data.elements)
    {
        //state = table->philos[index].state;
        // D for DEAD and M for EatMax
        if(table->philos[i].state == 'E')
        {
            if(index != -1)
            {
                pthread_mutex_unlock(table->philos[index].forkLeft);
                pthread_mutex_unlock(table->philos[index].forkRight);
                //pthread_mutex_destroy(table->philos[index].forkLeft);
                //pthread_mutex_destroy(table->philos[index].forkRight);
            }
            return (1);
        }
        i++;
    }

    return(0);
}

/*
// philosopher life with all process functions 
// ret = -1 if the philo died;
// ret = 1 if philo as eat enought 
*/ 

void     *philo_life(void *tab)
{
    int fork;
    int index;
    t_human *human;
    t_table *table;

    human = tab;
    table = human->table; 
    fork = 1;
    index = human->index;
    ft_free_safe(tab);
    if(table->philos[index].PIO == 'P')
        is_sleep(table, index);
    table->philos[index].lastEat = instanttime(table);
    while(g_isDead == false)
    {
        monitor(table, index, "is thinking");
        fork = 1;
        while(fork != 0)
        {
            fork = if_take_one_fork(table,index);
        }
        fork = 1;
        while(fork)
        {               
            fork = if_take_two_fork(table,index);
        }
        fork = is_eating(table, index); 
        //  if(fork == table->data.maxEat)
        //     return(NULL);
    }
    return(NULL);
}
