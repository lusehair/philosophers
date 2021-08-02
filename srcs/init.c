#include "../includes/philo.h"



// Give the address of the good forks to the good philos
void    fork_dispatch(t_table *table)
{
    int p; 
    int f;
    
    p = 1;
    f = 0;
    table->philos[0].forkRight =  &table->forks[table->data.elements - 1 ]; 
    table->philos[0].forkLeft =  &table->forks[0]; 
    while(p < table->data.elements)
    {
        table->philos[p].forkLeft =  &table->forks[f];
        table->philos[p].forkRight =  &table->forks[f + 1];
        f++;
        p++;
    }
}

t_philo     *init_philos(t_data data)
{
    t_philo *philos; 
    int i;

    i = 0;
    philos = malloc(sizeof(t_philo) * data.elements); 
    if(philos == NULL)
        return(NULL);
    while(i < data.elements)
    {
        philos[i].index = i;
        if(i%2)
            philos[i].PIO = 'I';
        else
            philos[i].PIO = 'P';
        if (data.maxEat != -1)
            philos[i].numEat = 0;
        philos[i].state = 'A';
        i++;

    }
    i--;
    return(philos);
}

int     init_data(t_data *data, int ac, char **av)
{

    if(ac != 5 && ac != 6)
    {
       printf("You have %d arguments, must be 4 or 5 arguments. Goodbye\n", ac);
       return(-1);
    }
    data->realtime = realtime();
    data->timeDie = (unsigned long)ft_atoi(av[2]);
    data->timeEat = (unsigned long)ft_atoi(av[3]);
    data->timeSleep = (unsigned long)ft_atoi(av[4]);
    data->elements = ft_atoi(av[1]);
    pthread_mutex_init(&data->monitor,NULL);
    puts("merde");
    //data->isDead = false; 
    g_isDead = false;
    if(ac == 6)
        data->maxEat = ft_atoi(av[5]);
    else
        data->maxEat = -1;

    // if(data->timeDie < 0 || data->timeEat < 0 || data->timeSleep < 0 ||
    // data->maxEat == 0 || data->elements < 0)
    //     return (-1);
    return(0);
}

pthread_mutex_t     *init_forks(t_data data)
{
    int i; 
    int ret;
    pthread_mutex_t *forks;
    
    i = 0; 
   forks = malloc(sizeof(pthread_mutex_t) * data.elements);
   while(i < data.elements)
   {
       ret = pthread_mutex_init(&forks[i], NULL);
       if(ret)
        return (NULL);
    i++;
   }
   return (forks);
}



int     diner_launcher(t_table *table)
{
    int i; 
    t_human *human; 

    

    i = 0;

    while(i < table->data.elements)
    {
        human = malloc(sizeof(t_human));
        human->index = i; 
        human->table = table;

        if((pthread_create(&table->philos[i].tPhilo, NULL, &philo_life, (void*)human)))
        {
            printf("Sorry, the philo %d (thread) can\'t eat : End Of Execution, Goodbye (!CREATE)\n", i +1);
            return (0);
        }
        //usleep(200);
        i++;
    }
    watcher(table);
    pthread_mutex_destroy(&table->data.monitor);

    i = 0;
    while(i < table->data.elements)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    i = 0;
    // while(i < table->data.elements)
    // {
    //     free(&table->philos[i]);
    // }
    return (i);
}
