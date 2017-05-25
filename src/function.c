#include "function.h"
#include "strings.h"

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
                    printf(GRN);
                else if (x == shift + patternLength)
                {
                    printf(RESET);
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


void list_dir (const char * dir_name, int f, char *pattern)
{
    DIR *dir;
    dir = opendir (dir_name);

    if (dir == NULL) {
        printf("Error open dir.\n");
        exit(0);
    }
    while (1) {
        struct dirent *entry;
        char path_full[PATH_MAX];
        int path_length;
        char path[PATH_MAX];
        const char *d_name;
        entry = readdir(dir);
        
        if (entry == NULL) break;

        d_name = entry->d_name;
        if (d_name == NULL) break;
        if (sspn(d_name, '.')) {
            snprintf(path_full, PATH_MAX, "%s/%s", dir_name, d_name);
            if(scmp(path_full + slen(path_full) - 4, ".txt")) {
                if(!check(path_full)) {
                    file_read(path_full, pattern); 
                }     
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
    if (dir != NULL) closedir(dir);
}

int file_read(char *path, char *pattern) {
    int k = 0;
    printf(RED "\n");
    while(k < slen(path) + 4) {
        printf("-");
        k++;
    }
    printf("\n| %s |\n", path);
    
    k = 0;
    
    while(k < slen(path) + 4) {
        printf("-");
        k++;
    }
    printf("\n\n" RESET);

    int patternLength = slen(pattern);
    pattern[patternLength] = '\0';
    FILE *input;
    input = fopen(path, "r");
    if(input == NULL) return 0;
    int textLength = 0;
    while (!feof(input))
    {
        fgetc(input);
        textLength++;
    }
    if (patternLength > textLength)
    {
        printf("Pattern is bigger than text.\n");
        return -1;
    }
    char *text = (char*)calloc(textLength, sizeof(char));
    rewind(input);
    int i = 0;
    while (!feof(input))
    {
        fscanf(input, "%c", &text[i]);
        i++;
    }
    fclose(input);
    int lastSym = BMatcher(text, strlen(text), pattern, strlen(pattern));
    if(lastSym == 0) {   
        return 0;
    }
    while (lastSym < textLength)
    {
        printf("%c", text[lastSym]);
        lastSym++;
    }
    return 0;
}


int check(char *str) 
{
    while(*(str + 1)) {
        if(*str == '/' && *(str + 1) == '.') return 1;
        str++;
    }
    return 0;
}