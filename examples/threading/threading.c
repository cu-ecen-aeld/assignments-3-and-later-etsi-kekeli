#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg, ...)
// #define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg, ...) printf("threading ERROR: " msg "\n", ##__VA_ARGS__)

void *threadfunc(void *thread_param)
{
    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    // struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    struct thread_data *arg = (struct thread_data *)thread_param;
    usleep(arg->wait_pre_mutex);

    int rc = pthread_mutex_lock(arg->mutex);
    if (rc != 0)
    {
        fprintf(stderr, "Fail to lock the mutex\n");
    }

    usleep(arg->wait_post_mutex);
    rc = pthread_mutex_unlock(arg->mutex);
    if (rc != 0)
    {
        fprintf(stderr, "Fail to unlock the mutex\n");
    }

    arg->thread_complete_success = true;

    return thread_param;
}

bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex, int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    struct thread_data *data = (struct thread_data *)malloc(sizeof(struct thread_data));
    if (data == NULL)
    {
        perror("Memory allocation failure");
        return false;
    }

    data->mutex = mutex;
    data->thread_complete_success = false;
    data->wait_pre_mutex = wait_to_obtain_ms * 1000;
    data->wait_post_mutex = wait_to_release_ms * 1000;

    pthread_t thr[1];

    int ret = pthread_create(thr, NULL, threadfunc, (void *)data);
    *thread = *thr;
    if (ret != 0)
    {
        perror("Fail to create a new thread");
        return false;
    }

    return true;
}
