# Physics Based Animation 
<!--
used to make the gif from videos 
https://ezgif.com/video-to-gif
-->
### Single particle ODE (ordinary differential equation)

<!-- 
drag to move the ball , speed based on length of clicks 
press control and left click 
press option and left click 
-->
Animated the behaviour of 3D sphere as a particle on a plane. Its motion is restricted within a square on the plane. Mouse based interaction used to apply force on the particle. The direction and magnitude are based on the press and release location of the left mouse button.

The arrow visualizes the direction of the particle. The colour range is blue to red based on the velocity of the particle. 

<!-- ![ezgif com-video-to-gif](https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/2b8efc16-f3bf-4d61-bccd-0432dc00d617.gif) -->
<img src="https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/2b8efc16-f3bf-4d61-bccd-0432dc00d617.gif" width="400">


The spiral trajectory is the result of a particle under a concentric force field i.e. the acceleration is always along the tangent direction of a circile whose center is at (0, 0), near the starting position of the particle.  

The magnittude of the force here is linearly proportional to the radius of the circle (i.e., the distance of the particle to the origin). Used explicit Euler and implicit Euler with different time step sizes to simulate the trajectory of the particle for the concentric acceleration.

The arrow visualizes the direction of the acting on the particle. The colour range is blue to red based on the force acting on the particle. 
<!-- ![pba1_spiral](https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/815226e4-5261-45de-84a9-a571303112e0) -->
<img src="https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/815226e4-5261-45de-84a9-a571303112e0.gif" width="400">


### Rigid body simulation

<!-- 
drag to move the ball , speed based on length of clicks 
press control and left click 
press option and left click 
-->
Rigid body simulation
<!-- ![pba2](https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/b61c509e-d83f-40cf-91aa-953cef436fcc) -->
<img src="https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/b61c509e-d83f-40cf-91aa-953cef436fcc.gif" width="700">


## Spring mass system

<!-- 
drag to move the ball , speed based on length of clicks 
press control and left click 
press option and left click 
-->
Spring mass free fall 

Mouse interaction 
<!-- ![pba3_freefall_mouseforce](https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/67abcb10-7a43-47d0-bbd4-c1679da9843f) -->
<img src="https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/67abcb10-7a43-47d0-bbd4-c1679da9843f.gif" width="700">

Fixed node
<!-- ![pba3_fixednode](https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/201bcd78-005d-488c-ba73-48461d46b109) -->
<img src="https://github.com/nishita96/PhysicsBasedAnimation/assets/24264347/201bcd78-005d-488c-ba73-48461d46b109.gif" width="700">

