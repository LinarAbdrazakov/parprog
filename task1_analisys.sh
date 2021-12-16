#!/bin/bash

mpicc task1_mpi.c -o task1 -lm
for seed in $(seq 1 10);  do
	for num in $(seq 1 8); do
		mpirun -n $num task1 >> results/results_1.txt
	done
done