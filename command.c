
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "command.h"
#include "helper_command.h"

void listDir() {

    char* cwd = getcwd(NULL,0);

    DIR* directory;
    directory = opendir(cwd);
    struct dirent *dirp;
    dirp = readdir(directory);

    while (dirp != NULL) {
        write(STDOUT_FILENO,dirp->d_name,strlen(dirp->d_name));
        write(STDOUT_FILENO," ",strlen(" "));
        dirp = readdir(directory);
    }

    closedir(directory);
    free(cwd);

    return;
}

void showCurrentDir() {
    char* cwd = NULL;
    cwd = getcwd(cwd,0);
    write(STDOUT_FILENO,cwd,strlen(cwd));
    free(cwd);
    write(STDOUT_FILENO, "\n\0", strlen("\n\0"));
    return;
}

void makeDir(char *dirName) {
    if (mkdir(dirName, 0777) == -1) {
        if (errno == EEXIST) {
            write(STDOUT_FILENO, "Directory already exists!\n\0", strlen("Directory already exists!\n\0"));
            return;
        } else {
            write(STDOUT_FILENO, "Error creating directory!\n\0", strlen("Error creating directory!\n\0"));
            return;
        }
    }
    return;
}

void changeDir(char *dirName) {
    int c = chdir(dirName);
    if (c == -1) {
        write(STDOUT_FILENO, "Could not change to this directory!\n\0", strlen("Could not change to this directory!\n\0"));
        return;
    }
    return;
}

void copyFile(char *sourcePath, char *destinationPath) {

    char buf[1024];
    int line;

    int copied_file = open(sourcePath, O_RDONLY);

    if (copied_file  == -1) {
        write(STDOUT_FILENO, "Error copying file\n\0", strlen("Error copying file\n\0"));
        return;
    }

    struct stat s;

    char* dest = NULL;
    char* src_file = find_file(sourcePath, "/");

    if (stat(destinationPath, &s) == 0) {

        if (S_ISDIR(s.st_mode)) {
            dest = malloc(strlen(destinationPath)+strlen(src_file)+2);
            strcpy(dest, destinationPath);
            strcat(dest, "/");
            strcat(dest, src_file);
        } else {
            dest = strdup(destinationPath);
        }

    } else {

        dest = strdup(destinationPath);

    }

    int copy_file = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (copy_file == -1) {
        write(STDOUT_FILENO, "Error creating file\n\0", strlen("Error creating file\n\0"));
        close(copied_file);
        free(src_file);
        free(dest);
        return;
    }

    while ((line = read(copied_file, buf, sizeof(buf))) > 0) {
        write(copy_file, buf, line);
    }

    close(copied_file);
    close(copy_file);
    free(src_file);
    free(dest);

    return;

}

void moveFile(char *sourcePath, char *destinationPath) {

    struct stat s;

    char* source = (char*)malloc(strlen(sourcePath)+1);
    strcpy(source, sourcePath);

    char* src_file = find_file(sourcePath, "/");
    char* dest = NULL;

    if (stat(destinationPath, &s) == 0) {

        if (strchr(destinationPath, '/') != NULL) {
            size_t len = (strlen(destinationPath)+1+strlen(src_file) + 1);
            dest = (char*)malloc(len);  
            snprintf(dest,len,"%s/%s", destinationPath, src_file);
        }
        else if ((s.st_mode & S_IFDIR) == S_IFDIR) {
            size_t len = (strlen(destinationPath)+1+strlen(src_file) + 1);
            dest = (char*)malloc(len);  
            snprintf(dest,len,"%s/%s", destinationPath, src_file);
        }

    } else {

        dest = strdup(destinationPath);

    }

    int c = rename(source, dest);

    if (c == -1) {
        write(STDOUT_FILENO, "Could not move this file\n\0", strlen("Could not move this file\n\0"));
        free(source);
        free(dest);
        free(src_file);
        return;
    }

    free(source);
    free(src_file);
    free(dest);

    return;
}

void deleteFile(char *filename) {
    int c = remove(filename);
    if (c == -1) {
        write(STDOUT_FILENO, "Could not delete the mafile\n\0", strlen("Could not delete the file\n\0"));
        return;
    }

    return;
}

void displayFile(char *filename) {

    char buf[1024];
    int line;

    int cat_file = open(filename, O_RDONLY | O_CREAT);

    while ((line = read(cat_file, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, line);
    }
    close(cat_file);


    return;
}
