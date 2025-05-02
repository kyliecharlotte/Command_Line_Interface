#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "helper_command.h"

char* find_file(char* long_str, char* delim) {

	char* copy_one = strdup(long_str);
    char* token = strtok(copy_one, delim);

    int count = 0;

    while (token != NULL) {
        count = count + 1;
        token = strtok(NULL, delim);
    }
    
    free(copy_one);

    if (count == 1) {
        return strdup(long_str);
    }

    char* copy_two = strdup(long_str);
    token = strtok(copy_two, delim);

    for (int i = 1; i < count; i++) {
        token = strtok(NULL, delim);
    }

    char* result = strdup(token);
    free(copy_two);
    return result;
    /*char* copy_one = (char*)malloc(sizeof(char)*strlen(long_str));
    strcpy(copy_one,long_str);
    char* file = strtok(copy_one, delim);
    char* return_file;

    int count = 0;

    while (file != NULL) {
        count = count + 1;
        file = strtok(NULL, delim);
    }
    
    free(copy_one);

    if (count == 1) {
        return long_str;
    }

    char* copy_two = (char*)malloc(sizeof(char)*strlen(long_str));
    strcpy(copy_two, long_str);
    return_file = strtok(copy_two, delim);

    for (int i = 1; i < count; i++) {
        return_file = strtok(NULL, delim);
    }

    strcpy(long_str,return_file);
    free(copy_two);
    return long_str;*/
}
