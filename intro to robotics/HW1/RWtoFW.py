def RWtoFW():

    import numpy as np
    import scipy as sp
    import matplotlib as mpl
    import matplotlib.pyplot as plt

    x = []
    y = []

    a1, a2 = 15.0, 15.0
    #Part A
    # t = np . linspace(0,25, 500)
    # x = t
    # y = 25-x
    #Part B
    t = np . linspace(0,np.pi * 2, 50)
    x = 10 * np.cos ( t ) + 15
    y = 10 * np.sin ( t )

    #inverse kinematics
    d = ( (x*x) + (y*y) - (a1*a1) - (a2*a2) ) / ( 2* a1*a2 )
    t2 = np.arctan2(-np.sqrt (1.0 -d*d ) , d )
    t1 = np.arctan2 ( y , x ) - np.arctan2 ( a2*np.sin ( t2 ) , a1+a2*np.cos ( t2 ) )

    x1 = a2*np.cos ( t1+t2 ) + a1*np.cos ( t1 )
    y1 = a2*np.sin ( t1+t2 ) + a1*np . sin ( t1 )
    z = np.sum ( np.square ( x-x1 ) + np.square ( y-y1 ) )

    #ploting
    plt.figure(1)
    plt.subplot(221)
    plt.xlim( 0 , 30 )
    plt.ylim( -20 , 25 )
    plt.title('Requested Path')
    plt.plot( x , y, 'go-' )

    plt.subplot(222)
    plt.xlim( -3.14 , 3.14 )
    plt.ylim( -3.14 , 3.14 )
    plt.title('Joint Angles')
    plt.plot( t1 , t2 , 'ro-')

    plt.subplot(223)
    plt.xlim( 0 , 30 )
    plt.ylim( -20 , 25 )
    plt.title('Simulated Path')
    plt.plot( x1 , y1 )
    plt.show()

RWtoFW()
