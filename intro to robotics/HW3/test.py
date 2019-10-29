def test():

    import numpy as np
    import scipy as sp
    from scipy import integrate
    import matplotlib as mpl
    import matplotlib.pyplot as plt

    theta = [0]
    x = [0]
    y = [0]

    for i in range(1, 21):
        theta.append(theta[i-1] + 1)
        x.append(x[i-1] + np.cos(theta[i-1]))
        y.append(y[i-1] + np.cos(theta[i-1]))


    print(theta)
    print(x)
    print(y)

test()
