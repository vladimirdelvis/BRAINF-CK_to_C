#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
BRAINFUCK COMMANDS -> C
< -> --pointer;
> -> ++pointer;
+ -> ++(*pointer);
- -> --(*pointer);
. -> putchar(*pointer);
, -> *pointer = getchar();
[ -> while(*pointer) {
] -> }
*/
static char* getchars(){
    FILE* fl = fopen("program.bf","r");
    char *ptr = malloc(8);
    char val = 0;
    int index = 0;
    for(;;){
        val = getc(fl);
        if(val == EOF){
            ptr[index] = '\0';
            break;       
        }
        else if(val != '\n'){
            ptr[index] = val;
            index++;
            ptr = realloc(ptr,8 + index);
        }
    }
    fclose(fl);
    return ptr;
}

int main(int argc, char** argv){

    int max_mem = 0;
    puts("MAX MEMORY : ");
    scanf("%u",&max_mem);
    getchar();
    FILE *fl = fopen("program.c","w");
    char* ptr = getchars();
    int index = 0;
    char test_val = 0;
    fprintf(fl,"%s%d%s","int main(){\nunsigned char *pointer = calloc(",max_mem,",1);\nunsigned char* ptr2 = pointer;\n");
    fflush(fl);
    for(;;){
        if(ptr[index] == '\0'){
            break;
        }
        else{
            test_val = ptr[index];
            switch (test_val)
            {
            case '<':
                fputs("--pointer;\n",fl);
                break;
            case '>':
                fputs("++pointer;\n",fl);
                break;
            case '+':
                fputs("++(*pointer);\n",fl);
                break;
            case '-':
                fputs("--(*pointer);\n",fl);
                break;
            case '.':
                fputs("putchar(*pointer);\n",fl);
                break;
            case ',':
                fputs("*pointer = getchar();\n",fl);
                break;
            case '[':
                fputs("while(*pointer) {\n",fl);
                break;
            case ']':
                fputs("}\n",fl);
                break;
            default:
                break;
            }
            fflush(fl);
            index++;
        }
    }
    fputs("free(ptr2);\n}\n",fl);
    fflush(fl);
    fclose(fl);
    free(ptr);

    return 0;
}