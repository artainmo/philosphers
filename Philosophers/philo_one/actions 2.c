#include "philo_one.h"

int dies(philosopher *p, char *tim)
{
  pthread_mutex_lock(p->dead_lock);
  if (g_dead == 1)
  {
    pthread_mutex_unlock(p->dead_lock);
    return (1);
  }
  g_dead = 1;
  dead_message(p, tim);
  pthread_mutex_unlock(p->dead_lock);
  return (1);
}

int think(philosopher *p)
{
  if (status_change(p, "\tis thinking\n") == 1)
    return (1);
  return (0);
}

int sleeps(philosopher *p)
{
  if (status_change(p, "\tis sleeping\n") == 1)
    return (1);
  usleep(p->p->time_to_sleep);
  return (0);
}

int eat(philosopher *p)
{
  if (specific_mutex(p, LOCK) == 1) //Makes other threads wait until the key is unlocked, only one thread at a time can have the key
    return (1);
  if (status_change(p, "\tis eating\n") == 1)
    return (1);
  g_eating_counter++;
  p->is_eating = 1;
  usleep(p->p->time_to_eat);
  p->last_meal_time = get_time();
  p->is_eating = 0;
  if (specific_mutex(p, UNLOCK) == 1) //Each time a philosopher has finished eating, he will drop his forks
    return (1);
  return (0);
}

int take_fork(philosopher *p)
{
  if (status_change(p, "\thas taken a fork\n") == 1)
    return (1);
  return (0);
}