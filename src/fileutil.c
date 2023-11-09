#include "../include/fileutil.h"

int is_directory(const char *path) {
	#ifdef _WIN32
		DWORD attrib = GetFileAttributesA(path);
		return (attrib != INVALID_FILE_ATTRIBUTES) && (attrib & FILE_ATTRIBUTE_DIRECTORY);
	#else
		struct stat st;
		return !stat(path, &st) && S_ISDIR(st.st_mode);
	#endif
}

