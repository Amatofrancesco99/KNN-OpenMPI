#include <string>

// This function displays an error message and exit from program flow
void print_error(const char* error_message) { printf("\033[1;31m%s\033[0m\n", error_message); }


// Function that returns a boolean value indicating whether input file is empty or not
bool check_if_empty(std::ofstream &file){
    file.seekp(0, std::ios_base::end);  // go to end
    bool empty = (file.tellp() == 0);
    return empty;
}


// This function saves into a file, passed as parameter, the execution time (in seconds) and the configuration
void save_execution_details(const char* file, int N_SAMPLES, int V_CPU, double EXECUTION_TIME) { 
    std::ofstream outfile;
    outfile.open(file, std::ios_base::app); // append instead of overwrite
    // If the file is empty add the header line
    if (check_if_empty(outfile)){
        outfile << "N_SAMPLES, V_CPU, EXECUTION_TIME \n";
    }
    outfile << N_SAMPLES << ", " << V_CPU << ", " << EXECUTION_TIME << "\n";
    outfile.close();
}


// This function describes the program when the help parameter is inserted
void print_description() {
    printf("\n\033[1;33mK-NEAREST NEIGHBOR CLASSIFICATION ALGORITHM - PARALLEL VERSION\033[0m\n\n"
        "------------------------------------------------------------\n"
        "The following program, written in C++, allows to perform an high performance computing (HPC - OpenMPI) calculation (using multiple CPUs) of the "
        "well known K-Nearest Neighbors Machine Learning algorithm.\n\n"
        "It is a non-parametric supervised learning method, used, in this specific implementation, to solve a general purpose classification problem.\n"
        "The classification works basically by considering the K closest training points of a given sample, and the predicted class of the 'fresh' sample "
        "is given by the most common class among its K nearest neighbors.\n"
        "The distance functions used to understand what are the nearest points can be multiple, in this specific implementation the only one considered is the "
        "Euclidian one.\n"
        "This version, with respect to the serial one, scales up exploiting the computational power of multiple cores architecture. "
        "So, theoretically, the higher the cores the lower the execution time, until a certain limit is reached."
        "There are some arguments that can be passed to this program, in order to work properly, that are:\n"
        "\t - The number of cores to use \033[;32m[N]\033[0m\n"
        "\t - Training dataset file \033[;32m[trainFile]\033[0m\n"
        "\t - Number of training points to use \033[;32m[nTrainSamples]\033[0m\n"
        "\t - Test dataset file \033[;32m[testFile]\033[0m\n"
        "\t - Number of test points to use \033[;32m[nTestSamples]\033[0m\n"
        "\t - Number of neighbors to consider \033[;32m[K]\033[0m\n"
        "\t - Number of features for each training and test sample (max 255) \033[;32m[nFeatures]\033[0m\n"
        "\t - Number of possible classes \033[;32m[nClasses]\033[0m\n"
        "\n\033[1mRun it:\033[0m $ mpirun -n \033[;32m[N]\033[0m executableFile \033[;32m[trainFile] [nTrainSamples] [testFile] [nTestSamples] [K] [nFeatures] [nClasses]\033[0m\n\n\n"
        "\033[;34mProgram developed by F. Amato & D. Ligari (Data Science track)\n"
        "Advanced Computer Architecture project\n"
        "University of Pavia - A.Y. 2022/23\033[0m\n\n");
}