classdef Flock
    %FLOCK Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        boids
        lattice_size
        step_counter=1;
    end
    
    methods
        
%       Constructor function
        function obj = Flock(boids,lattice_size)
            obj.boids=boids;
            obj.lattice_size=lattice_size;
        end
        
%       main program loop
        function run(obj)
            curve = animatedline('Marker','o','LineStyle','none');
            set(gca, 'Xlim', [0, obj.lattice_size(1)], 'Ylim', [0, obj.lattice_size(2)]);
            
            while true

%               Find force vector
                for i=1:length(obj.boids)
                    obj.boids(i)=obj.boids(i).flock(obj.boids);
                end

%               Update position from force vector
                for i=1:length(obj.boids)
                    obj.boids(i)=obj.boids(i).update();
                end
                
%               Loop boids arround plane if they go off the edge
                for i=1:length(obj.boids)
                    obj.boids(i) = obj.boids(i).borders(obj.lattice_size);
                end
                
%               Render new frame
                delete(gca);
                set(gca, 'Xlim', [0, obj.lattice_size(1)], 'Ylim', [0, obj.lattice_size(2)]);
                [obj] = render(obj);
                
%                 for video writer
%                 F = getframe(gca);
%                 if(obj.step_counter > 20)
%                     break;
%                 end
            end
            
%             for video writer
%             video = VideoWriter('boids_flocking.avi');
%             open(video);
%             writeVideo(video, F);
%             close(video)
        end
        
%       Display frame to the plot
        function [obj] = render(obj)
            obj.step_counter=obj.step_counter+1;
%             fprintf('Rendering %s \n',num2str(obj.step_counter))

            
            hold on;
            for i=1:length(obj.boids)
                x = obj.boids(i).position(1);
                y = obj.boids(i).position(2);
                xvel = obj.boids(i).velocity(1);
                yvel = obj.boids(i).velocity(2);
                quiver(x,y, xvel,yvel, 'linewidth', 7, 'color', [0,0,0]);
            end
            hold off;
            drawnow;

        end

    end
    
end

