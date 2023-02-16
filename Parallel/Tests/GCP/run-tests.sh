# This script executes the KNN distributed program on a cluster, with an already created sample dataset 
# (at least 25K samples, 50 features and 4 classes)

#!/bin/bash
PS3='Choose your on which cluster configuration you want to perform a test 
of the KNN distributed algorithm (select the integer option): '
cluster=("LIGHT" "FAT" "QUIT")
select fav in "${cluster[@]}"; do
    case $fav in
        "LIGHT")
            echo "\033[;32mStart running tests on LIGHT cluster\033[0m"
            # Using 1 CPUs and varying the datasets samples considered
            mpirun -n 1 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun -n 1 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun -n 1 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 2 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 2 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 2 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 2 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 4 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 4 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 4 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 4 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 8 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 8 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 8 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 8 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 10 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 10 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 10 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 10 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 12 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 12 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 12 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 12 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4
            echo "\033[;32mEnded tests on LIGHT cluster\033[0m"
            ;;
        "FAT")
            echo "\033[;34mStart running tests on FAT cluster\033[0m"
	        # Using 1 CPUs and varying the datasets samples considered
            mpirun -n 1 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun -n 1 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun -n 1 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 4 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 4 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 4 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 4 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 8 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 8 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 8 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 8 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4
            
            # Using 12 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 12 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 12 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 12 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 16 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 16 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 16 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 16 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 20 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 20 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 20 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 20 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4

            # Using 24 vCPUs and varying the datasets samples considered
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 24 ../../main.o ../../../Datasets/train.txt 1000 ../../../Datasets/test.txt 200 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 24 ../../main.o ../../../Datasets/train.txt 10000 ../../../Datasets/test.txt 2000 6 50 4
            mpirun --use-hwthread-cpus --hostfile my_hosts -n 24 ../../main.o ../../../Datasets/train.txt 20000 ../../../Datasets/test.txt 4000 6 50 4
            echo "\033[;34mEnded tests on FAT cluster\033[0m"
	        break
            ;;
	"QUIT")
	    exit
	    ;;
        *) echo "\033[0;31mInvalid option $REPLY\033[0m";;
    esac
done