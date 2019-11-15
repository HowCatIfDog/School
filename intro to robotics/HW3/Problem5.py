def Problem5():
    import numpy as np
    import scipy as sp
    from scipy import integrate
    import matplotlib as mpl
    import matplotlib.pyplot as plt

    timepoints = 1000
    t = np.linspace(0,5,timepoints)
    dt = 5/timepoints

    r = 20
    L = 12
    w1 = 0.25*(t*t)
    w2 = 0.5*t

    #noise generation
    mu, sigma = 0.0, 0.01
    xerr = np.random.normal(mu,sigma, timepoints)
    yerr = np.random.normal(mu,sigma, timepoints)

    # comment out to include error
    # xerr = np.zeros(timepoints)
    # yerr = np.zeros(timepoints)

    x = np.array([0.0])
    y = np.array([0.0])
    theta0 = np.array(0)

    theta = r/(2*L) * (w1 - w2) * t + theta0
    for i in range(len(t)):
        xnew = (x[i-1] + xerr[i] + (r*dt/2.0) * (w1[i]+w2[i]) * np.cos(theta[i]))
        ynew = (y[i-1] + yerr[i] + (r*dt/2.0) * (w1[i]+w2[i]) * np.sin(theta[i]))
        x = np.append(x, xnew)
        y = np.append(y, ynew)

    plt.title('Simulated Path')
    plt.plot( x , y )
    plt.show()


Problem5()
