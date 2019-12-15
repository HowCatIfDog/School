clc
clear
close all

%Define the Time Span
tSpan = 4;

%Define the X and Y Ranges
xRange = 7;
yRange = 7;

%Create the Range of X and Y Values
x1 = linspace(-xRange, xRange, xRange*2*tSpan);
x2 = linspace(-yRange, yRange, yRange*2*tSpan);
[x1,x2] = meshgrid(x1,x2);

%Define the Differential Equations
alpha = -2;
u_NL = x2 - x1.*(x1.^2 + x2.^2 - 5^2); %u
v_NL = -x1 - x2.*(x1.^2 + x2.^2 - 5^2); %v

% Normalize the Vector Lengths
[u_NL, v_NL] = normalize(u_NL, v_NL);

%Create the Non-Linear ODE
xInit = 6.0;
yInit = 6.0;
[xOde_NL,yOde_NL] = ode45(@ODE_NL,linspace(0,20,5000),[xInit yInit]);
xOde_NL = yOde_NL(:, 1);
yOde_NL = yOde_NL(:, 2);

%Print the Non-Linear Plot
figure
hold on;
quiver(x1,x2,u_NL,v_NL);
plot(xOde_NL, yOde_NL)
xlim([-xRange xRange])
ylim([-yRange yRange])
title('Phase Plane Plot with with convergence at 5')
hold off;

function dydt_NL = ODE_NL(t,x)
    dydt_NL = [x(2) - x(1)*(x(1)^2 + x(2)^2 - 5^2); -x(1) - x(2)*(x(1)^2 + x(2)^2 - 5^2)];
end 

%Normalize the vectors in the field by dividing by their magnitude
function [un, vn] = normalize(u, v)
    un = u./sqrt(u.^2 + v.^2);
    vn = v./sqrt(u.^2 + v.^2);
end