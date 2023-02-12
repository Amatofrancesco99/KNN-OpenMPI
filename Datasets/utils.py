def print_error(message):
    print("\033[1;31m"+message+"\033[0m")

def print_description():
    print("\n\033[1;33mK-NEAREST NEIGHBOR CLASSIFICATION ALGORITHM - GENERATE TRAIN & TEST DATASETS\033[0m\n\n"
        "------------------------------------------------------------\n"
        "The following program, written in Python, allows to generate two general purpose multiclass datasets (already splitted into"
        " train and test sets).\n\n"
        "There are some arguments that must be passed to this program, in order to work properly, that are:\n"
        "\t - Overall number of samples \033[;32m[n_samples]\033[0m\n"
        "\t - Number of features for each sample (max 255) \033[;32m[n_features]\033[0m\n"
        "\t - Number of classes \033[;32m[n_classes]\033[0m\n"
        "\t - Percentage of samples to put in the train set (remaining fraction into the test set) \033[;32m[split]\033[0m\n"
        "\t - Apply MinMax scaling to avoid features with different value ranges \033[;32m[min-max_scaling]\033[0m\n"
        "\n\033[1mRun it:\033[0m $ python3 generate.py \033[;32m[n_samples] [n_features] [n_classes] [split] [min-max_scaling]\033[0m\n\n\n"
        "\033[;34mProgram developed by F. Amato & D. Ligari (Data Science track)\n"
        "Advanced Computer Architecture project\n"
        "University of Pavia - A.Y. 2022/23\033[0m\n\n");