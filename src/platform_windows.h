#ifndef PLATFORM_WINDOWS_H
#define PLATFORM_WINDOWS_H

/**
 * Creates %APPDATA%/local/project_name and puts the path in dest
 */
void get_fpath(char *dest, const char *project_name);

#endif
