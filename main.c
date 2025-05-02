
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"
#include "command.h"
#include "helper_command.h"

// freopen sets stream to standard output or file

char* acceptable_commands[] = {"ls", "pwd", "mkdir", "cd", "cp", "mv", "rm", "cat", "exit"};

int find_index(char* val) {

    if (val == NULL) {
        return -1;
    }
    int index = 0;
    while (index < 9 && strcmp(val, acceptable_commands[index]) != 0) {
        index++;
    }
    if (index == 9) {
        index = -1;
    }
    return index;
}

void print_file() {

    char* line = NULL;
    size_t len;

    FILE* fp = fopen("output.txt", "r");
    line = NULL;
    len = 0;

    while (getline(&line, &len, fp) != -1) {
        printf("%s", line);
    }

    fclose(fp);
    free(line);
}

void file_mode(char* file_name, char* output_path) {

    char* input;
    char* keyword = "exit";
    char* buffer;
    int val;
    FILE* inFPtr;
    inFPtr = fopen(file_name, "r");
 	if (inFPtr == NULL) {
		printf("File doesn't exist");
		return;
	}
 
    size_t buffer_size = 128;
    size_t commands;

    command_line control_command;
    command_line command;

    buffer = (char*)malloc(buffer_size);

    FILE* clear_file = fopen("output.txt", "w");
    fclose(clear_file);

    FILE* f_open = freopen("output.txt", "a", stdout);

    while (getline(&buffer, &buffer_size, inFPtr) != -1) {

        control_command = str_filler(buffer, ";");

            for (int i = 0; control_command.command_list[i] != NULL; i++) {

                command = str_filler(control_command.command_list[i], " ");

                int number_entries = command.num_token;
                input = command.command_list[0];
                val = find_index(input);


                if (number_entries == 0) {
                    free_command_line(&command);
                    continue;
                }
                
                if (strcmp(input, keyword) == 0) {
                    free_command_line(&control_command);
                    free_command_line(&command);
                    free(buffer);
                    return;
                };

                switch (val) {

                    case (0):
                    // LS - 0 args
                        if (number_entries != 1) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        listDir();
                        printf("\n");
                        break;

                    case (1):
                    // PWD - 0 args
                        if (number_entries != 1) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        showCurrentDir();
                        break;
                    
                    case(2):
                        if (number_entries != 2) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        makeDir(command.command_list[1]);
                        break;

                    case(3):
                        if (number_entries != 2) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        changeDir(command.command_list[1]);
                        break;
                    case(4):
                        if (number_entries != 3) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        copyFile(command.command_list[1], command.command_list[2]);
                        break;
                        
                    case (5):
                        if (number_entries != 3) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        moveFile(command.command_list[1], command.command_list[2]);
                        break;

                    case (6):
                        if (number_entries != 2) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        deleteFile(command.command_list[1]);
                        break;

                    case (7):
                        if (number_entries != 2) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        displayFile(command.command_list[1]);
                        break;

                    case (-1):
                        printf("Error! Unrecognized command: %s\n", input);
                        break;
                    
		        }
                fflush(stdout);
			free_command_line(&command);
                
            }
	    free_command_line(&control_command); 

    }

    free(buffer);
    fclose(f_open);
    fclose(inFPtr);

    return;

}

void interactive_mode() {

    char* input;
    char* keyword = "exit";
    char* buffer;
    int val;
    size_t buffer_size = 128;
    size_t commands;

    command_line control_command;
    command_line command;

    buffer = (char*)malloc(sizeof(char)*buffer_size);

    while (1) {

        printf(">>>");
        commands = getline(&buffer, &buffer_size, stdin);

        control_command = str_filler(buffer, ";");
        int nums = control_command.num_token;

            for (int i = 0; i < nums; i++) {
                
                command = str_filler(control_command.command_list[i], " ");
                int number_entries = command.num_token;
                input = command.command_list[0];
                val = find_index(input);
                

                if (number_entries == 0) {
                    free_command_line(&command);
                    continue;
                }

                if (strcmp(input, keyword) == 0) {
                    free_command_line(&control_command);
                    free_command_line(&command);
                    free(buffer);
                    return;
                };

                switch (val) {
                    case (0):
                    // LS - 0 args
                        if (number_entries != 1) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        listDir();
                        printf("\n");
                        break;

                    case (1):
                    // PWD - 0 args
                        if (number_entries != 1) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        showCurrentDir();
                        break;
                    
                    case(2):
                        if (number_entries != 2) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        makeDir(command.command_list[1]);
                        break;

                    case(3):
                        if (number_entries != 2) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        changeDir(command.command_list[1]);
                        break;
                    case(4):
                        if (number_entries != 3) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        copyFile(command.command_list[1], command.command_list[2]);
                        break;
                        
                    case (5):
                        if (number_entries != 3) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        moveFile(command.command_list[1], command.command_list[2]);
                        break;

                    case (6):
                        if (number_entries != 2) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        deleteFile(command.command_list[1]);
                        break;

                    case (7):
                        if (number_entries != 2) {
                            printf("Error! Unsupported parameters for command: %s\n", acceptable_commands[val]);
                            break;
                        }
                        displayFile(command.command_list[1]);
                        printf("\n");
                        break;

                    case (-1):
                        printf("Error! Unrecognized command: %s\n", input);
                        break;
                    
                    default:
                        printf("\n");
                        break;
		        }
			free_command_line(&command);
                
            }
	    free_command_line(&control_command); 

    }
    free(buffer);
    return;
}

int main(int argc, char* argv[])
{
    int length = argc;
    int interactive = 0;

    char* cwd = getcwd(NULL,0);
    char* output_path = (char*)malloc(strlen(cwd)+strlen("/output.txt")+1);
    sprintf(output_path, "%s/output.txt",cwd);

    for (int i = 0; i < length; i++) {
        if (strcmp(argv[i],"-f") == 0) {
            file_mode(argv[2], output_path);
            interactive = 1;
	}
    }
    if (interactive == 0) {
        interactive_mode();
    }
    free(output_path);
    free(cwd);
}
