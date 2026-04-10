// direction lib
// created 26. 3. 2024

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    u,  //up
    r,  //right
    d,  //down
    l,  //left
    s   //stop
} Direction;

typedef enum {
    VERTICAL,
    HORIZONTAL
} Mirror_type;

typedef struct{
    Direction *directions;
    unsigned int length;
} Dtring;   

static const Direction DIRSEQ[] = {u, r, d, l};
static const char FILEPATH[] = "output.txt";

Direction char_to_dir(char ch) { 
    switch(ch) {
        case 'u':
            return u;
        case 'r':
            return r;
        case 'd':
            return d;   
        case 'l':
            return l;
        case 's':
            return s;
        default:
            return s; 
    }
}

char dir_to_char(Direction dir) { 
    switch(dir) {
        case u:
            return 'u';
        case r:
            return 'r';
        case d:
            return 'd';   
        case l:
            return 'l';
        case s:
            return 's';
        default:
            return 's'; 
    }
}

void fputdir(FILE *file, Direction dir) { //follows the fputc naming convention
    fputc(dir_to_char(dir), file);
}

void fprintdtr(FILE *file, Dtring dtr) {
    for (unsigned int i = 0; i < dtr.length; i++) {
        fputdir(file, dtr.directions[i]);
    }
}

int editDrt(Dtring *dtr, unsigned int num, Direction dir) {
    if (num < dtr->length) { 
        dtr->directions[num] = dir;
        return 0; //success
    } else {
        return 1; //fail
    }
}

Dtring initDtring() {
    Dtring dtr;
    dtr.directions = NULL;
    dtr.length = 0;
    return dtr;
}

void appendDtring(Dtring *dtr, Direction dir) {
    if (dtr->directions == NULL) *dtr = initDtring(); // Initialize if not initialized
    dtr->directions = realloc(dtr->directions, (dtr->length + 1) * sizeof(Direction));
    if (dtr->directions == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    dtr->directions[dtr->length] = dir;
    dtr->length++;
}

void freeDtring(Dtring dtr) {
    free(dtr.directions);
    dtr.length = -1;
}

Direction mirrorDir(Direction dir, int is_vertical) {
    if (is_vertical) {
        if (dir == l) return r;
        if (dir == r) return l;
    }else{
        if (dir == u) return d;
        if (dir == d) return u;
    }
    return dir; //if not to be mirrored
}

Dtring mirrorDtring(Dtring dtr, int is_vertical) {
    Dtring newDtr = initDtring(); 
    Direction newDir;

    for (unsigned int i = 0; i < dtr.length; i++) {
        newDir = mirrorDir(dtr.directions[i], is_vertical);
        appendDtring(&newDtr, newDir);
    }
    return newDtr;
}

Direction rotateDir(Direction dir, int clockwise) {
    if (dir == s) return s; //dont rotate if stop
    int simplerot = (clockwise % 4 + 4) % 4; //simplify the rotation
    return DIRSEQ[(dir + simplerot) % 4]; //the actual rotation
}

Dtring rotateDtring(Dtring dtr, int clockwise) {
    Dtring newDtr = initDtring(); 
    Direction newDir;

    for (unsigned int i = 0; i < dtr.length; i++) {
        newDir = rotateDir(dtr.directions[i], clockwise);
        appendDtring(&newDtr, newDir);
    }
    return newDtr;
}

void printDir(Direction dir){
    switch (dir) {
            case u:
                printf("UP ");
                break;
            case r:
                printf("RIGHT ");
                break;
            case d:
                printf("DOWN ");
                break;
            case l:
                printf("LEFT ");
                break;
            case s:
                printf("STOP ");
                break;
            default:
                printf("UNKNOWN ");
                break;
        }
}

void printDtring(Dtring dtr) {
    printf("Direction String: ");
    for (unsigned int i = 0; i < dtr.length; i++) {
        printDir(dtr.directions[i]);
    }
    printf("\n");
}

int Hilberts(unsigned int i) {
    if (i>0) Hilberts(i-1); else return 1;

    printf("Iteration %d: ", i);

    FILE *file = fopen(FILEPATH, "r+"); // Open file
    if (file == NULL) {
        exit(1);    
    }

    int ch;
    Dtring dtr = initDtring();
    while ((ch = fgetc(file)) != EOF) {
        appendDtring(&dtr, char_to_dir(ch));
    }
    fclose(file); // Closes the file

    printf("readying dtrings.");
    Dtring temp1 = rotateDtring(dtr, 1);
    printf(".");
    Dtring temp2 = mirrorDtring(temp1, HORIZONTAL);
    printf(".");
    Dtring temp3 = mirrorDtring(temp1, VERTICAL);
    freeDtring(temp1);

    file = fopen(FILEPATH, "w+");

    printf("writing dtrings");
    fprintdtr(file, temp2);
    printf(".");
    fputdir(file, d);
    fprintdtr(file, dtr);
    printf(".");
    fputdir(file, r);
    fprintdtr(file, dtr);
    printf(".");
    fputdir(file, u);
    fprintdtr(file, temp3);

    fclose(file); // Close the file
    printf("done.\n");

    freeDtring(dtr);
    freeDtring(temp2);
    freeDtring(temp3);

    return 0;
}

int main(/*int argc, char *argv[]*/) {

    unsigned int i;

    printf("Enter the number of iterations: ");
   // printf("Zadejte pocet iteraci: ");
    if (scanf("%u", &i) != 1) {
        printf("Invalid input.\n");
        exit(1);
    }

    FILE *file = fopen(FILEPATH, "w"); 
    if (file == NULL) {
        exit(1);
    } else fprintf(file, "%s", "dru");
    fclose(file); 

    Hilberts(i);

    printf("%s is ready!\nPress any key to exit.\n", FILEPATH);
    getchar();

    //printDir(mirrorDir(char_to_dir(argv[1][0]), atoi(argv[2])));
    return 0;
}


