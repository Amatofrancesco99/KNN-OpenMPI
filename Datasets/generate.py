# This simple snippet of Python code generates two samples datasets ('train.txt' & 'test.txt') used to check 
# the C++ K-Nearest Neighbor Classifier implementation (serial/openMPI), starting from some parameters passed by the user.
from sklearn import datasets, preprocessing
from sklearn.model_selection import train_test_split
import numpy as np, sys, utils

if len(sys.argv) != 6:
    utils.print_error("It seems you did not pass all the required parameters to generate the train and test datasets.")
    utils.print_description()
    exit() 
else:
    n_samples = int(sys.argv[1])
    n_features = int(sys.argv[2])
    n_classes = int(sys.argv[3])
    split = int(sys.argv[4])
    apply_scaling = bool(int(sys.argv[5]))
    
    # Checks on passed parameters
    if (n_samples <= 0 or n_features <= 0 or n_classes <= 0 or split <= 0 or apply_scaling < 0):
        utils.print_error("All the numeric parameters must assume positive values.")
        exit()
    if (n_features > 255):
        utils.print_error("The maximum number of features that a sample can have is 255.")
        exit()

# Generate dataset and divide in train & test
X, y = datasets.make_classification(n_samples=n_samples, n_features=n_features, n_informative=n_classes, n_classes=n_classes)
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=(split/100))

# Scaling numerical features
if (apply_scaling == True):
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