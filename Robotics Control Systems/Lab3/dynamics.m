function [dx, ut, r] = dynamics(t,x,r)

    % Model of the aircraft system and Control gains %
    kp = 1; % Proportional control gain %
    kd = 1; % Dirivative control gain (recall this has ∆ t wrapped in) %
    ki = 1; % Integral control gain (recall this has ∆ t wrapped in) %
     % Desired pitch angle %
    e = r - x(3); % Pitch error %
    % Account for actuator saturation %
    u_limit = pi/4;

    % PID regulation - need to keep a running total of the error
    % as well as the old error for the derivative term %
    % ek is the total error accumulated, e_old is the previous error
    persistent ek e_old
    edot = ????;

    % First time through e_old will be empty because there's no
    % intitialization (need to account for that)
    if(isempty(e_old))
    u = ????
    else
    u = ????
    end

    % Check and limit actuators here %


    % Keep old values for control %
    e_old = e;
    ek = [ek;e];

    % Enter system dynamics here %
    dx = zeros(3,1);

    % Need this to get the control signal out later %
    if nargout>1
    ut = u;
end