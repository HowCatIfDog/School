def problem4():

    import numpy as np
    import scipy as sp
    from scipy import integrate
    import matplotlib as mpl
    import matplotlib.pyplot as plt

    t = np.arange(0, 20.05, 0.05)

    # Initial Conditions about robot
    L1 = 0.30
    L2 = 0.20
    r = 0.08

    # Wheel velocities
    FLW = 0.75*np.cos(t/3.0)
    FRW = 1.50*np.cos(t/3.0)
    BLW = -1.0
    BRW = 0.5

    # initialize x,y, and theta
    theta = [0]
    x = [0]
    y = [0]


    # space saving code
    short = (r*0.05)/4
    A = FLW+FRW+BLW+BRW
    B = -FLW+FRW+BLW-BRW
    C = -FLW+FRW-BLW+BRW

    for i in range(1, 201):
        theta.append(theta[i-1] + short*(1/(L1+L2)*C[i]))
        x.append(x[i-1] + short * (A[i] * np.cos(theta[i-1]) + B[i] * np.sin(theta[i-1])))
        y.append(y[i-1] + short * (A[i] * np.sin(theta[i-1]) + B[i] * np.cos(theta[i-1])))


    u = np.cos(theta)
    v = np.sin(theta)

    plt.quiver(x,y,u,v)
    plt.title("Chapter 5: Problem 4")

    plt.plot(x,y)
    plt.show()




problem4()
