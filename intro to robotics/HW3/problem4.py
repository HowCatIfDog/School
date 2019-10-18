def problem4():

    import numpy as np
    import scipy as sp
    from scipy import integrate
    import matplotlib as mpl
    import matplotlib.pyplot as plt

    t = np.arange(0, 20.05, 0.05)

    L1 = 0.30
    L2 = 0.20
    r = 0.08

    FLW = 0.75*np.cos(t/3.0)
    FRW = 1.50*np.cos(t/3.0)
    BLW = -1.0
    BRW = 0.5

    theta = np.zeros(201)
    x = np.zeros(201)
    y = np.zeros(201)

    short = (r*0.05)/4

    A = FLW+FRW+BLW+BRW
    B = -FLW+FRW+BLW-BRW
    C = -FLW+FRW-BLW+BRW

    for i in range(0, 200):
        thetaNext = theta[i] + short*(1/(L1+L2)*C)
        xNext = x[i] + short * (A * np.cos(theta[i]) + B * np.sin(theta[i]))
        yNext = y[i] + short * (A * np.sin(theta[i]) + B * np.cos(theta[i]))
        x[i+1] = xNext
        y[i+1] = yNext
        theta[i+1] = thetaNext

    plt.plot(x,y)
    plt.show()

    # thetaDot = (r/4) * C * (1/(L1+L2))
    # theta = integrate.simps(thetaDot)
    #
    # xvel = (r/4) * (A*np.cos(theta) + B*np.sin(theta))
    # yvel = (r/4) * (A*np.sin(theta) + B*np.cos(theta))
    #
    # x = np.trapz(xvel)
    # y = integrate.simps(yvel)

    print(x)
    print(y)

problem4()
