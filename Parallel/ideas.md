# HOW TO PARALLELIZE THE KNN ALGORITHM?

> N.B: This is referred to obtain the *overall test accuracy* (same reasoning when considering the overall train accuracy)<br>


In order to do so, the following behavior has been implemented:

1. The master sends in broadcast - `MPI_Bcast` - to all slaves the train samples (used to compute distances)
2. The master splits - `MPI_Scatter` - the test samples in same groups of `N_TEST/SIZE` - @TODO: fix the case when N_TEST is not divisible by # cores
3. Each node performs the `KNN prediction` of the test samples subset (using all the train samples to perform distances and every node sorts, ...). <br> The slaves return the obtained `weighted accuracy = samples accuracy * N_SAMPLES` (the accuracy should be weighted since not all the nodes perform the knn accuracy considering the same number of samples)
4. Once all the nodes have performed the test accuracy, on the subset of data they can work on, they return the obtained result to the master - `MPI_REDUCE` -
that performs a reducing function (sum of all the weighted accuracies)
5. The master node prints the overall accuracy, dividing the sum of the all nodes weighted accuracies by the total number of test samples.