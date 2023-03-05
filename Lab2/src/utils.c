#include "library.h"
#include "utils.h"

void Handle_error(bool expr, char* msg) {
    if (expr) {
        write(fileno(stdout), msg, strlen(msg) * sizeof(char));
        exit(-1);
    }
}

void Print_t(char* str, char* msg){
    char* full_msg = malloc((strlen(str) + strlen(msg)) * sizeof(char));
    strcat(full_msg, str); 
    strcat(full_msg, msg);
    write(fileno(stdout), full_msg, strlen(full_msg) * sizeof(char));
}

void Clean(char* str){
    for (int i = 0 ; i < strlen(str); ++i){
        if (str[i] == '\n'){ str[i] = '\0'; }
    }
}

bool StrLength(char* str) {
    for (int i = 0 ; i < strlen(str); ++i){
        if(str[i] == '.' || str[i] == ';') return true;
    }
    return false;
}