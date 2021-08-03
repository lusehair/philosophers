#ifndef STRUCTS_H
# define STRUCTS_H

#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/time.h>
#include "philo.h"


bool  g_isDead;


/* 
// STRUCTURES 
*/ 

// typedef struct t_fork
// {
//     int index;
//     char isTaken;
//     void *AddrPhilo;
//     pthread_mutex_t mFork;  

// }               t_fork;




typedef struct t_philo
{
    int index;
    pthread_mutex_t *forkLeft;
    pthread_mutex_t *forkRight;
    int numEat;
    unsigned long lastEat;
    char PIO;
    pthread_t tPhilo;
    char state; 
    bool *isDead;
}               t_philo;

typedef struct t_data
{
    int elements;
    unsigned long timeDie;
    unsigned long timeEat;
    unsigned long timeSleep;
    int maxEat;
    unsigned long realtime;
    bool isDead; 
    pthread_mutex_t monitor;
    pthread_mutex_t time;


}              t_data;

enum state{
    notinit = -2,
    dead = -1,
    took_a_fork = 1,
    thinking = 0,
    eating = 4,
    sleeping = 3,
    init = 2,
};

typedef struct t_table
{
    t_data data;
    pthread_mutex_t *forks;
    t_philo *philos;
}               t_table;

typedef struct {
    t_table *table;
    int index;
} t_human;




#endif 