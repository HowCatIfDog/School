def problem11():

    import numpy as np
    import scipy as sp
    import matplotlib as mpl
    import matplotlib.pyplot as plt

    x = []
    y = []

    a1, a2 = 15.0, 15.0
    #(5,0),(5,15),(20,15),(20,0)
    #x = (np.linspace(5,5,20), np.linspace(5,20,20), np.linspace(20,20,20), np.linspace(20,5,20))
    x = np.linspace(5,5,20)
    x = np.append(x,np.linspace(5,20,20))
    x = np.append(x,np.linspace(20,20,20))
    x = np.append(x,np.linspace(20,5,20))
    y = np.linspace(0,15,20)
    y = np.append(y,np.linspace(15,15,20))
    y = np.append(y,np.linspace(15,0,20))
    y = np.append(y,np.linspace(0,0,20))
    t = np.linspace(0,np.pi * 2, 50)

    d = ( (x*x) + (y*y) - (a1*a1) - (a2*a2) ) / ( 2* a1*a2 )
    t2 = np.arctan2(-np.sqrt (1.0 -d*d ) , d )
    t1 = np.arctan2 ( y , x ) - np.arctan2 ( a2*np.sin ( t2 ) , a1+a2*np.cos ( t2 ) )

    x1 = a2*np.cos ( t1+t2 ) + a1*np.cos ( t1 )
    y1 = a2*np.sin ( t1+t2 ) + a1*np . sin ( t1 )
    z = np.sum ( np.square ( x-x1 ) + np.square ( y-y1 ) )

    plt.figure(1)
    plt.subplot(221)
    plt.xlim( 0 , 25 )
    plt.ylim( -5 , 25 )
    plt.title('Requested Path')
    plt.plot( x , y, 'go-' )

    plt.subplot(222)
    plt.xlim( -3.14 , 3.14 )
    plt.ylim( -3.14 , 3.14 )
    plt.title('Joint Angles')
    plt.plot( t1 , t2 , 'ro-')

    plt.subplot(223)
    plt.xlim( 0 , 25 )
    plt.ylim( -5 , 25 )
    plt.title('Simulated Path')
    plt.plot( x1 , y1 )
    plt.show()

problem11()
