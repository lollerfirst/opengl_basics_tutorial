/** -- Busy Wait Implementation -- **/
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <unistd.h>
#include <stdint.h>

typedef volatile _Atomic uint8_t __mutex_semaphore;

/* initialize the mutex semaphore */
#define mutex_init(__mutex)\
    __atomic_store_n(__mutex, 0, __ATOMIC_RELAXED)

/* wait for the mutex to be 0 */
#define mutex_wait(__mutex) {\
    uint8_t __expected = 0;\
    while(!__atomic_compare_exchange_n(__mutex, &__expected, 1, 0, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));\
}

/* signal the mutex is now free */
#define mutex_signal(__mutex)\
    __atomic_store_n(__mutex, 0, __ATOMIC_RELEASE)


#endif