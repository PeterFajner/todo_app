#include "platform_unix.h"

void get_fpath(char *dest, const char *project_name)
{
	strcat(dest, getenv("HOME"));
	strcat(dest, "/.");
	strcat(dest, project_name);
	mkdir(dest, S_IRWXU | S_IRWXG); // permissions: 770
}
