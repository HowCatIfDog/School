clc
clear
close all

%  vector point multiplier *must be positive integer*
Ts = 4;

% x/y initial location to evaluate ode at
xode = -2;
yode = -2;

% range/domain of the plotting area
xrange = 10;
yrange = 10;

x = linspace(-xrange,xrange,xrange*2*Ts);
y = linspace(-yrange,yrange,yrange*2*Ts);
tspan = [-5*xrange, 5*xrange];
[x,y] = meshgrid(x,y);

% user defined system
% non-linear example from lab description
% u = x + x.*y;
% v = -y + y.^2 + x.*y + x.^3;

% linear example
u = x + 2*y;
v = 3*x + 2*y;

% pendulum example
% l = 5;
% g = -9.81;
% u = y;
% v = -(g/l)*sin(x);


% ode solver for the function
y0 = [xode yode];
[xode, yode] = ode45(@odefcn, tspan, y0);
xode = yode(:, 1);
yode = yode(:, 2);

% plotting stuff
% linearize vector lengths
un = u./sqrt(u.^2+v.^2);
vn = v./sqrt(u.^2+v.^2);
figure
hold on;
axis([-xrange xrange -yrange yrange]);
quiver(x,y,un,vn);
plot(xode, yode);
hold off;


function dydt = odefcn(t,x)
% linear example
    dydt = [x(2), -x(1)];

% non-linear example from lab description
%     dydt = [x(1)+x(1)*x(2); -x(2)+x(2)^2+x(1)*x(2)+x(1)^3];
    
% pendulum example
%     dydt = [];
end