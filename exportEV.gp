set t push																# save the current terminal settings
set t png																# change terminal to PNG, taking additional options from second argument
set style data point
set o "./evol/$0.png"													# set the output filename to the first option
set xlabel "t"
set ylabel ""
set grid
plot "$1" u 1:2 title "V_1", "$1" u 1:3 title "OU", "$1" u 1:4 title "v" 			# plot command
set o																	# restore output to interactive mode
set t pop																# restore the terminal
