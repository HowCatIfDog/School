import numpy as np
import scipy as sp
import matplotlib as mpl
import matplotlib.pyplot as plt
import math as m


points = np.array([[0, 0],[1, 1],[2, 0], [3, -1],[4, 0],[5, 1],[4, 2],[3, 3],[2, 3],[1, 2],[0, 1],[0, 0]])
points = points*10
r = 2.0
l = 5.0
dt  = 0.01
Tend = 6.0
N = int(Tend/dt)

xend = 0
yend = 0
v = 10.0
k1 = 5.0
k2 = 0.2

x = np.zeros(N)
y = np.zeros(N)
th = np.zeros(N)

j=0
i= 0
for i in range(len(points)):
    xend = points[j,0]
    yend = points[j,1]
    xerr = xend-x
    yerr = yend-y

    while(i<N-1):
        th_err = np.arctan2(yend - y[i], xend - x[i]) - th[i]

        # xerr = points[j,0]-x[i]
        # yerr = points[j,1]-y[i]
        # v1 = complex(xerr, yerr)
        # thetaDesired = np.angle(v1, deg=1)
        # th_err = thetaDesired - th[i]

        # print("theta error: ", th_err)
        d1 = abs(x[i] - xend)
        d2 = abs(y[i] - yend)
        # print("d1: ", d1, "d2: ", d2)
        w = v
        d = m.sqrt(d1*d1+d2*d2)
        # print("distance: ", d)

        if (d<0.5):
            break

        if (d > 10000):
            break

        w1 = w + k1*th_err
        w2 = w - k1*th_err
        if (d<5.0):
            w1, w2 = k2*d*(w + k1*th_err), k2*d*(w - k1*th_err)

        # v = (r*dt/2.0)*(w1+w2)
        dx = (r*dt/2.0)*(w1+w2)*np.cos(th[i])
        dy = (r*dt/2.0)*(w1+w2)*np.sin(th[i])
        # print("dx: ", dx, "dy: ", dy)
        dth = (r*dt/(2.0*l))*(w1-w2)
        x[i+1] = x[i] + dx
        y[i+1] = y[i] + dy
        th[i+1] = th[i] + dth
        # print("theta: ", th[i])
        i = i+1

    j += 1

pointsX = points[:,0]
pointsY = points[:,1]
plt.title('Point Tracking')
plt.plot( x , y , label="Simulated Path")
plt.plot(pointsX, pointsY, 'o', color='red', label="Desired Points")
plt.show()


# # initial conditions
# x = 0
# y = 0
# theta = 0
# vdot = 0
#
# Kp = 0.2 #proportional gain
# ts = 0.1 #time step
#
# for i in range(len(points)):
#     xerr = points[i,0]-x
#     yerr = points[i,1]-y
#
#     while(xerr > 0.05 and yerr > 0.05):
#         # find angle error
#         xerr = points[i,0]-x
#         yerr = points[i,1]-y
#
#         v1 = complex(xerr, yerr)
#
#         thetaDesired = np.angle(v1, deg=1)
#         thetaErr = thetaDesired - theta
#
#         print(thetaDesired, "   ", thetaErr, "   ", theta)
#
#         # update angle
#         theta = theta + Kp*thetaErr*ts
#
#         # update velocity
#         xcomp = vdot*np.cos(theta)
#         ycomp = vdot*np.sin(theta)
#         vcurr = complex(xcomp,ycomp)
#         vdesired = np.vdot(v1, vcurr)
#         vdot = vdot + Kp*vdesired*ts
#
#         # update position
#         x = x + Kp*vdot*np.cos(theta)*ts
#         y = y + Kp*vdot*np.sin(theta)*ts
#
#         # print(x,"  ",y)
#
#     print("point reached")
