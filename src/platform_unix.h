#ifndef PLATFORM_UNIX_H
#define PLATFORM_UNIX_H

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Creates ~/.project_name and puts the path in dest
 */
void get_fpath(char *dest, const char *project_name);

#endif
