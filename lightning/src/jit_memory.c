/*
 * Copyright (C) 2013  Free Software Foundation, Inc.
 *
 * This file is part of GNU lightning.
 *
 * GNU lightning is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU lightning is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * Authors:
 *	Paulo Cesar Pereira de Andrade
 */

#include <lightning.h>
#include <lightning/jit_private.h>
#include <mman.h>

/*
 * Prototypes
 */
static void *jit_default_alloc_func(size_t);
static void *jit_default_realloc_func(void*, size_t);
static void jit_default_free_func(void *);

/*
 * Initialization
 */
static jit_alloc_func_ptr jit_alloc_ptr = jit_default_alloc_func;
static jit_realloc_func_ptr jit_realloc_ptr = jit_default_realloc_func;
static jit_free_func_ptr jit_free_ptr = jit_default_free_func;

/*
 * Implementation
 */
void
jit_set_memory_functions(jit_alloc_func_ptr alloc_ptr,
			 jit_realloc_func_ptr realloc_ptr,
			 jit_free_func_ptr free_ptr)
{
    if (alloc_ptr == NULL)
	alloc_ptr = jit_default_alloc_func;
    if (realloc_ptr == NULL)
	realloc_ptr = jit_default_realloc_func;
    if (free_ptr == NULL)
	free_ptr = jit_default_free_func;
    jit_alloc_ptr = alloc_ptr;
    jit_realloc_ptr = realloc_ptr;
    jit_free_ptr = free_ptr;
}

void
jit_get_memory_functions(jit_alloc_func_ptr *alloc_ptr,
			 jit_realloc_func_ptr *realloc_ptr,
			 jit_free_func_ptr *free_ptr)
{
    *alloc_ptr = jit_alloc_ptr;
    *realloc_ptr = jit_realloc_ptr;
    *free_ptr = jit_free_ptr;
}

void
jit_alloc(jit_pointer_t *ptr, jit_word_t size)
{
    *ptr = (*jit_alloc_ptr)(size);
    memset(*ptr, 0, size);
}

void
jit_realloc(jit_pointer_t *ptr, jit_word_t old_size, jit_word_t new_size)
{
    *ptr = (*jit_realloc_ptr)(*ptr, new_size);
    if (old_size < new_size)
	memset((jit_int8_t*)*ptr + old_size, 0, new_size - old_size);
}

void
jit_free(jit_pointer_t *ptr)
{
    (*jit_free_ptr)(*ptr);
    *ptr = NULL;
}

#if HAVE_MREMAP
jit_bool_t
_jit_remap(jit_state_t *_jit)
{
    jit_uint8_t		*code;
    jit_word_t		 length;

    length = _jitc->pool.length * 1024 * (_jitc->mult + 1);

    code = mremap(_jit->code.ptr, _jit->code.length, length, 0, NULL);
    if (code != MAP_FAILED) {
	assert(code == _jit->code.ptr);
	++_jitc->mult;
	_jit->code.length = length;
	_jitc->code.end = _jit->code.ptr + _jit->code.length - 64;

	return (1);
    }

    return (0);
}
#endif

static void *
jit_default_alloc_func(size_t size)
{
    return (malloc(size));
}

static void *
jit_default_realloc_func(void *ptr, size_t size)
{
    return (realloc(ptr, size));
}

static void
jit_default_free_func(void *ptr)
{
    free(ptr);
}
