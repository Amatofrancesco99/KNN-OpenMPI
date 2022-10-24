#include <mpi.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <fstream>
#include "utils.cpp"

using namespace std;
#define NMAX_FEATURES 255


// Define the characteristics of a sample placed in r^n
struct Sample {
    double features[NMAX_FEATURES]; // Sample coordinates
    int _class;                     // Group of sample
    double distance;                // Distance from a single specific test sample (this feature changes when considering a different test sample)
};
  

// Used to sort an array of samples by ascending order of distance
bool comparison(Sample a, Sample b) { return (a.distance < b.distance); }


// Get the euclidian distance between two samples placed in r^n
double euclidian_distance(Sample train_sample, Sample test_sample, int N_FEATURES) {
    double sum = 0;
    for (int i=0; i < N_FEATURES; i++){
        sum += pow((train_sample.features[i] - test_sample.features[i]), 2);
    }
    return sqrt(sum);
}


// This function finds the class of a given test sample using K nearest neighbor algorithm.
int knn_prediction(Sample train_samples[], int N_TRAIN, int K, Sample test_sample, int N_CLASSES, int N_FEATURES) {
    // Fill distances of all samples from the test sample
    for (int i = 0; i < N_TRAIN; i++)
        train_samples[i].distance = euclidian_distance(train_samples[i], test_sample, N_FEATURES);
  
    // Sort the train samples by distance from the test sample
    sort(train_samples, train_samples+N_TRAIN, comparison);
  
    // Get the classes of the k neighbors samples in the training set of the test sample
    int freq[N_CLASSES];
    for (int i = 0; i < N_CLASSES; i++) freq[i] = -1; // Initialize the occurrencies array
    for (int i = 0; i < K; i++) freq[train_samples[i]._class] += 1; // Count the occurrencies of train samples belonging to each class
    int max = -1, predicted_class = -1;
    // The test sample belongs to the class of the most occurring class of its K neighbor samples
    for (int i = 0; i < N_CLASSES; i++) {
        if ((freq[i] > max)){
                max = freq[i];
                predicted_class = i;
        }
    }
    return predicted_class;
}


/* Function that returns the accuracy of the model.
IMPORTANT: If the desired accuracy is the training one it is just needed that test_samples = train_samples & N_TRAIN = N_TEST. */
double get_accuracy(Sample train_samples[], Sample test_samples[], int N_TRAIN, int N_TEST, int K, int N_CLASSES, int N_FEATURES) {
    int correctly_classified_samples = 0;
    for (int i = 0; i < N_TEST; i++) {
        if (test_samples[i]._class == knn_prediction(train_samples, N_TRAIN, K, test_samples[i], N_CLASSES, N_FEATURES))
            correctly_classified_samples += 1;
    }
    return (correctly_classified_samples/(double)N_TEST)*100;
}


// Function that import data samples from a given file
void read_dataset(ifstream& file, Sample dataset_samples[], int N_SAMPLES, int N_FEATURES) {
    file.seekg(0, ios::beg);
    while (!file.eof()) {
        int i;
        for (i = 0; i <= N_SAMPLES; i++) {
            for (int j = 0; j < N_FEATURES; j++) file >> dataset_samples[i].features[j];
            file >> dataset_samples[i]._class;
        }
    }
    file.close();
}


