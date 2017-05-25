#include <stdio.h>
#include "strings.h"


int scmp(const char *one, const char *two) 
{
    while(1) {
        if(*one == *two) {
            if(*one == '\0' && *two == '\0') {
                break;
            }
            if(*one == '\0' || *two == '\0') {
                return 0;
            }
            one++;
            two++;
        } else return 0;
    }
    return 1;
}

int slen(const char *one) 
{   
    size_t i = 0;
    while(*one != '\0') {
        i++;
        one++;
    }
    return i;
}

int sspn(const char *string, const char item)
{
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        if(string[i] == item) return 1;
    }
    return 0;
}