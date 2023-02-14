#this script download the knn program and create the executable file
#in order to be ready for the execution
git clone git@github.com:Amatofrancesco99/KNN-OpenMPI.git
# send  the dataset 
# scp $HOME/github/KNN-OpenMPI/Datasets/*.txt  username@VM_IP_address:$HOME/KNN-OpenMPI/Datasets
cd KNN-OpenMPI/Parallel
mpic++ -Wall main.cpp
# on the master create my_hostFile file structured in the following way
# slave_ip_address_1 slots= number_of_available_slots
# slave_ip_address_2 slots= number_of_available_slots
# ....
# slave_ip_address_n slots= number_of_available_slots
# to execute the mpi program run the following istruction
# mpirun --hostﬁle my_hostFile -n number_of_nodes a.out