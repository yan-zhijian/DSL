#ifndef __DSL_H
#define __DSL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#define dsl_malloc  malloc
#define dsl_free    free
#define dsl_memcpy  memcpy

#ifdef __cplusplus
}
#endif

#endif
