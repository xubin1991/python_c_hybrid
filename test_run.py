import numpy as np
import matplotlib.pyplot as plt
import cos_doubles
from scipy.spatial.transform import Rotation as R

rot = R.from_euler('xyz',(1,2,3))
rotM = rot.as_matrix()
rot_q = rot.as_quat()
c_q = cos_doubles.matrixToQuaternion(rotM)
print(rot_q)
print(c_q)
x = np.arange(0, 2 * np.pi, 0.1)
y = cos_doubles.cos_doubles_func(x)
plt.plot(x, y)
plt.show()