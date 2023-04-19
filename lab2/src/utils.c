#include "library.h"
#include "utils.h"

void Handle_error(bool expr, char* msg) {
    if (expr) {
        write(fileno(stdout), msg, strlen(msg) * sizeof(char));
        exit(-1);
    }
}

void Clean(char* str){
    for (int i = 0 ; i < strlen(str); ++i){
        if (str[i] == '\n'){ str[i] = '\0'; }
    }
}

bool StrLength(char* str) {
    return str[strlen(str) - 1] == '.' || str[strlen(str) - 1] == ';';
}