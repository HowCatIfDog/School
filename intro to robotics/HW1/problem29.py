def problem29():

    import numpy as np
    import scipy as sp
    import matplotlib as mpl
    import matplotlib.pyplot as plt

    w1 = []
    w2 = []
    #initial conditions
    x0, y0, theta0 = 0, 0, 0

    #fill t w1 and w2 arrays
    t = np.linspace(0,10,100)
    w1 = np.linspace(2,2,50)
    w1 = np.append(w1,np.linspace(3,3,10))
    w1 = np.append(w1,np.linspace(1,1,40))

    w2 = np.linspace(2,2,50)
    w2 = np.append(w2,np.linspace(4,4,10))
    w2 = np.append(w2,np.linspace(2,2,40))

    #known parameters
    D = 10
    L = 16
    r = D/2

    #find theta
    thetaDot = (r/(2*L) * (w1 - w2) * t ) + theta0
    #integrate thetaDot
    # theta = np.trapz(thetaDot)
    #
    # #find the final location
    # xdot = (r/2) * (w1+w2) * np.cos(thetaDot)
    # ydot = (r/2) * (w1+w2) * np.sin(thetaDot)

    theta = r/(2*L) * (w1 - w2) * t + theta0

    wparttop = (w1+w2)
    wpartbot = (w1-w2)
    for n, i in enumerate(wpartbot):
        if i == 0:
            wpartbot[n] = 0.0001

    print(wpartbot)
    wpart = wparttop/wpartbot
    x = L * wpart * np.sin(theta) + x0
    y = L * -wpart * np.cos(theta) + y0

    # x = np.trapz(xdot)
    # y = np.trapz(ydot)

    # print(thetaDot)
    # print(theta)

    #print(theta)
    print(x)
    print(y)

    plt.xlim( 0 , 100)
    plt.ylim( -5 , 100 )
    plt.title('Simulated Path')
    plt.plot( x , y )
    plt.show()

problem29()
