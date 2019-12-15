% simple boids simulation
boids_count=20;
Xwindow = 640/3;
Ywindow = 360/3;

boids=Boid.empty;
for i=1:boids_count
   boids(i)=Boid(rand*Xwindow,rand*Ywindow);
end



flock=Flock(boids,[Xwindow Ywindow]);
f = figure;
flock.run();

