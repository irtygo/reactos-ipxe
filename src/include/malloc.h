#ifndef _MALLOC_H
#define _MALLOC_H

#include <stdint.h>

/** @file
 *
 * Dynamic memory allocation
 *
 */

extern void * alloc_memblock ( size_t size, size_t align );
extern void free_memblock ( void *ptr, size_t size );
extern void * realloc ( void *old_ptr, size_t new_size );
extern void * malloc ( size_t size );
extern void free ( void *ptr );
extern void mpopulate ( void *start, size_t len );
extern void mdumpfree ( void );

/**
 * Allocate memory for DMA
 *
 * @v size		Requested size
 * @v align		Physical alignment
 * @ret ptr		Memory, or NULL
 *
 * Allocates physically-aligned memory for DMA.
 *
 * @c align must be a power of two.  @c size may not be zero.
 */
static inline void * malloc_dma ( size_t size, size_t phys_align ) {
	return alloc_memblock ( size, phys_align );
}

/**
 * Free memory allocated with malloc_dma()
 *
 * @v ptr		Memory allocated by malloc_dma(), or NULL
 * @v size		Size of memory, as passed to malloc_dma()
 *
 * Memory allocated with malloc_dma() can only be freed with
 * free_dma(); it cannot be freed with the standard free().
 *
 * If @c ptr is NULL, no action is taken.
 */
static inline void free_dma ( void *ptr, size_t size ) {
	free_memblock ( ptr, size );
}

/**
 * Allocate cleared memory
 *
 * @v nmemb		Number of members
 * @v size		Size of each member
 * @ret ptr		Allocated memory
 *
 * Allocate memory as per malloc(), and zero it.
 *
 * Note that malloc() and calloc() are identical, in the interests of
 * reducing code size.  Callers should not, however, rely on malloc()
 * clearing memory, since this behaviour may change in future.
 */
static inline void * calloc ( size_t nmemb, size_t size ) {
	return malloc ( nmemb * size );
}

#endif /* _MALLOC_H */
