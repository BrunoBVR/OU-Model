set t push																# save the current terminal settings
set t png
set style data linespoints
set o "./figs/$0.png"													# set the output filename to the first option
set xlabel "t"
set ylabel ""
set grid
set ytic 0.4
set xtic 0.2
set key outside
set title "D = $2, c1 = $3"
plot "$1" u 1:2 ps 0.05 title "{V}_{1}", "$1" u 1:3 ps 0.05 title "OU", "$1" u 1:4 ps 0.05 title "v" 			# plot command
set o																	# restore output to interactive mode
set t pop																# restore the terminal
