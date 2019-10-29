def Problem12():

    import numpy as np
    import scipy as sp
    import matplotlib as mpl
    import matplotlib.pyplot as plt
    import math as math

    z = [20,20,100,100]
    x = [10,29,10,29]

    f = 0.8
    b = 30

    for i in range(len(z)):
        u = f/(z[i]/x[i])
        alpha = np.arctan(z[i]/(b-x[i]))
        print(u,alpha)



Problem12()
