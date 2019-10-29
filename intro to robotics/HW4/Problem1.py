def Problem1():

    import numpy as np
    import scipy as sp
    import matplotlib as mpl
    import matplotlib.pyplot as plt
    import math as math
    # from math import *


    # Location of the beacons and distances
    L = [[884,554,713,222],[120,703,771,843],[938,871,583,436],[967,653,46,529],[593,186,989,610]]

    def funct(x,y,z):
        F = np.sqrt((x-L[0][0])*(x-L[0][0]) + (y-L[0][1])*(y-L[0][1]) + (z-L[0][2])*(z-L[0][2])) - L[0][3]
        G = np.sqrt((x-L[1][0])*(x-L[1][0]) + (y-L[1][1])*(y-L[1][1]) + (z-L[1][2])*(z-L[1][2])) - L[1][3]
        H = np.sqrt((x-L[2][0])*(x-L[2][0]) + (y-L[2][1])*(y-L[2][1]) + (z-L[2][2])*(z-L[2][2])) - L[2][3]
        I = np.sqrt((x-L[3][0])*(x-L[3][0]) + (y-L[3][1])*(y-L[3][1]) + (z-L[3][2])*(z-L[3][2])) - L[3][3]
        K = np.sqrt((x-L[4][0])*(x-L[4][0]) + (y-L[4][1])*(y-L[4][1]) + (z-L[4][2])*(z-L[4][2])) - L[4][3]

        F=F*F
        G=G*G
        H=H*H
        I=I*I
        K=K*K

        E = F+G+H+I+K
        # print(E)
        return E

    # Numerical gradient approximation
    def grad(x,y,z):
        delta = 0.0001
        E = funct(x,y,z)
        E1 = funct(x+delta,y,z)
        E2 = funct(x,y+delta,z)
        E3 = funct(x,y,z+delta)
        dEx = (E1-E)/delta
        dEy = (E2-E)/delta
        dEz = (E3-E)/delta
        return dEx, dEy, dEz


    # The size of the vector
    def norm(r,s,q):
        return np.sqrt(r*r+s*s+q*q)

    # The step in the direction (u,v)
    def step(x,y,z, u,v,w,t):
        a = x - t*u
        b = y - t*v
        c = z - t*w
        return a, b, c


    # Globals
    x = 5000
    y = 5000
    z = 5000
    t = 20.0
    tsmall = 0.00001

    # The descent algorithm
    while (t > tsmall):
        dx, dy, dz = grad(x,y,z)
        size = norm(dx,dy,dz)
        u = dx/size
        v = dy/size
        w = dz/size
        a,b,c = step(x,y,z,u,v,w,t)
        while (funct(a,b,c) > funct(x,y,z)):
            t = 0.5*t
            a,b,c = step(x,y,z,u,v,w,t)
        x,y,z = a,b,c

    print(x, y, z)

Problem1()
