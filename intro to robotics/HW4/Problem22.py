def Problem22():

    import numpy as np
    import scipy as sp
    import matplotlib as mpl
    import matplotlib.pyplot as plt
    import math as math

    f = 7
    b = 100

    v1 = [2.0,2.2,2.2,1.8,1.8]
    v2 = [3.0,3.3,2.7,3.3,2.7]
    z = []

    for i in range(len(v1)):
        z.append((f*b)/(v1[i]+v2[i]))

    z_min = min(z)
    z_max = max(z)
    error_min = 100 * (z_min-z[0])/z[0]
    error_max = 100 * (z_max-z[0])/z[0]
    print("actual value: ", z[0])
    print("min value: ", z_min, "max value: ", z_max)
    print("error min: ", error_min, "error max: ", error_max)

Problem22()
