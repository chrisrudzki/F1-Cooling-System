#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/* Event structure for POSIX */
typedef struct Event_t {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int signaled;
} Event_t;

/* Create an event */
void *event_create(void)
{
    Event_t *event = (Event_t *)malloc(sizeof(Event_t));
    if (event == NULL) return NULL;

    pthread_mutex_init(&event->mutex, NULL);
    pthread_cond_init(&event->cond, NULL);
    event->signaled = 0;

    return event;
}

/* Delete an event */
void event_delete(void *eventHandle)
{
    Event_t *event = (Event_t *)eventHandle;
    pthread_mutex_destroy(&event->mutex);
    pthread_cond_destroy(&event->cond);
    free(event);
}

/* Signal an event */
void event_signal(void *eventHandle)
{
    Event_t *event = (Event_t *)eventHandle;

    pthread_mutex_lock(&event->mutex);
    event->signaled = 1;
    pthread_cond_signal(&event->cond);
    pthread_mutex_unlock(&event->mutex);
}

/* Wait for an event */
void event_wait(void *eventHandle)
{
    Event_t *event = (Event_t *)eventHandle;

    pthread_mutex_lock(&event->mutex);
    while (!event->signaled)
    {
        pthread_cond_wait(&event->cond, &event->mutex);
    }
    event->signaled = 0;
    pthread_mutex_unlock(&event->mutex);
}
