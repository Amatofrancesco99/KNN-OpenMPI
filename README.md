# KNN-OpenMPI
An Open MPI implementation of the **K-Nearest Neighbors algorithm**. It has been designed to solve classification problems.<br><br>
This repository contains the code for the final parallel programming project of the **Advanced Computer Architecture** course (University of Pavia - A.Y. 2022/23).<br><br>
If interested on a better description of this project, with also a discussion on the obtained performances, you can have a look at the following link: [official paper](/Report/paper.pdf).

<br>

![Views](https://komarev.com/ghpvc/?username=KNN-OpenMPI&label=Views&style=for-the-badge&color=blue)
![Google Cloud](https://img.shields.io/badge/Google_Cloud-4285F4?style=for-the-badge&logo=google-cloud&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/Python-FFD43B?style=for-the-badge&logo=python&logoColor=blue)

## Execution Instructions

### 1 - Setup the Git Repository
If not already done, download and install ```git``` from [git-scm.com](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git). 
Then clone the repository with the following command:
```bash
$ git clone https://github.com/Amatofrancesco99/KNN-OpenMPI.git
```

### 2 - Install OpenMPI
Download Open MPI 4.1.4 from the official [Open MPI website](https://www.open-mpi.org/software/ompi/v4.1/) and install it following the [official guide](https://www.open-mpi.org/faq/?category=building#easy-build). The project has been developed using Open MPI 4.1.4, but consider dowloading any compatible version of your choice. Furthermore, if you are not interested in the parallel implementation, this step is optional.

### 3 - Generate the Datasets
Provided you have installed Python on you computer, if you do not have a dataset you want to run the K-Nearest Neighbor algorithm on, you can run the Python script ```generate.py```, inside the ```Datasets``` folder, to generate a sample dataset (already splitted into train and test sets).

If you want to run it, move inside the ```Datasets``` folder, and run the following command:
```bash
$ python3 generate.py [n_samples] [n_features] [n_classes] [split] [min-max_scaling]
```

In the command illustrated above, ```n_samples``` is the number of samples you want to generate, ```n_features``` is the number of features that each sample must have (*max 255*), ```n_classes``` is the overall number of possible classes, ```split``` is the percentage of samples to put into the train set (the ramaining into the test, allowed values range from 0 to 100 - extreme excluded), ```min-max_scaling``` allows to select whether to apply MinMax scaling to the numerical features (1 to apply it, 0 otherwise).

All specified parameters must be inserted for a correct behavior.

**Note** that if you intend to run the application with your own dataset, it must comply some requisites:
- each line of the (train/test) file must represent a single data point, with the coordinates separated by a single space;
- all the numerical features (except the target one which is categorical) should be normalized a priori for well-known interpretability issues;
- the last element of each line must represent the class of the sample, and must be an integer value;

### 4 - Compile and Run the Program
To compile and run the serial application, run the following commands, moving inside the ```Serial``` folder:
```bash
$ g++ -Wall main.cpp -o executableFile.o
$ ./executableFile.o --help
$ ./executableFile.o [trainFile] [nTrainSamples] [testFile] [nTestSamples] [K] [nFeatures] [nClasses]
```

If you want to compile and run the parallel application instead, moving inside the ```Parallel``` folder, then compile and run the Open MPI program:
```bash
$ mpic++ -Wall main.cpp -o executableFile.o
$ mpirun executableFile.o --help
$ mpirun -n [N] executableFile.o [trainFile] [nTrainSamples] [testFile] [nTestSamples] [K] [nFeatures] [nClasses]
```

In the two commands above, ```N``` is the number of cores you want to execute the parallel application on, ```executableFile``` is the name you want to give to the executable application, ```trainFile``` and ```testFile``` are the files containing the datasets, ```nTrainSamples``` and ```nTestSamples``` are the number of samples starting from the top to use in the two datasets, ```K``` is the number of nearest neighbors to consider, ```nFeatures``` is the number of features to consider for each training and test sample (*max 255*), ```nClasses``` is the number of sample classes to consider.

All specified parameters must be inserted and for the numerical ones they all must be greater than 0.

When the program has finished running, both the obtained train and test accuracy are displayed, in order to assess some simple performance 
metrics. Please note that some improvements can be implemented in further iterations, such as: 
- specify other distance functions (not just the Euclidean one);
- obtain better performance metrics (like confusion matrix, instead of just overall accuracy), to better understand whether the obtained model is more polarized in recognizing a specific class with respect to another.

## Example
An example of the output provided, using the **Iris dataset** is the following (both Serial and Parallel version are providing almost same results, not exactly equal in some cases due to averages and approximations):
```bash
$ cd Serial
$ ./executableFile.o ../Datasets/train.txt 120 ../Datasets/test.txt 30 2 4 3
$ cd ../Parallel
$ mpirun -n 2 executableFile.o ../Datasets/train.txt 120 ../Datasets/test.txt 30 2 4 3
```

***
[![forthebadge](https://forthebadge.com/images/badges/powered-by-coders-sweat.svg)](https://forthebadge.com)