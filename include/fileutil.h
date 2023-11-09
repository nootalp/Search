#ifndef FILEUTIL_H
	#define FILEUTIL_H

	#ifdef _WIN32
		#include <windows.h>
	#else
		#include <sys/stat.h>
	#endif

	#include <stdio.h>
	#include <stdlib.h>
	int is_directory(const char *path);
#endif
