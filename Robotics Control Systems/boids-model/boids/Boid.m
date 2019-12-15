classdef Boid
    
    properties
        position
        velocity
        acceleration
        r
        max_force
        max_speed
    end
    
    methods
        
%       Constructor function
        function obj = Boid(position_x,  position_y)
            obj.acceleration = [0 0];
            
            angle = (2*pi).*rand;
            obj.velocity = [cos(angle), sin(angle)];
            
            obj.position = [position_x, position_y];
            obj.r = 0;
            obj.max_speed = 4;
            obj.max_force = 0.1;
        end        
        
%       find the force vectors and scale them with proportional gain
        function obj = flock(obj,boids)
            sep = obj.seperate(boids);
            ali = obj.align(boids);
            coh = obj.cohesion(boids);
            
            
%           proportional gain
     
            sep = sep.*15;
            ali = ali.*1.0;
            coh = coh.*1.0;
            
            obj.acceleration = obj.acceleration+sep+coh+ali;
        end
        
%       for checking if the boid goes off the edge
        function obj = borders(obj, lattice_size)
            if obj.position(1) < -obj.r
                obj.position(1)=lattice_size(1)+obj.r;
            end
            
            if obj.position(2) < -obj.r
                obj.position(2)=lattice_size(2)+obj.r;
            end
            
            if obj.position(1) > lattice_size(1) + obj.r
                obj.position(1)=-obj.r;
            end
            
            if obj.position(2) > lattice_size(2) + obj.r
                obj.position(2)=-obj.r;
            end
        end
        
%       updates the velocity and position
        function obj = update(obj)
            obj.velocity = obj.velocity + obj.acceleration;
            obj.velocity = obj.velocity./norm(obj.velocity).*obj.max_speed;
            obj.position = obj.position + obj.velocity;
            obj.acceleration = [0 0];
        end
        


        
        function [steer] = seperate(obj, boids)
            desired_separation = 100.0;
            steer = [0,0];
            count = 0;
            positions = zeros(2,length(boids));
            
%             get positions of all boids in flock
            for i=1:1:length(boids)
                positions(:,i) = boids(i).position;
            end
%             get distance between self and every boid in flock
            d = pdist([obj.position; positions']);
            d = d(1:length(boids));
            
            
            for i=1:1:length(boids)
%                 check if each boid is close enough to see and if it is
%                 add it to the steer vector
                if d(i) > 0 && d(i) <  desired_separation
                    difference = obj.position - boids(i).position;
                    difference = difference./norm(difference);
                    difference = difference./d(i);
                    steer = steer + difference;
                    count = count+1;
                end
                
                if count > 0
                    steer = steer./count;
                end
                
%                 scale the steer force so that it can't go faster than max
%                 speed
                if norm(steer) > 0
                    steer = steer./norm(steer).*obj.max_speed;
                    steer = steer - obj.velocity;
                    steer = steer./norm(steer).*obj.max_force;
                end
            end
        end
        
        function steer = align(obj, boids)
            neighbor_dist = 50;
            sum = [0 0];
            count = 0;
            steer = [0 0];
            
%           get positions of all boids in flock
            positions = zeros(2,length(boids));
            for i=1:1:length(boids)
                positions(:,i) = boids(i).position;
            end
%           find distance to all of the boids
            d = pdist([obj.position; positions']);
            d = d(1:length(boids));
            
%           if they are close enough to see add it to the sum
            for i=1:1:length(boids)
                if d(i)>0 && d(i) < neighbor_dist
                    sum=sum+boids(i).position;
                    count=count+1;
                end
            end
            
%             scale steer force so the boid so that it can't go faster than
%             max speed
            if count > 0
                sum=sum./count;
                sum=sum./norm(sum).*obj.max_speed;
                steer=sum-obj.velocity;
                steer=steer./norm(steer).*obj.max_force;
            end
        end
        
        function steer = cohesion(obj, boids)
            neighbor_dist = 50;
            sum = [0 0];
            count = 0;
            steer = [0 0];
            
%           make list of the flock
            positions = zeros(2,length(boids));
            for i=1:1:length(boids)
                positions(:,i) = boids(i).position;
            end
%           find the distance to each boid
            d = pdist([obj.position; positions']);
            d = d(1:length(boids));
            
%           if the boid is close enough to see add it to the sum
            for i=1:1:length(boids)
                if d(i)>0 && d(i) < neighbor_dist
                    sum=sum+boids(i).position;
                    count=count+1;
                end
            end
            
            if count > 0
                sum=sum./count;
                steer = obj.seek(sum);
            end
        end
        
%         helper function for cohesion
        function [steer] = seek(obj, target)
            desired = target - obj.position;
            desired = norm(desired);
            desired = desired*obj.max_speed;
            
            steer = desired-obj.velocity;
            steer = steer./norm(steer).*obj.max_force;
        end
    end
end
