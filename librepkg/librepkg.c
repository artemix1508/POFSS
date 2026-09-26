#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Librepkg distributed under the BSD 3-Clause license.
 *
 * Direct successor to https://raw.githubusercontent.com/ilikeminecraft22/insane-software/main/librepkg.c
 *
 * Made by https://github.com/ilikeminecraft22
 *
 */

int main(int argc, char **argv)
{
    if (argc == 2) { // Make help work with no 3rd argument
        if (strcmp(argv[1], "-h") == 0) { // Show help
            printf("POFSS Librepkg\n");
            printf(" -r - direct data fetch\n");
            printf(" -g - clone a git repository from https://github.com/\n");
            printf(" -h show Librepkg help\n");
            return 0;
        }
        return 1;
    }

    if (argc < 3) // Exit when there's not enough arguments
        return 1;

    if (strcmp(argv[1], "-g") == 0) // Github clone
    {
        char url[1024];

        snprintf(url, sizeof(url),
                 "https://github.com/%s", argv[2]);

        char *args[] = {
            "git",
            "clone",
            url,
            NULL
        };

        execvp("git", args);

        // Only reached if execvp() fails
        perror("execvp");
        return 1;
    }

    if (strcmp(argv[1], "-r") == 0) // Raw curl download
    {
        char url[1024];

	snprintf(url, sizeof(url), "%s", argv[2]);

	char *args[] = {
		"curl",
		url,
		NULL
	};

	execvp("curl", args);

	// Only reached if execvp() fails
	perror("execvp");
	return 1;

    }

    return 0;
}
