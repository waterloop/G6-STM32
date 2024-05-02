#include "logging.h"
#include <stdio.h>

void write_to_file(char *string, char* fname){
    FILE* fptr;
    fptr = fopen("../_Log/%s", fname, "a");

    fprintf(fptr, "%s\n", string);

    fclose(fptr);
    return;
}

void write_to_log(char *string){
    FILE* fptr;
    fptr = fopen("../_Log/log", "a");

    fprintf(fptr, "%s\n", string);

    fclose(fptr);
    return;
}