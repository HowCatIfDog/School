def Problem5():
    import numpy as np
    import scipy as sp
    from scipy import integrate
    import matplotlib as mpl
    import matplotlib.pyplot as plt

    t = np.linspace(0,5,100)

    r = 0.2
    L = 0.12
    w1 = 0.25*(t*t)
    w2 = 0.5*t

    x = [0]
    y = [0]
    theta0 = 0

    theta = r/(2*L) * (w1 - w2) * t + theta0




Problem5()
