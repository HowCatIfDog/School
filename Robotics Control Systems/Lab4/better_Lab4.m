
clc
clear
close all

%Define the Time Span
tSpan = 5 ;

%Define t h e X and Y Ranges
xRange = 5 ;
yRange = 5 ;

%Create the Range of X and Y Values
x1 = linspace(-xRange , xRange , xRange*2*tSpan ) ;
x2 = linspace (-yRange , yRange , yRange*2*tSpan ) ;
[ x1 , x2 ] = meshgrid ( x1 , x2 ) ;

%Define the Non−Linear Differential Equations
uNL = x1 + x1.*x2 ; %u
vNL = -x2 + x2.^2 + x1.*x2 + x1.^3 ; %v

%Define the Linear Differential Equations
uL = x1 + 2*x2 ;
vL = 3*x1 +2*x2 ;

%Define t h e Pendulum Differential Equations
g = -9.81; % Gravity Constant
l = 10;

% Pendulum String Length
k = 0.50; % Damping Coefficient
m = 10;

% Pendulum Mass
uPen = x2 ;
vPen = ( g/ l )*sin(x1)-( k/m)*x2 ;

% Normalize t h e Vector Lengths
[ unNL , vnNL ] = normalize ( uNL , vNL ) ;
[ unL , vnL ] = normalize ( uL , vL ) ;
[ unPen , vnPen ] = normalize ( uPen , vPen ) ;

%Create the Non−Linear ODE
xInit = 0.1;
yInit = -5.0;
[ xOdeNL , yOdeNL ] = ode45 (@ODENL, linspace(0 , 20 , 5000) , [xInit yInit]) ;
xOdeNL = yOdeNL(: , 1);
yOdeNL = yOdeNL(: , 2);

%Create the Linear ODE
xInit = -4;
yInit = 3.9;
[ xOdeL , yOdeL ] = ode45 (@ODEL , linspace(0 , 20 , 5000 ) , [ xInit yInit ] ) ;
xOdeL = yOdeL(: , 1);
yOdeL = yOdeL(: , 2);

%Create the Pendulum ODE
xInit = -2.9;
yInit = 0;
[ xOdePen , yOdePen ] = ode45 ( @ODEPen , linspace( 0 , 20 , 5000) , [xInit yInit]) ;
xOdePen = yOdePen(: , 1);
yOdePen = yOdePen(: , 2);

%Print the Non−Linear Plot
figure
hold on;
quiver(x1 , x2 , unNL , vnNL);
plot(xOdeNL , yOdeNL)
xlim([-xRange xRange])
ylim([-yRange yRange])
title('Non−Linear Plot')
hold off;

%Print the Linear Plot
figure
hold on;
quiver(x1 , x2 , unL , vnL);
plot(xOdeL , yOdeL)
xlim([-xRange xRange])
ylim([-yRange yRange])
title('Linear Plot')
hold off;

%Print the Pendulum Plot
figure
hold on;
quiver(x1 , x2 , unPen , vnPen);
plot(xOdePen , yOdePen)
xlim([-xRange xRange])
ylim([-yRange yRange])
title ('Pendulum Plot')
hold off;
function dydtNL = ODENL(t , x)
    dydtNL = [x(1) + x(1)*x(2); -x(2)+x(2)^2 + x(1)*x(2) +x(1)^3];
end

function dydtNL = ODEL(t , x)
    dydtNL = [x(1)+2*x(2); 3∗ x ( 1 ) + 2∗ x ( 2 ) ] ;
end
f u n c t i o n dydt NL = ODE Pen ( t , x )
g = − 9 . 8 1 ; % G r a v i t y Constant
l = 10;
% Pendulum S t r i n g Length
k = 0 . 5 0 ; % Damping C o e f f i c i e n t
m = 10;
% Pendulum Mass
dydt NL = [ x ( 2 ) ; ( g/ l ) ∗ s i n ( x ( 1 ) ) − ( k/m) ∗ x ( 2 ) ] ;
end
%Normalize t h e v e c t o r s i n t h e f i e l d by d i v i d i n g by t h e i r magnitude
f u n c t i o n [ un , vn ] = normalize ( u , v )
un = u . / s q r t ( u . ˆ 2 + v . ˆ 2 ) ;
vn = v . / s q r t ( u . ˆ 2 + v . ˆ 2 ) ;
end