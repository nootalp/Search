#include <stdio.h>
#include <windows.h>
#include <regex.h>

void listFilesInDirectories(const char* directoryPath, const regex_t* compiledRegex);


boolean isDirectory(const WIN32_FIND_DATA* fileData) {
    return (fileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}


void displayFileInfo(const char* directoryPath, const regex_t* compiledRegex,  const WIN32_FIND_DATA* fileData) {
	char fullPath[MAX_PATH];

    snprintf(fullPath, MAX_PATH, "%s\\%s", directoryPath, fileData->cFileName);

    TCHAR buffer[MAX_PATH];
    DWORD retval = GetFullPathName(fullPath, MAX_PATH, buffer, NULL);

    if (retval != 0) {
		if (regexec(compiledRegex, fileData->cFileName, 0, NULL, 0) == 0)
			printf("%s\n", buffer);
	}
    else printf("Error to get path.\n");
}


void listSubDirectories(const char* directoryPath, const WIN32_FIND_DATA* fileData,  const regex_t* compiledRegex) {
    char subDirPath[MAX_PATH];
    snprintf(subDirPath, MAX_PATH, "%s\\%s", directoryPath, fileData->cFileName);
    listFilesInDirectories(subDirPath, compiledRegex);
}


void listFilesInDirectories(const char* directoryPath, const regex_t* compiledRegex) {
    char searchPath[MAX_PATH];
    WIN32_FIND_DATA fileData;
	
    snprintf(searchPath, MAX_PATH, "%s\\*", directoryPath);
    HANDLE hFind = FindFirstFile(searchPath, &fileData);

    while (FindNextFile(hFind, &fileData)) {
    	if (strcmp(fileData.cFileName, ".") && strcmp(fileData.cFileName, "..")) {
    		displayFileInfo(directoryPath, compiledRegex, &fileData);
    		if (isDirectory(&fileData))
				listSubDirectories(directoryPath, &fileData, compiledRegex);
    	}
    }
    FindClose(hFind);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [DIRECTORY] [REGEX]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* directoryPath = argv[1];
    const char* regexPattern = 	argv[2];

	regex_t compiledRegex;
    if (regcomp(&compiledRegex, regexPattern, REG_EXTENDED) != 0) {
        printf("Error compiling regular expression.\n");
        return EXIT_FAILURE;
    }

    listFilesInDirectories(directoryPath, &compiledRegex);
    regfree(&compiledRegex);

    return EXIT_SUCCESS;
}
