import numpy as np
import matplotlib.pyplot as plt
import cos_doubles

x = np.arange(0, 2 * np.pi, 0.1)
y = cos_doubles.cos_doubles_func(x)
plt.plot(x, y)
plt.show()