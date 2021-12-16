#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ISIZE 1000
#define JSIZE 1000

int main(int argc, char **argv)
{
    double a[ISIZE][JSIZE];
    int i, j;
    FILE *ff;
    for (i=0; i<ISIZE; i++){
        for (j=0; j<JSIZE; j++){
            a[i][j] = 10*i +j;
        }
    }
    
    for (i=8; i<ISIZE; i++){
        for (j = 0; j < JSIZE-3; j++){
            a[i][j] = sin(0.00001*a[i-8][j+3]);
        }
    }

    ff = fopen("result.txt","w");
    for(i=0; i < ISIZE; i++){
        for (j=0; j < JSIZE; j++){
            fprintf(ff,"%f ",a[i][j]);
        }
        fprintf(ff,"\n");
    }
    fclose(ff);
}