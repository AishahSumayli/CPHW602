'''
Question5: Optional: (K1, S1, S2, S3 & S4)
create a plot for the data.txt file
'''

import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('data.txt')

x = data[:, 0]  # First column
y = data[:, 1]  # Second column
plt.plot(x,y)
plt.xlabel("X")
plt.ylabel("Y")
plt.grid()
plt.savefig("Q5.pdf")
plt.show()
# Create a plot
