#include <stdio.h>

int main(){
    printf("Shell\n");
    while(1){
        char* line = NULL;
        size_t size;
        if (getline(&line, &size, stdin) == -1){
            printf("Error!\n");
        }
        else{
            printf("Input: %s", line);
        }
    }
    return 0;
}
