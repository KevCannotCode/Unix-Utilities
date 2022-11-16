//
// Created by kevin on 11/16/2022.
//
//less than 2 args are nono
//if enough arg (lets say 3 ) then open the file, if it can't open then "wis-tar: cannot open file” (followed by a newline) and with exit status 1.
//if file is greater than 100 read first 100
// otherwise compress the first chars and fill the rest with zero (could be method name) util reach 100
#include<sys/types.h>
// #include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include <string.h>

size_t BUFFER = 10;

int main(int argc, char ** argv) {
    if(argc < 2) {
        printf("wis-tar: tar-file file […]\n");
        exit(1);
    }

    if(argc == 2) {
//        * Open the file for reading */
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            printf("wis-tar: cannot open file\n");
            exit(1);
        }
q
    }
    return 0;
}
