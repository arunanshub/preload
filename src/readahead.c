/* readahead.c - read in advance a list of files, adding them to the page cache
 *
 * Copyright (C) 2005,2008  Behdad Esfahbod
 *
 * This file is part of preload.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301  USA
 */

#include "readahead.h"

#include <sys/ioctl.h>
#include <sys/wait.h>

#include "common.h"
#include "conf.h"
#include "log.h"
#ifdef HAVE_LINUX_FS_H
#include <linux/fs.h>
#endif

static void set_block(preload_map_t *file, gboolean G_GNUC_UNUSED use_inode) {
    int fd = -1;
    int block = 0;
    struct stat buf;

    /* in case we can get block, set to 0 to not retry */
    file->block = 0;

    fd = open(file->path, O_RDONLY);
    if (fd < 0) return;

    if (0 > fstat(fd, &buf)) return;

#ifdef FIBMAP
    if (!use_inode) {
        block = file->offset / buf.st_blksize;
        if (0 > ioctl(fd, FIBMAP, &block)) block = 0;
    }
#endif

    /* fall back to inode number */
    block = buf.st_ino;

    file->block = block;

    close(fd);
}

/* Compare files by path */
static int map_path_compare(const preload_map_t **pa,
                            const preload_map_t **pb) {
    const preload_map_t *a = *pa, *b = *pb;
    int i;

    i = strcmp(a->path, b->path);
    if (!i) /* same file */
        i = a->offset - b->offset;
    if (!i) /* same offset?! */
        i = b->length - a->length;

    return i;
}

/* Compare files by block */
static int map_block_compare(const preload_map_t **pa,
                             const preload_map_t **pb) {
    const preload_map_t *a = *pa, *b = *pb;
    int i;

    i = a->block - b->block;
    if (!i) /* no block? */
        i = strcmp(a->path, b->path);
    if (!i) /* same file */
        i = a->offset - b->offset;
    if (!i) /* same offset?! */
        i = b->length - a->length;

    return i;
}

static int procs = 0;

static void wait_for_children(void) {
    /* wait for child processes to terminate */
    while (procs > 0) {
        int status;
        if (wait(&status) > 0) procs--;
    }
}

static void process_file(const char *path, size_t offset, size_t length) {
    int fd = -1;
    int maxprocs = conf->system.maxprocs;

    if (procs >= maxprocs) wait_for_children();

    if (maxprocs > 0) {
        /* parallel reading */

        int status = fork();

        if (status == -1) {
            /* ignore error, return */
            return;
        }

        /* return immediately in the parent */
        if (status > 0) {
            procs++;
            return;
        }
    }

    fd = open(path, O_RDONLY | O_NOCTTY
#ifdef O_NOATIME
                        | O_NOATIME
#endif
    );
    if (fd >= 0) {
        readahead(fd, offset, length);

        close(fd);
    }

    if (maxprocs > 0) {
        /* we're in a child process, exit */
        exit(0);
    }
}

static void sort_by_block_or_inode(preload_map_t **files, int file_count) {
    int i;
    gboolean need_block = FALSE;

    /* first see if any file doesn't have block/inode info */
    for (i = 0; i < file_count; i++)
        if (files[i]->block == -1) {
            need_block = TRUE;
            break;
        }

    if (need_block) {
        /* Sorting by path, to make stat fast. */
        qsort(files, file_count, sizeof(*files),
              (GCompareFunc)map_path_compare);

        for (i = 0; i < file_count; i++)
            if (files[i]->block == -1)
                set_block(files[i], conf->system.sortstrategy == SORT_INODE);
    }

    /* Sorting by block. */
    qsort(files, file_count, sizeof(*files), (GCompareFunc)map_block_compare);
}

static void sort_files(preload_map_t **files, int file_count) {
    switch (conf->system.sortstrategy) {
        case SORT_NONE:
            break;

        case SORT_PATH:
            qsort(files, file_count, sizeof(*files),
                  (GCompareFunc)map_path_compare);
            break;

        case SORT_INODE:
        case SORT_BLOCK:
            sort_by_block_or_inode(files, file_count);
            break;

        default:
            g_warning("Invalid value for config key system.sortstrategy: %d",
                      conf->system.sortstrategy);
            /* avoid warning every time */
            conf->system.sortstrategy = SORT_BLOCK;
            break;
    }
}

int preload_readahead(preload_map_t **files, int file_count) {
    int i;
    const char *path = NULL;
    size_t offset = 0, length = 0;
    int processed = 0;

    sort_files(files, file_count);
    for (i = 0; i < file_count; i++) {
        if (path && offset <= files[i]->offset &&
            offset + length >= files[i]->offset &&
            0 == strcmp(path, files[i]->path)) {
            /* merge requests */
            length = files[i]->offset + files[i]->length - offset;
            continue;
        }

        if (path) {
            process_file(path, offset, length);
            processed++;
            path = NULL;
        }

        path = files[i]->path;
        offset = files[i]->offset;
        length = files[i]->length;
    }

    if (path) {
        process_file(path, offset, length);
        processed++;
        path = NULL;
    }

    wait_for_children();

    return processed;
}
