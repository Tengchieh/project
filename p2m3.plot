#gnuplot command line

set terminal png
set output 'p2m3.png'
set title "Step size from 0.2 to 0.000001"
set xrange [0.000001:0.2]
set key below
set grid
set xlabel 'Step size'
set ylabel 'Error %'
set logscale xy
plot 'p2m3.dat' using 1:2 title "problem2 method3" with lines

set output 'p2m3_time.png'
set title "Step size from 0.2 to 0.000001"
set xrange [0.000001:0.2]
set key below
set grid
set xlabel 'Step size'
set ylabel 'time(s)'
set logscale xy
plot 'p2m3.dat' using 1:3 title "problem2 method3 Time" with lines
exit
