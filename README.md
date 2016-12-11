Created by Teng-Chieh Huang for Tools and Techniques Computational Science final project.

To source the third party library, please type 	
	
	source setup.bash

Then type 
	
	make

to compile all the cpp files. Then type
 
	./run

to run the ODE solver.


All the slection can be made in input.txt. There are two different questions, simple ODE and charged particle motion. Different methods can be chosen.
Step size (h) is changeable. Debug mode and verification mode are also provided.

To plot the graph, type

	gnuplot pxmy.plot

where x is # of problem and y is # of method.

To plot the trajectory graph, type

	gnuplot pxmy_traj.plot

where x is # of problem and y is # of method.
 
