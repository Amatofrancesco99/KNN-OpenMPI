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
int knn_prediction(Sample train_samples[], int train_N, int K, Sample test_sample, int NMAX_CLASSES, int N_FEATURES) {
    // Fill distances of all samples from the test sample
    for (int i = 0; i < train_N; i++)
        train_samples[i].distance = euclidian_distance(train_samples[i], test_sample, N_FEATURES);
  
    // Sort the train samples by distance from the test sample
    sort(train_samples, train_samples+train_N, comparison);
  
    // Get the classes of the k neighbors samples in the training set of the test sample
    int freq[NMAX_CLASSES];
    for (int i = 0; i < NMAX_CLASSES; i++) freq[i] = -1; // Initialize the occurrencies array
    for (int i = 0; i < K; i++) freq[train_samples[i]._class] += 1; // Count the occurrencies of train samples belonging to each class
    int max = -1, predicted_class = -1;
    // The test sample belongs to the class of the most occurring class of its K neighbor samples
    for (int i = 0; i < NMAX_CLASSES; i++) {
        if ((freq[i] > max)){
                max = freq[i];
                predicted_class = i;
        }
    }
    return predicted_class;
}


/* Function that returns the accuracy of the model.
IMPORTANT: If the desired accuracy is the training one it is just needed that test_samples = train_samples & test_N = train_N. */
float get_accuracy(Sample train_samples[], Sample test_samples[], int train_N, int test_N, int K, int NMAX_CLASSES, int N_FEATURES) {
    int correctly_classified_samples = 0;
    for (int i = 0; i < test_N; i++) {
        if (test_samples[i]._class == knn_prediction(train_samples, train_N, K, test_samples[i], NMAX_CLASSES, N_FEATURES)){ correctly_classified_samples += 1; }
    }
    return (correctly_classified_samples/(double)test_N)*100;
}


// Function that import data samples from a given file
void read_dataset(ifstream& file, Sample dataset_samples[], int N_SAMPLES, int N_FEATURES) {
    file.seekg(0, ios::beg);
    while (!file.eof()) {
        int i;
        for (i = 0; i <= N_SAMPLES; i++) {
            for (int j = 0; j< N_FEATURES; j++) file >> dataset_samples[i].features[j];
            file >> dataset_samples[i]._class;
        }
    }
    file.close();
}


// Main program
int main(int argc, char** argv) {
    // Help description
    if(argc == 2 && strcmp(argv[1], "--help") == 0)
        return print_description();
    else { 
        if(argc < 8) // Check that the number of inserted parameters is correct
            return print_error_and_exit("Please insert all the necessary parameters (for a complete description use --help option)");
        else { 
            // Loading files and parameters (checking also them)
            ifstream train_file;
            train_file.open(argv[1]);
            ifstream test_file;
            test_file.open(argv[3]);
            if (!train_file || !test_file) 
                return print_error_and_exit("Error when trying to open the files. Please retry");

            int N_TRAIN = stoi(argv[2]);
            int N_TEST = stoi(argv[4]);
            int K = stoi(argv[5]);
            int N_FEATURES = stoi(argv[6]);
            int N_CLASSES = stoi(argv[7]);

            if (N_TRAIN <= 0 || N_TEST <= 0 || K <= 0 || N_FEATURES <= 0 || N_CLASSES <= 0)
                return print_error_and_exit("All the numeric parameters must assume positive values");

            if (N_FEATURES > NMAX_FEATURES)
                return print_error_and_exit("The maximum number of features that a sample can have is 255");
            

            // Loading training dataset from the filed passed as input
            Sample train_samples[N_TRAIN];
            read_dataset(train_file, train_samples, N_TRAIN, N_FEATURES);
            // Loading testing dataset from the filed passed as input
            Sample test_samples[N_TEST];
            read_dataset(test_file, test_samples, N_TEST, N_FEATURES);

            // Assess the test accuracy of the obtained KNN model
            printf("KNN train accuracy: %.2f%%\n", get_accuracy(train_samples, train_samples, N_TRAIN, N_TRAIN, K, N_CLASSES, N_FEATURES));
            // Assess the test accuracy of the obtained KNN model
            printf("KNN test accuracy: %.2f%%\n", get_accuracy(train_samples, test_samples, N_TRAIN, N_TEST, K, N_CLASSES, N_FEATURES));

            return 0;
        }
    }
}