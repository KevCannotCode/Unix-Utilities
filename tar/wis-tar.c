//
// Created by kevin on 11/16/2022.
//
//less than 2 args are nono
//if enough arg (lets say 3 ) then open the file, if it can't open then "wis-tar: cannot open file” (followed by a newline) and with exit status 1.
//if file is greater than 100 read first 100
// otherwise compress the first chars and fill the rest with zero (could be method name) util reach 100
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>

typedef unsigned char BYTE;
size_t BUFFER = 10;
#define FILE_SIZE 100

////function to convert string to byte array
//void string2ByteArray(char* input, BYTE* output)
//{
//    int loop;
//    int i;
//
//    loop = 0;
//    i = 0;
//
//    while(input[loop] != '\0')
//    {
//        output[i++] = input[loop++];
//    }
//}

int* readFile(char * filePath, FILE *stream) {
    printf("start readfile...\n");
//    struct stat info;
//    stat(filePath, &info);
//    // Do error checking here!
//
//    printf("size of %s = %ld\n", filePath, info.st_size);

    printf("listing vars ...\n");
    int * result = (int*) malloc(FILE_SIZE *sizeof(int));
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int offset = 0;

    printf("entering loop\n");

    while ((read = getline(&line, &len, stream)) != -1 && offset < FILE_SIZE) {
        printf("\nstart loop iteration\n------\n");
        printf("read = %zu , offset = %d\n", read, offset);
        for(int i = 0; i < read ; i++) {
            printf("for loop i = %d , offset = %d\n\n", i, offset);
            result[offset] = line[i];
            offset++;
            if(offset >= FILE_SIZE)
                break;
        }
        printf("\n------\nend loop iteration\n");
    }

    //fill with zeros
    while(offset < FILE_SIZE) {
        result[offset] = '\0';
        offset++;
        printf("offset = %d\n", offset);
    }

    printf("freeing line\n");
    free(line);

    printf("closing stream\n");
    fclose(stream);

    return result;
}

char* createArchive(char * writeFileName, int * buffer) {
    printf("creating a write file...\n");
    FILE *writeFile = fopen(writeFileName, "wb");
    if (!writeFile) {
        printf("wis-tar unexpected error: cannot open write file\n");
        exit(1);
    }

    printf("writing bytes to archive file ...\n");
//
//    //convert from chars to bytes
//    BYTE byteBuff[FILE_SIZE];
//    string2ByteArray(buffer, byteBuff);

    if( 0 == fwrite(buffer,1,FILE_SIZE,writeFile)) {
        printf("an error occurred when writing chars to archive file.");
    }

    printf("closing stream\n");
    fclose(writeFile);

    return writeFileName;
}

int main(int argc, char ** argv) {
    if(argc < 3) {
        printf("wis-tar: tar-file file […]\n");
        exit(1);
    }

    printf("attempting tothree args\n");
    if(argc == 3) {
        printf("yes I have 3 args...\n");
        char * filePath = argv[1];
        printf("filePath = %s\n", filePath);

        printf("opening file...\n");
        FILE *fp = fopen(filePath, "r");
        if (!fp) {
            printf("wis-tar: cannot open file\n");
            exit(1);
        }
        printf("file opened\n");

        printf("Calling readFile...\n");
        int * fileRead = readFile(filePath, fp);
        printf("%ls\n-----------------\n\n", fileRead);

        char * writeFilePath = argv[2];
        printf("archive created ! %s\n", createArchive(writeFilePath, fileRead));
    }
    return 0;
}
