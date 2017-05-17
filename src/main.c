#include <stdio.h>
#include "strings.h"
#include "function.h"
#include <dirent.h>


int main(int argc, char const *argv[])
{
    list_dir(argv[1], 1, "a");
    return 0;
}
