#ifndef VECTOR_H
#define VECTOR_H

#include "semaphore.h"
#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>
#include "narg.h"


/* Vector max size */
#define __VECTOR_MAX_SIZE 1073741824

/* Pop an element from the back of the vector into __dest. (vector_popn for a more efficient call)*/
#define vector_popb(__vec, __dest) vector_popn(__vec, __dest, 1)
/* Push an element to the back of the vector from __src. (vector_pushn for a more efficient call)*/
#define vector_pushb(__vec, __src) vector_pushn(__vec, __src, 1)
/* Read an element at the specified vector __index. (vector_readn for a more efficient call)*/
#define vector_read(__vec, __dest, __index) vector_readn(__vec, __dest, __index, 1)
/* Store and element at the specified vector __index. (vector_storen for a more efficient call)*/
#define vector_store(__vec, __src, __index) vector_storen(__vec, __src, __index, 1)
/* Initialize the vector with a pre-existing array __arr*/
#define vector_init_arr(__vec, __arr, __element_count, __type_size) ({   \
    int8_t __i = vector_init(__vec, __element_count, __type_size);       \
    __i = vector_pushn(__vec, __arr, __element_count);                   \
    (__i);                                                               \
})
/* Returns the current size of the vector (pass a vector, not a pointer). */
#define vector_size(__vec) __vec.__vector_size

/* Initialize a vector with an list of arguments passed in by pointer and terminated by a NULL pointer */
#define vector_init_list(__vec, __type_size, ...) ({                                             \
    int8_t __i = vector_init(__vec, PP_NARG(__VA_ARGS__), __type_size);                          \
    __i = __init_list(__vec, PP_NARG(__VA_ARGS__), __VA_ARGS__);                                 \
    (__i);                                                                                       \
})

/* Vector type definition */
typedef struct __vector{ uint8_t __vector_init;
                         uint8_t* __vector_ptr; 
                         uint32_t __vector_pages;
                         float __vector_swap_indices[2];
                         uint64_t __vector_size; 
                         uint64_t __vector_element_size; 
                         uint64_t __vector_index; 
                         __mutex_semaphore __vector_sem; 
                         uint16_t __vector_head_popped;
                         } Vector;

/* Read __element_count elements starting from __index (ATTENTION: this can still segfault)*/
extern void vector_readn(Vector*__restrict __vec, void*__restrict __dest, const uint64_t __index, const size_t __element_count);
/* Store __element_count elements starting from __index (ATTENTION: this can still segfault)*/
extern void vector_storen(Vector* __restrict __vec, void* __restrict __src, const uint64_t __index, const size_t __element_count);
/* Initialize the vector with specified __size and of the type __type_size */
extern int vector_init(Vector* __vec, const size_t __size, const size_t __type_size);
/* Push __element_count elements to the back of the vector from __src */
extern int vector_pushn(Vector*__restrict __vec, const void* __restrict __src, const size_t __element_count);
/* Push an element to the front of the vector from __src */
extern int vector_pushf(Vector*__restrict __vec, const void*__restrict __src);
/* Pop __element_count elements from the back of the vector into __dest */
extern int vector_popn(Vector*__restrict __vec, void*__restrict __dest, const size_t __element_count);
/* Pop an element from the front of the vector into __dest */
extern int vector_popf(Vector*__restrict __vec, void*__restrict __dest);
/* Returns the address of an element at the specified zero addressed index */
extern void* vector_at(Vector* __vec, const uint64_t __index);
/* Releases all the memory under the specified vector and deinitializes it */
extern void vector_free(Vector* __vec);



/* init_list */
extern int __init_list(Vector* __vec, const uint32_t __narg, ...); 

#endif