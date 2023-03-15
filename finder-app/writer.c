#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

char *dirname(char *path)
{
    int length = strlen(path);
    for (int i = length - 1; i >= 0; i--)
    {
        if (path[i] == '/')
        {
            char *dir_path = (char *)malloc(sizeof(char) * (i + 2));
            strncpy(dir_path, path, i + 1);
            dir_path[i + 1] = '\0';
            return dir_path;
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "2 arguments expected but %d given\n", argc - 1);
        exit(1);
    }

    char *writefile = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));
    if (writefile == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(writefile, argv[1]);

    char *writestr = (char *)malloc(sizeof(char) * (strlen(argv[2]) + 1));
    if (writestr == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(writestr, argv[2]);

    char *dir_path = dirname(writefile);
    DIR *dir = opendir(dir_path);
    if (dir || dir == NULL)
    {
        FILE *file = fopen(writefile, "w");
        fprintf(file, "%s", writestr);
        fclose(file);
    }
    else if (errno == ENOENT)
    {
        fprintf(stderr, "The directory '%s' doesn't exist.\n", dir_path);
    }
    else
    {
        fprintf(stderr, "The directory can not be opened for other reasons.\n");
    }

    free(dir_path);
    free(writestr);
    free(writefile);
}