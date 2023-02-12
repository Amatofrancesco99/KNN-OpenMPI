# This simple snippet of Python code generates two sample files ('train.txt' & 'test.txt') used to check 
# the C++ K-Nearest Neighbor Classifier implementation (serial/openMPI).
# In this case the Iris classification dataset has been chosen.
from sklearn import datasets, preprocessing
from sklearn.model_selection import train_test_split
import numpy as np, sys, pandas as pd

if len(sys.argv) != 5:
    print('Please pass all the needed parameters.')
    exit()
if sys.argv[1] == "-- help":
    print('')
else:
    n_samples = int(sys.argv[1])
    n_features = int(sys.argv[2])
    n_classes = int(sys.argv[3])
    split = int(sys.argv[4])

# Load Iris dataset and divide in train & test
X, y = datasets.make_classification(n_samples=n_samples, n_features=n_features, n_informative=n_classes, n_classes=n_classes)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=(split/100))

# Scaling numerical features
minmax_scaler = preprocessing.MinMaxScaler().fit(X_train)
X_train = minmax_scaler.transform(X_train)
X_test = minmax_scaler.transform(X_test)

# Store the datasets
train_df = np.hstack((X_train, y_train[:,None]))
test_df = np.hstack((X_test, y_test[:,None]))
fmt = []
for i in range(n_features):
    fmt.append('%.1f')
fmt.append('%d')
np.savetxt(r'train.txt', train_df, fmt=fmt)
np.savetxt(r'test.txt', test_df, fmt=fmt)