#include <stdio.h>
#include "strings.h"
#include "function.h"
#include <dirent.h>


int main(int argc, char *argv[])
{
	
    if(argc == 4 && scmp(argv[1], "-r")) {
    	list_dir(argv[3], 1, argv[2]);
    } else if(argc == 3)  {
    	list_dir(argv[2], 0, argv[1]);
    }
    return 0;
}
