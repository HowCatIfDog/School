% simple boids simulation
boids_count=25;
Xwindow = 640/2;
Ywindow = 360/2;
boids=Boid.empty;
for i=1:boids_count
   boids(i)=Boid(rand*Xwindow,rand*Ywindow);
end



flock=Flock(boids,[Xwindow Ywindow]);
f = figure;
flock.run();

