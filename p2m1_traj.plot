set terminal png
set output 'p2m1_traj.png'
#set dummy x,y
#set parametric
set view 45, 50, 1, 1
#set nokey; unset xtics; unset ytics; unset ztics
#set hidden3d offset 1 trianglepattern 3 undefined 1 altdiagonal bentover
set ticslevel 0
set title "Charged Particle Motion Method1"
set xrange[-10.0000 : 10.0000]
set yrange[-10.0000 : 10.0000]
set zrange[0.0000 : 10.0000] 
splot 'p2m1_traj.dat' using 2:3:4 with lines

exit
