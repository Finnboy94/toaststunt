#ifndef EXTENSION_BACKGROUND_H
#define EXTENSION_BACKGROUND_H 1

#include <pthread.h>
#include <map>

#include "bf_register.h"
#include "functions.h"
#include "my-unistd.h"      // sleep()
#include "storage.h"        // myfree, mymalloc
#include "tasks.h"          // TEA
#include "utils.h"          // var_dup
#include "server.h"         // server options

#define THREAD_MOO_VERSION      "2.0" // Version of our MOO threading library.
#define MAX_BACKGROUND_THREADS  20    /* Maximum number of background threads that can be open
                                       * at a single time. Can be overridden with an INT in
                                       * $server_options.max_background_threads */

typedef struct background_waiter {
    vm the_vm;                          // Where we resume when we're done.
    pthread_t thread;                   // The thread data so we can pthread_cancel if the task gets killed in-MOO
    int handle;                         // Our position in the process table.
    void (*callback)(void*, Var*);      // The callback function that does the actual work.
    void* data;                         // Any data the callback function should be aware of.
    bool active;                        // @kill will set active to false and the callback should handle it accordingly.
} background_waiter;

static std::map <int, background_waiter*> background_process_table;
static int next_background_handle = 1;

// User-visible functions
extern package background_thread(void (*callback)(void*, Var*), void* data);
extern bool can_create_thread();

// Other helper functions
extern void deallocate_background_waiter(background_waiter *waiter);
void initialize_background_waiter(background_waiter *waiter);
void *run_callback(void *bw);

// Example functions
void background_test_callback(void *bw, Var *ret);

#endif /* EXTENSION_BACKGROUND_H */