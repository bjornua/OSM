#ifndef KERNEL_LOCK_COND_H
#define KERNEL_LOCK_COND_H

#include "kernel/thread.h"
#include "kernel/spinlock.h"

/* We define the lock type, it can be either locked or unlocked */
typedef struct {
    int locked;
    spinlock_t spinlock;
} lock_t;

int lock_reset(lock_t *lock);
void lock_acquire(lock_t *lock);
void lock_release(lock_t *lock);

typedef struct {
    spinlock_t spinlock;
} cond_t;

int condition_reset(cond_t *cond);
void condition_wait(cond_t *cond, lock_t *condition_lock);
void condition_signal(cond_t *cond, lock_t *condition_lock);
void condition_broadcast(cond_t *cond, lock_t *condition_lock);
#endif
