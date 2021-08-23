set t push																# save the current terminal settings
set t postscript eps size 3.5,2.62 enhanced color font 'Helvetica,20' linewidth 2
set style data linespoints
set o "./figs/$0.eps"													# set the output filename to the first option
set xlabel "t"
set ylabel ""
set grid
set ytic 0.4
set xtic 0.4
set key outside
set title "D = $2, c1 = $3"
plot [0:1][] "$1" u 1:2 pt 7 ps 0.1 lc rgb "black" title "{V}_{1}", "$1" u 1:3 pt 7 ps 0.1 lc rgb "red" title "OU", "$1" u 1:4 pt 7 ps 0.1 lc rgb "green" title "v"
set o																	# restore output to interactive mode
set t pop																# restore the terminal
