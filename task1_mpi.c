#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define ISIZE 1000
#define JSIZE 1000

int main(int argc, char **argv)
{
    int size = 0;
	int rank = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    long long unsigned int job_size = ISIZE*JSIZE;
	int per_proc = job_size / size;
	if (job_size % size) per_proc++;
    int i, j;
    double start, end;
	
    double **a;
    double *array;
	double *sub_array = calloc(sizeof(double), per_proc);

    if(rank==0) {
        // initialize
        a = calloc(sizeof(double *), ISIZE);
		for (i = 0; i < ISIZE; i++) a[i] = calloc(sizeof(double), JSIZE);
		
        // fill 
        for (i=0; i<ISIZE; i++){
            for (j=0; j<JSIZE; j++){
                a[i][j] = 10*i +j;
            }
        }

        // flatten
        array = calloc(sizeof(double), job_size);
		for (i=0; i<ISIZE; i++)
        {
            for (j=0; j<JSIZE; j++)
            {
				array[i*JSIZE+j] = a[i][j];
            }
        }

        start = MPI_Wtime();
    }

	MPI_Scatter(array, per_proc, MPI_DOUBLE, sub_array, per_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for (i=0; i<per_proc; i++)
    {
        sub_array[i] = sin(0.00001*sub_array[i]);
    }
	MPI_Gather(sub_array, per_proc, MPI_DOUBLE, array, per_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank==0) {
        end = MPI_Wtime();
		printf("%d\t%lf\n", size, end-start);

        // FILE *ff = fopen("result.txt","w");
        // for(i=0; i < ISIZE; i++){
        //     for (j=0; j < JSIZE; j++){
        //         fprintf(ff,"%f ",a[i][j]);
        //     }
        //     fprintf(ff,"\n");
        // }
        // fclose(ff);

        for (i = 0; i < ISIZE; i++) free(a[i]);
		free(a);
		free(array);
    }

    free(sub_array);
	MPI_Finalize();
}