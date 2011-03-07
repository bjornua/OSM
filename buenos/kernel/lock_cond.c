#include "kernel/lock_cond.h"
#include "kernel/interrupt.h"
#include "kernel/sleepq.h"
#include "kernel/spinlock.h"

/* We use a single spinlock to lock all locks */

int lock_reset(lock_t *lock){

    interrupt_status_t intr_status;
    intr_status = _interrupt_disable();
    spinlock_release(&(lock->spinlock));

    lock->locked = 0;

    _interrupt_set_state(intr_status);
    spinlock_acquire(&(lock->spinlock));

    return 0;
}

void lock_acquire(lock_t *lock){

    interrupt_status_t intr_status;
    intr_status = _interrupt_disable();
    spinlock_acquire(&(lock->spinlock));

    /* If the lock is locked we set the thread to sleep, and check agin when
     * the thread is awoken */
    while(lock->locked){
        sleepq_add(lock);
        spinlock_release(&(lock->spinlock));

        /* let the thread sleep */
        thread_switch();
        spinlock_acquire(&(lock->spinlock));
    }

    lock->locked = 1;

    spinlock_release(&(lock->spinlock));
    _interrupt_set_state(intr_status);
}

void lock_release(lock_t *lock){

    interrupt_status_t intr_status;
    intr_status = _interrupt_disable();
    spinlock_acquire(&(lock->spinlock));

    /* We unlock the lock and wake the next thread in the queue */
    lock->locked = 0;
    sleepq_wake(lock);

    spinlock_release(&(lock->spinlock));
    _interrupt_set_state(intr_status);
}

int condition_reset(cond_t *cond){

}

/* We add the thread to the sleepqueue, and sleep, when we wake again, we
 * acquire the lock */
void condition_wait(cond_t *cond, lock_t *condition_lock){

    interrupt_status_t intr_status;
    intr_status = _interrupt_disable();
    spinlock_acquire(&(cond->spinlock));

    sleepq_add(cond);

    spinlock_release(&(cond->spinlock));

    thread_switch();

    lock_acquire(condition_lock);

    _interrupt_set_state(intr_status);
}

/* For the signal function, we simply wake the the next thread waiting */
void condition_signal(cond_t *cond, lock_t *condition_lock){

    interrupt_status_t intr_status;
    intr_status = _interrupt_disable();
    spinlock_acquire(&(cond->spinlock));

    sleepq_wake(cond);

    spinlock_release(&(cond->spinlock));
}

void condition_broadcast(cond_t *cond, lock_t *condition_lock){

    interrupt_status_t intr_status;
    intr_status = _interrupt_disable();
    spinlock_acquire(&(cond->spinlock));

    sleepq_wake_all(cond);

    spinlock_release(&(cond->spinlock));
}
