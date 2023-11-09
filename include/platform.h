#ifndef PLATFORM_H
	#define PLATFORM_H

	#ifdef _WIN32
		#include <windows.h>
		#define PATH_SEPARATOR "\\"
	#else
		#include <dirent.h>
		#include <sys/stat.h>
		#define PATH_SEPARATOR "/"
	#endif
#endif
