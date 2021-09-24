#ifndef PROC_H
#define PROC_H

/* preload_memory_t: structure holding information
 * about memory conditions of the system. */
#include "common.h"
typedef struct _preload_memory_t {
    /* runtime: */

    /* all the following are in kilobytes (1024) */

    int total;   /* total memory */
    int free;    /* free memory */
    int buffers; /* buffers memory */
    int cached;  /* page-cache memory */

    int pagein;  /* total data paged (read) in since boot */
    int pageout; /* total data paged (written) out since boot */

} preload_memory_t;

/* read system memory information */
void proc_get_memstat(preload_memory_t *mem);

/* returns sum of length of maps, in bytes, or 0 if failed */
size_t proc_get_maps(pid_t pid, GHashTable *maps, GSet **exemaps);

/* foreach process running, passes pid as key and exe path as value */
void proc_foreach(GHFunc func, gpointer user_data);

#endif
