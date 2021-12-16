#!/bin/bash

mpicc task2_mpi.c -o task2 -lm
for seed in $(seq 1 10);  do
	for num in $(seq 1 8); do
		mpirun -n $num task2 >> results/results_2.txt
	done
done