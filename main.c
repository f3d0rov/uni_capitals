
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isAWhitespace(char c){
    return c == ' ' || c == '\t' || c == '\n';
}

bool isCapital(char c){
    if(c >= 'A' && c <= 'Z') return true;
    return false;
}

int getNextNonWhitespace(char *str, int index){
    int i = index;
    while(isAWhitespace(str[i]) && str[i] != 0) i++;
    return i;
}

int getNextWhitespace(char *str, int index){
    int i = index;
    while(!isAWhitespace(str[i]) && str[i] != 0) i++;
    return i;
}

int countFirstCapitals(char *str){
    int count = 0, i = 0;

    while(str[i] != 0){
        i = getNextNonWhitespace(str, i);
        if(str[i] == 0) break;
        if(isCapital(str[i])) count++;
        i = getNextWhitespace(str, i);
    }

    return count;
}

int *getFirstCapitals(char *str){
    int size = countFirstCapitals(str);
    int *firstCapitals = malloc(size * sizeof(int));
    int i = 0, count = 0;
    while(str[i] != 0){
        i = getNextNonWhitespace(str, i);
        if(str[i] == 0) break;
        if(isCapital(str[i])){
            firstCapitals[count++] = i;
        }
        i = getNextWhitespace(str, i);
    }

    return firstCapitals;
}

char *readLine(){
    int size = 64;
    char *line = malloc(size * sizeof(char));
    char c = 0;
    int i = 0;

    while(true){
        
        if(i == size){
            size = 2 * size;
            line = realloc(line, size * sizeof(char));
        }

        c = getc(stdin);
        
        if(c == '\n'){
            line[i++] = 0;
            break;
        }

        line[i++] = c;
    }

    line = realloc(line, i * sizeof(char));

    return line;
}

char **readLines(){
    int size = 5;
    char *end = "end";
    char **lines = malloc(sizeof(char *) * size);
    int i = 0;

    while(true){
        char *next = readLine();

        if(!strcmp(next, &end[0])){
            free(next);
            lines[i++] = NULL;
            break;
        }

        lines[i++] = next;

        // printf("i: %d/%d, %s\n", i, size, lines[i - 1]);
        
        if(i == size){
            size = 2 * size;
            lines = realloc(lines, sizeof(char *) * size);
        }
    }
    
    lines = realloc(lines, i * sizeof(char *));

    return lines;
}

void freeLines(char **lines){
    int i = 0;
    
    while(lines[i] != NULL){
        free(lines[i++]);
    }

    free(lines);
}

char *formatStr(char *old){ 
    char *str = malloc(sizeof(char) * strlen(old) + 1);
    int i, j, start, end, newpos;
    bool notFirstWord = false;

    i = 0;
    newpos = 0;
    while(old[i] != 0){
        int start = getNextNonWhitespace(old, i);
        int end = getNextWhitespace(old, start);
        
        if(isCapital(old[start])){

            if(notFirstWord){
                str[newpos++] = ' ';
            }else{
                notFirstWord = true;
            }

            for(j = start; j < end; j++){
                str[newpos++] = old[j];
            }
        }
        
        i = end;
    }

    i = 0;
    while(old[i] != 0){
        int start = getNextNonWhitespace(old, i);
        int end = getNextWhitespace(old, start);
        
        if(!isCapital(old[start])){

            if(notFirstWord){
                str[newpos++] = ' ';
            }else{
                notFirstWord = true;
            }

            for(j = start; j < end; j++){
                str[newpos++] = old[j];
            }
        }
        
        i = end;
    }

    str[newpos] = 0;

    free(old);
    return str;
}

void format(char **lines){
    int i = 0;

    while(lines[i] != NULL){
        lines[i] = formatStr(lines[i]);
        i++;
    }
}

void printStr(char *str){
    char c = 0;
    while(c = *(str++)){
        putc(c, stdout);

        if(c == '.'){
            printf("\n\t");
        }
    }
    putc('\n', stdout);
}

void printFormat(char **lines){
    int i = 0;
    while(lines[i] != NULL){
        printStr(lines[i]);
        i++;
    }
}

int main(){
    char **lines = NULL;
    int size = 0;
    char c = 0;
    int i = 0, j, k;

    lines = readLines();

    format(lines);

    printFormat(lines);

    freeLines(lines);
    
    return 0;
}
