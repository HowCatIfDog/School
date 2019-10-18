clc
clear
close all
% Simulate the autopilot %
% options = odeset('RelTol',1e-4,'AbsTol',[1e-5 1e-5 ]);
discretePoints = 50;
% tspan = linspace(0,20,discretePoints);

numberOfRobots = 4;


% Problem 1: universal vision, predefined endpoint
position = randi(40, numberOfRobots, 2) - 20;
rgb = zeros(numberOfRobots, 3);
%rgb = randi(255, numberOfRobots, 3);
% desired point
desired = zeros(numberOfRobots, 2)+5;

kp1 = 0.09;


figure;
hold on;

for i = 0:discretePoints
    % extract x,y vectors
    xpos = position(:,1);
    ypos = position(:,2);
    
    % plot it
    scatter(xpos, ypos, 20, rgb, 'filled');
    xlabel('X axis','fontsize',16,'interpreter','latex')
    ylabel('Y axis',...
    'fontsize',16,'interpreter','latex')

    % update position using proportional control
    error = desired-position;
    position = position + kp1*error;
end
hold off;



%Problem 2: limited vision, changing endpoint
position2 = randi(40, numberOfRobots, 2) - 20;

range = 5;
kp2 = 0.1;

figure;
hold on;

for i = 0:discretePoints
    desired2 = zeros(numberOfRobots, 2);
    xpos = position2(:,1);
    ypos = position2(:,2);
    
    scatter(xpos, ypos, 20, rgb, 'filled');
    xlabel('X axis','fontsize',16,'interpreter','latex')
    ylabel('Y axis',...
    'fontsize',16,'interpreter','latex')
    % update position
    for j = 1:numberOfRobots
        a = 0;
        x1 = position2(j, 1);
        y1 = position2(j, 2);
        
        for k = 1:numberOfRobots
            if(j ~= k)
                              
                x2 = position2(k,1);
                y2 = position2(k, 2);
                
                if(range > sqrt((x1-x2)^2 + (y1-y2)^2))
                    a = a+1;
                    desired2(j, 1) = desired2(j, 1) + x2;
                    desired2(j, 2) = desired2(j, 2) + y2;
                end
            end
        end
        
        if( a == 0)
            desired2(j, 1) = position2(j, 1);
            desired2(j, 2) = position2(j, 2);
        else
            desired2(j, 1) = desired2(j, 1)/a;
            desired2(j, 2) = desired2(j, 2)/a;
        end
        
    end
    
    error2 = desired2 - position2;
    position2 = position2 + kp2*error2;
    
end
hold off;

% Problem 3: universal vision, predefined endpoint
position = randi(40, numberOfRobots, 2) - 20;
rgb = zeros(numberOfRobots, 3);
% desired point
desired31 = [ 0 0;
              0 -5;
              -5 -5;
              5 -5];
desired32 = [0 5;
             5 0;
             -5 0;
             0 -5];

kp3 = 0.09;


figure;
hold on;

for i = 0:discretePoints
    % extract x,y vectors
    xpos = position(:,1);
    ypos = position(:,2);
    
    % plot it
    scatter(xpos, ypos, 20, rgb, 'filled');
    xlabel('X axis','fontsize',16,'interpreter','latex')
    ylabel('Y axis',...
    'fontsize',16,'interpreter','latex')

    % update position using proportional control
    error = desired31-position;
    position = position + kp3*error;
end


for i = 0:discretePoints
    % extract x,y vectors
    xpos = position(:,1);
    ypos = position(:,2);
    
    % plot it
    scatter(xpos, ypos, 20, rgb, 'filled');
    xlabel('X axis','fontsize',16,'interpreter','latex')
    ylabel('Y axis',...
    'fontsize',16,'interpreter','latex')

    % update position using proportional control
    error = desired32-position;
    position = position + kp3*error;
end

for i = 0:discretePoints
    % extract x,y vectors
    xpos = position(:,1);
    ypos = position(:,2);
    
    % plot it
    scatter(xpos, ypos, 20, rgb, 'filled');
    xlabel('X axis','fontsize',16,'interpreter','latex')
    ylabel('Y axis',...
    'fontsize',16,'interpreter','latex')

    % update position using proportional control
    error = desired31-position;
    position = position + kp3*error;
end

hold off;