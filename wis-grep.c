//
// Created by kevin on 11/15/2022.
//printFile = https://dev-notes.eu/2019/07/Get-a-line-from-stdin-in-C/
//
#include<sys/types.h>
// #include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include <string.h>

size_t BUFFER = 10;

void printFile(FILE *stream, char * lookup)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stream)) != -1) {
        if(strstr(line, lookup)) {//a substring matching lookup was found in the file or user input
            printf("%s", line);
        }
    }

    free(line);
    fclose(stream);
}

int main(int argc, char ** argv) {
    if(argc < 2) {
        printf("wis-grep: searchterm [file …]\n");
        exit(1);
    }

    if(argc == 2) {
        printFile(stdin, argv[1]);
    }

    if(argc >= 3) {
        for(int i = 2; i < argc; i++) {
            /* Open the file for reading */
            FILE *fp = fopen(argv[i], "r");
            if (!fp) {
                printf("Error opening file '%s'\n", argv[i]);
            }

            printFile(fp, argv[1]);
        }
    }
    return 0;
}
