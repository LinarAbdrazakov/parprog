#!/bin/bash

mpicc task3_mpi.c -o task3 -lm
for seed in $(seq 1 10);  do
	for num in $(seq 1 8); do
		mpirun -n $num task3 >> results/results_3.txt
	done
done