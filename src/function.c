#include "function.h"

void computeLastOccurrence(int *J, char *pattern, int patternLength)
{
    for (int i = 0; i < ALPHABET_LEN; i++)
        J[i] = patternLength;

    for (int i = 0; i < patternLength-1; i++)
        J[(int)pattern[i]] = patternLength-1 - i;
}

int BMatcher(char *text, int textLength, char *pattern, int patternLength)
{
    int x, i, shift;
    int J[ALPHABET_LEN];
    computeLastOccurrence(J, pattern, patternLength);
    i = patternLength-1;
    while (i < textLength)
    {
        int j = patternLength-1;
        if(pattern[j] == '*') {

        }
        while (j >= 0 && ((text[i] == pattern[j])))
        {
            --i;
            --j;
        }
        if (j < 0)
        {
            shift = i+1;
            for (x = 0; x < textLength; x++)
            {
                if (x == shift)
                    printf("\x1b[31;1m");
                else if (x == shift + patternLength)
                {
                    printf("\x1b[0m");
                    break;
                }
                printf("%c", text[x]);
            }
            x += BMatcher(text + shift + patternLength, strlen(text + shift + patternLength), pattern, patternLength);
            return x;
        }
        i += J[(int)text[i]];
    }
    return 0;
}


void list_dir (const char * dir_name, const int f, char *pattern)
{
    DIR *dir;
    dir = opendir (dir_name);

    if (!dir) {
        printf("Error open dir.");
    }
    while (1) {
        struct dirent *entry;
        char path_full[PATH_MAX];
        int path_length;
        char path[PATH_MAX];
        const char *d_name;
        entry = readdir(dir);
        
        if (!entry) break;

        d_name = entry->d_name;
        if (strncmp(d_name, ".", strlen("."))) {
            snprintf(path_full, PATH_MAX, "%s/%s", dir_name, d_name);
            if(!strcmp(path_full + strlen(path_full) - 4, ".txt")) {
                file_read(path_full, pattern);
                printf("%s\n", path_full);       
            }
        }
        
        if (entry->d_type & DT_DIR) {
            
            if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
                path_length = snprintf(path, PATH_MAX, "%s/%s", dir_name, d_name);
                if (path_length >= PATH_MAX) exit(1);
                if(f) {
                    list_dir (path, f, pattern);
                }
            }
        }
    }
    closedir(dir);
}

int file_read(const char * path, char *pattern) {
    char text[10240];
    char temp;
    int i = 0;
    text[10239] = '\0';
    FILE *input = fopen(path, "rt");
    while(fscanf(input, "%c", &temp) != EOF && i < 10239) {
        *(text + i) = temp;
        i++;
    }
    fclose(input);
    //BMatcher(text, strlen(text), pattern, strlen(pattern));
    return 0;
}