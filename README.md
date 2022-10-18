# KNN-OpenMPI
An Open MPI implementation of the **K-Nearest Neighbor algorithm**. It has been designed to solve classification problems.<br><br>
This repository contains the code for the final parallel programming project of the **Advanced Computer Architecture** course (University of Pavia - A.Y. 2022/23).

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
Download Open MPI 4.0.5 from the official [Open MPI website](https://www.open-mpi.org/software/ompi/v4.0/) and install it following the [official guide](https://www.open-mpi.org/faq/?category=building#easy-build). The project has been developed using Open MPI 4.0.5, but consider dowloading any compatible version of your choice. Furthermore, if you are not interested in the parallel implementation, this step is optional.

### 3 - Generate the Datasets
Provided you have installed Python on you computer, if you do not have a dataset you want to run the K-Nearest Neighbor algorithm on, you can run the Python script ```generate.py```, inside the ```Datasets``` folder, to generate sample datasets of your choice.

Please note that if you intend to run the application with your own dataset, it must comply some simple requisites:
- each line of the (train/test) file must represent a single data point, with the coordinates separated by a single space;
- the last element of each line must represent the class of the sample, and must be an integer value.

### 4 - Compile and Run the Program
To compile and run the serial application, run the following commands, moving inside the ```Serial``` folder:
```bash
$ g++ -Wall *.cpp -o executableFile
$ ./executableFile --help
$ ./executableFile [trainFile] [nTrainSamples] [testFile] [nTestSamples] [K] [nFeatures] [nClasses]
```

If you want to compile and run the parallel application instead, moving inside the ```Parallel``` folder, then compile and run the Open MPI program:
```bash
$ mpicc -Wall *.cpp -o executableFile
$ mpirun -n N executableFile [parameters]
```

In the two commands above, ```N``` is the number of cores you want to execute the parallel application on, ```executableFile``` is the name you want to give to the executable application, ```trainFile``` and ```testFile``` are the files containing the datasets, ```nTrainSamples``` and ```nTestSamples``` are the number of samples starting from the top to use in the two datasets, ```K``` is the number of nearest neighbors to consider, ```nFeatures``` is the number of features to consider for each training and test sample (*max 255*), ```nClasses``` is the number of sample classes to consider.

Every parameter must be inserted and for the numerical ones they all must be greater than 0.

When the program has finished running, both the obtained train and test accuracy are displayed, in order to assess some simple performance 
metrics. Please note that better performance metrics can be further implemented to understand, for example, whether our classifier is biased on recognizing more a class with respect to others.

## Example
An example of the output provided, using the standard **Iris dataset** (as generated by the already discussed Python script), is the following:
```bash
$ ./executableFile ../Datasets/train.txt 120 ../Datasets/test.txt 30 10 4 3
KNN Train accuracy: 97.50%
KNN Test accuracy: 96.67%
```

***
[![forthebadge](https://forthebadge.com/images/badges/powered-by-coders-sweat.svg)](https://forthebadge.com)
