import subprocess
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap


# Compile the C++ program (if not already compiled)
subprocess.run(["g++", "Task_1.cpp", "-o", "Task_1"])

# Run the C++ executable and capture its output while displaying it in the terminal
cpp_executable = "./Task_1"
process = subprocess.Popen([cpp_executable], stdout=subprocess.PIPE, universal_newlines=True)

# Initialize an empty matrix
matrix = []

# Parse the output line by line
for line in process.stdout:
    # Print the output line to display it in the terminal
    print(line, end="")
    
    # Parse the line to extract matrix values
    values = [int(x) for x in line.split()]
    matrix.append(values)

# Convert the matrix to a NumPy array for easier manipulation
matrix = np.array(matrix)
num_rows, num_cols = matrix.shape
numUniqueValues = len(np.unique(matrix))

colors = ['white', 'black'] + [plt.cm.tab10(i) for i in range(numUniqueValues-1)]
custom_cmap = plt.cm.colors.ListedColormap(['black', 'white', 'red', 'blue', 'green'])

plt.imshow(matrix, cmap=custom_cmap, interpolation='nearest', vmin=-1, vmax=3)
plt.xticks([])
plt.yticks([])
# plt.grid(True, which='both', color='gray', linestyle='-', linewidth=1)
plt.show()

# Display the matrix
print("\nInput matrix:")
print(matrix)
