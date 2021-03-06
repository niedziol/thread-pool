/** @file
 * Threadpool header file.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 11.02.2020
 */

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * Runnable function
 */
typedef struct runnable {
  void (*function)(void *, size_t); ///< f(arg, argsz);
  void *arg; ///<                   array of arguments;
  size_t argsz; ///<               number of arguments;
} runnable_t;

/**
 * Single queue node
 */
typedef struct node {
    runnable_t runnable; ///<      runnable function;
    struct node* next; ///< pointer to the next node;
} node_t;

/**
 * Standard FIFO queue
 */
typedef struct queue {
    node_t* first; ///< pointer to the first element;
    node_t* last;  ///<  pointer to the last element;
    size_t size;   ///<            size of the queue;
} queue_t;

/**
 * Thread-pool
 */
typedef struct thread_pool {
    size_t pool_size; ///<                  number of threads;
    sem_t mutex; ///<                       thread-pool mutex;
    sem_t waiting_threads; ///<    semaphore for free threads;
    queue_t* queue; ///<        pointer to the queue of tasks;
    pthread_t* threads; ///<                 array of threads;
    bool finished; ///< information about finishing all tasks;
    pthread_attr_t attr; ///<      standard pthread attribute;
} thread_pool_t;

/** @brief Initialize the thread-pool.
 * Create a thread_pool_t object at argument pool
 * with number of thread passed as pool_size argument.
 * @param[in,out] pool  – pointer to the thread-pool;
 * @param[in] pool_size –    size of the thread-pool;
 * @return @p 0, if init was finished correctly.
 * Non-zero value, if errors occurred.
 */
int thread_pool_init(thread_pool_t *pool, size_t pool_size);

/** @brief Destroy the thread-pool.
 * Finish all of the tasks and remove the pool.
 * @param[in,out] pool –    pointer to the thread-pool;
 */
void thread_pool_destroy(thread_pool_t *pool);

/**
 * @brief Add a new task to the pool.
 * @param[in, out] pool – pointer to thread-pool;
 * @param[in] runnable  – task that will be run on the pool.
 * @return @p 0, if defer was finished correctly.
 * Non-zero value, if errors occurred.
 */
int defer(thread_pool_t *pool, runnable_t runnable);

#endif // __THREADPOOL_H__
