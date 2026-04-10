// direction lib
// created 26. 3. 2024

#include <stdio.h>
#include <stdlib.h>

static const char INPUTfilepath[] = "output.txt";  // todo: make this and cur.c filepath the same
static const char OUTPUTfilepath[] = "output.svg";
    
void printPOINT(FILE *file, int x, int y){
    fprintf(file, "%d,%d ", x*10, y*10);
}

void polylineSTART(FILE *file){
    fprintf(file, "<polyline points=\"");
}

void polylineSTOP(FILE *file){
    fprintf(file, "\" stroke=\"black\" fill=\"none\" />\n");
}

void svgSTOP(FILE *file){
    fprintf(file, "</svg>") ;
}

void svgSTART(FILE *file, int num){
    fprintf(file, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">", num*10, num*10) ;
}

int main(/*int argc, char *argv[]*/) {

    FILE *inputf = fopen(INPUTfilepath, "r"); 
    if (inputf == NULL) {
        exit(1);
        printf("something went wrong with opening the file.\n does output.txt exist? is it in the same folder as this .exe?");
    }

    FILE *outputf = fopen(OUTPUTfilepath, "w+"); 
    if (outputf == NULL) {
        exit(1);    
        // this is w+ so so this shouldnt happen
    }

    int ch;
    int x = 0;
    int y = 0;
    /*int max = 0;
    int may = 0; 
    int mix = 0;
    int miy = 0;*/
    svgSTART(outputf, 0);
    fprintf(outputf, "                                                   \n");
    polylineSTART(outputf);
    char last = 'x';
    while ((ch = fgetc(inputf)) != EOF) 
    {
        if (ch != last) {printPOINT(outputf, x, y); last = ch;}
        switch(ch) {
        case 'u':
            --y;
            break;
        case 'r':
            ++x;
            break;
        case 'd':
            ++y;
            break;   
        case 'l':
            --x;
            break;
        default:
            printf("something might be wrong.\n");
            break; 
        }
    }
    printPOINT(outputf, x, y);
    polylineSTOP(outputf);
    svgSTOP(outputf);
    fseek(outputf, 0, SEEK_SET);
    fflush(outputf) ;
    svgSTART(outputf, x);
        
    fclose(inputf);
    fclose(outputf);

    printf("output.svg is ready!\nPress any key to exit...\n");
    getchar();

    return 0;
}


