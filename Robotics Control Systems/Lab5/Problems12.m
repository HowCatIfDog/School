
% Part 1 with complete linearized model
n = 7;
A = [0 0 1 0 0 0 0; 0 0 0 0 0 0 0; 0 0 0 0 0 2.16 0; 0 0 0 0 1 0 0; 0 0 0 0 0 0 0; 0 0 0 0 0 0 1; 0 0 0 0 0 72.49 0];
B = [0 0; 0 0; -1.67 1.67; 0 0; 0.029 -0.029; 0 0; -24.15 -24.15];
C = ctrb(A, B);
rc = rank(C);
n-rc

% part 2 with simplified model
n2 = 4;
A2 = [0 0 2.16 0; 0 0 0 0; 0 0 0 1; 0 0 72.49 0];
B2 = [-1.67 1.67; 0.029 -0.029; 0 0; -24.15 -24.15];
C2 = ctrb(A2, B2);
rc2 = rank(C2);
n2-rc2

% if one of the answers is non-zero that means that n =/= rank so it isn't
% controlable

% part 3

% part 4
f = 1; % This is period not frequency
r = 5;
circ = pi*2*r;
vel = circ/f;
rads = (2*pi)/f;


function dydt = odefcn(t,x)
% linear example
    dydt = [x(1)+2*x(2), 3*x(1)+2*x(2)];
end