// Main program
int main(int argc, char** argv) {
    int MYRANK, SIZE;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &MYRANK);
    MPI_Comm_size(MPI_COMM_WORLD, &SIZE);

    // Help description
    if((argc == 2 && strcmp(argv[1], "--help") == 0)) {
        if (MYRANK == 0) print_description();
        MPI_Finalize(); return EXIT_SUCCESS;
    } 
    else { 
        if(argc < 8) { // Check that the number of inserted parameters is correct
            if (MYRANK == 0) print_error("Please insert all the necessary parameters (for a complete description use --help option)");
            MPI_Finalize(); return EXIT_FAILURE;
        } else { 
            // Loading files and parameters
            ifstream train_file;
            train_file.open(argv[1]);
            ifstream test_file;
            test_file.open(argv[3]);
        
            int N_TRAIN = stoi(argv[2]);
            int N_TEST = stoi(argv[4]);
            int K = stoi(argv[5]);
            int N_FEATURES = stoi(argv[6]);
            int N_CLASSES = stoi(argv[7]);

            Sample train_samples[N_TRAIN], test_samples[N_TEST];

            if (MYRANK == 0) {
                // Check parameters correctness
                if (!train_file || !test_file) {
                    print_error("Error when trying to open the files. Please retry");
                    MPI_Finalize(); return EXIT_FAILURE;
                }
                if (N_TRAIN <= 0 || N_TEST <= 0 || K <= 0 || N_FEATURES <= 0 || N_CLASSES <= 0) {
                    print_error("All the numeric parameters must assume positive values");
                    MPI_Finalize(); return EXIT_FAILURE;
                }
                
                if (N_FEATURES > NMAX_FEATURES) {
                    print_error("The maximum number of features that a sample can have is 255");
                    MPI_Finalize(); return EXIT_FAILURE;
                }

                /* Loading training & test datasets from the files passed as input - the master reads both the two datasets since 
                parallelizing this procedure (file read) is neither simple, nor induces an expected significant improvement in the speedup */
                read_dataset(train_file, train_samples, N_TRAIN, N_FEATURES);
                read_dataset(test_file, test_samples, N_TEST, N_FEATURES);
            }
            

            /*  HOW TO PARALLELIZE THE KNN ALGORITHM? In order to do so, the following behavior has been implemented (this is referred to 
            obtain the overall test accuracy - same reasoning when considering the overall train accuracy)
            1) The master sends in broadcast (MPI_Bcast) to all slaves the training samples (used to compute distances)
            2) The master splits (MPI_Scatter) the test samples in same groups of N_TEST/SIZE (@TODO: fix the case when N_TEST is
               not divisible by # cores)
            3) Each node performs the KNN prediction of the test samples subset (using all the train samples to perform distances and every
               node sorts, ...). The slaves return the obtained weighted accuracy = samples accuracy * N_SAMPLES (this, since not all the nodes 
               perform the knn accuracy considering the same number of samples and so the accuracy should be weighted)
            4) Once all the nodes have performed the test samples subset accuracy they return the obtained result to the master (MPI_REDUCE)
               that performs a reducing function (sum of all the weighted accuracies)
            5) The master node prints the obtained overall accuracy, dividing the sum of the weighted accuracies by the total number of
               test samples.  */

            // Send to all slaves the train samples and assess the train accuracy (@TODO: fix it!)
            MPI_Bcast(train_samples, N_TRAIN, MPI_BYTE, 0, MPI_COMM_WORLD);
            Sample train_samples_node_process[int(N_TRAIN/SIZE)];
            MPI_Scatter(train_samples, int(N_TRAIN/SIZE), MPI_BYTE, train_samples_node_process, int(N_TRAIN/SIZE), MPI_BYTE, 0, MPI_COMM_WORLD);
            double weighted_node_train_accuracy = get_accuracy(train_samples, train_samples_node_process, N_TRAIN, int(N_TRAIN/SIZE), K, N_CLASSES, N_FEATURES);
            double sum_weighted_nodes_train_accuracies;
            MPI_Reduce(&weighted_node_train_accuracy, &sum_weighted_nodes_train_accuracies, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);         
            if (MYRANK == 0) printf("KNN train accuracy: %.2f%%\n", sum_weighted_nodes_train_accuracies/SIZE);

            // Send to all slaves the test samples to work with and assess the test accuracy (@TODO: fix it!)
            Sample test_samples_node_process[int(N_TEST/SIZE)];
            MPI_Scatter(test_samples, int(N_TEST/SIZE), MPI_BYTE, test_samples_node_process, int(N_TEST/SIZE), MPI_BYTE, 0, MPI_COMM_WORLD);
            double weighted_node_test_accuracy = get_accuracy(train_samples, test_samples_node_process, N_TRAIN, int(N_TEST/SIZE), K, N_CLASSES, N_FEATURES);
            double sum_weighted_nodes_test_accuracies;
            MPI_Reduce(&weighted_node_test_accuracy, &sum_weighted_nodes_test_accuracies, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            if (MYRANK == 0) printf("KNN test accuracy: %.2f%%\n", sum_weighted_nodes_test_accuracies/SIZE);
    
            MPI_Finalize();

            return EXIT_SUCCESS;
        }
    }
}