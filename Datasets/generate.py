# This simple snippet of Python code generates two sample files ('train.txt' & 'test.txt') used to check 
# the C++ K-Nearest Neighbor Classifier implementation (serial/openMPI).
# In this case the Iris classification dataset has been chosen, from sklearn.
from sklearn import datasets
from sklearn.model_selection import train_test_split
import numpy as np

dataset = datasets.load_iris()
X_train, X_test, y_train, y_test = train_test_split(dataset.data, dataset.target, test_size=0.2)
train_df = np.hstack((X_train, y_train[:,None]))
test_df = np.hstack((X_test, y_test[:,None]))
fmt = '%.1f', '%.1f', '%.1f', '%.1f', '%d'
np.savetxt(r'train.txt', train_df, fmt=fmt)
np.savetxt(r'test.txt', test_df, fmt=fmt)