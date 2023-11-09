#include "../include/includes.h"

void search_files(const char *dir, const char *pattern) {
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
		fprintf(stderr, "Error to compile Regular Expression: %s\n", pattern);
		return;
    }

	#ifdef _WIN32
		WIN32_FIND_DATAA data;
		char tempPath[MAX_PATH];
		snprintf(tempPath, sizeof(tempPath), "%s%s%s", dir, PATH_SEPARATOR, "*");

		HANDLE handle = FindFirstFileA(tempPath, &data);
		if (handle != INVALID_HANDLE_VALUE) {
			do {
				if (strcmp(data.cFileName, ".") && strcmp(data.cFileName, "..")) {
					char entry[MAX_PATH];
					snprintf(entry, sizeof(entry), "%s%s%s", dir, PATH_SEPARATOR, data.cFileName);

					if (is_directory(entry)) {
						search_files(entry, pattern);
					} else if (!regexec(&regex, data.cFileName, 0, NULL, 0)) {
						printf("%s\n", entry);
					}
				}
			} while (FindNextFileA(handle, &data));
			FindClose(handle);
		}
	#else
	    DIR *dp = opendir(dir);
	    if (!dp) return;
	    struct dirent *entry;

	    while ((entry = readdir(dp))) {
	        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
	            char path[MAX_PATH];
	            snprintf(path, sizeof(path), "%s%s%s", dir, PATH_SEPARATOR, entry->d_name);

	            if (is_directory(path)) {
	                search_files(path, pattern);
	            } else if (!regexec(&regex, entry->d_name, 0, NULL, 0)) {
	                printf("%s%s%s\n", dir, PATH_SEPARATOR, entry->d_name);
	            }
	        }
	    }
	    closedir(dp);
	#endif
		regfree(&regex);
}

int main(int argc, char *argv[]) {

	if (argc < 3) {
        fprintf(stderr, "Usage: %s [DIRECTORY] [REGEX]\n", argv[0]);
        return 1;
    }
    search_files(argv[1], argv[2]);
    return 0;
}
