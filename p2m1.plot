set terminal png
set output 'p2m1.png'
set title "Step size from 0.2 to 0.000001"
set xrange [0.000001:0.2]
set key below
set grid
set xlabel 'Step size'
set ylabel 'Error %'
set logscale xy
plot 'p2m1.dat' using 1:2 title "problem2 method1" with lines

exit
