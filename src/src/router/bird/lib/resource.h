/*
 *	BIRD Resource Manager
 *
 *	(c) 1998--1999 Martin Mares <mj@ucw.cz>
 *
 *	Can be freely distributed and used under the terms of the GNU GPL.
 */

#ifndef _BIRD_RESOURCE_H_
#define _BIRD_RESOURCE_H_

#include "lib/lists.h"

/* Resource */

typedef struct resource {
  node n;				/* Inside resource pool */
  struct resclass *class;		/* Resource class */
} resource;

/* Resource class */

struct resclass {
  char *name;				/* Resource class name */
  unsigned size;			/* Standard size of single resource */
  void (*free)(resource *);		/* Freeing function */
  void (*dump)(resource *);		/* Dump to debug output */
  resource *(*lookup)(resource *, unsigned long);	/* Look up address (only for debugging) */
};

/* Generic resource manipulation */

typedef struct pool pool;

void resource_init(void);
pool *rp_new(pool *, char *);		/* Create new pool */
void rfree(void *);			/* Free single resource */
void rdump(void *);			/* Dump to debug output */
void rlookup(unsigned long);		/* Look up address (only for debugging) */
void rmove(void *, pool *);		/* Move to a different pool */

void *ralloc(pool *, struct resclass *);

extern pool root_pool;

/* Normal memory blocks */

void *mb_alloc(pool *, unsigned size);
void *mb_allocz(pool *, unsigned size);
void mb_free(void *);

/* Memory pools with linear allocation */

typedef struct linpool linpool;

linpool *lp_new(pool *, unsigned blk);
void *lp_alloc(linpool *, unsigned size);	/* Aligned */
void *lp_allocu(linpool *, unsigned size);	/* Unaligned */
void *lp_allocz(linpool *, unsigned size);	/* With clear */
void lp_flush(linpool *);			/* Free everything, but leave linpool */

/* Slabs */

typedef struct slab slab;

slab *sl_new(pool *, unsigned size);
void *sl_alloc(slab *);
void sl_free(slab *, void *);

/*
 * Low-level memory allocation functions, please don't use
 * outside resource manager and possibly sysdep code.
 */

#ifdef HAVE_LIBDMALLOC
/*
 * The standard dmalloc macros tend to produce lots of namespace
 * conflicts and we use only xmalloc and xfree, so we can define
 * the stubs ourselves.
 */
#define DMALLOC_DISABLE
#include <dmalloc.h>
#define xmalloc(size) _xmalloc_leap(__FILE__, __LINE__, size)
#define xfree(ptr) _xfree_leap(__FILE__, __LINE__, ptr)
#else
/*
 * Unfortunately, several libraries we might want to link to define
 * their own xmalloc and we don't want to interfere with them, hence
 * the renaming.
 */
#define xmalloc bird_xmalloc
void *xmalloc(unsigned);
#define xfree(x) free(x)
#endif

#endif
