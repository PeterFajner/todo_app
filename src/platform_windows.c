#include <windows.h>
#include "platform_windows.h"

void get_fpath(char *dest, const char *project_name)
{
	strcat(dest, getenv("APPDATA"));
	strcat(dest, "/.");
	strcat(dest, project_name);
	CreateDirectory(dest, NULL);
}
