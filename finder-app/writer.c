#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>

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
    openlog("Writer binary", LOG_CONS, LOG_USER);

    if (argc != 3)
    {
        syslog(LOG_ERR, "2 arguments expected but %d given\n", argc - 1);
        exit(1);
    }

    char *writefile = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));
    if (writefile == NULL)
    {
        perror("malloc");
        syslog(LOG_ERR, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(writefile, argv[1]);

    char *writestr = (char *)malloc(sizeof(char) * (strlen(argv[2]) + 1));
    if (writestr == NULL)
    {
        perror("malloc");
        syslog(LOG_ERR, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(writestr, argv[2]);

    char *dir_path = dirname(writefile);
    DIR *dir = opendir(dir_path);
    if (dir || dir == NULL)
    {
        FILE *file = fopen(writefile, "w");
        syslog(LOG_DEBUG, "Writting %s to %s\n", writestr, writefile);
        fprintf(file, "%s", writestr);
        fclose(file);
        closedir(dir);
    }
    else if (errno == ENOENT)
    {
        syslog(LOG_ERR, "The directory '%s' doesn't exist.\n", dir_path);
    }
    else
    {
        syslog(LOG_ERR, "The directory can not be opened for other reasons.\n");
    }

    closelog();
    free(dir_path);
    free(writestr);
    free(writefile);
}