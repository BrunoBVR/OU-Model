**Bruno V. Ribeiro - 2013**

Numeric simulation of results found [here](https://link.springer.com/article/10.1007/s10955-013-0835-4).

Run the executable compall to create two new executables: generate_paths.exe
 and AbsError_estimate.exe.

The first one creates a folder named "figs". In it, a .dat file is created with the name "D-'NumberOfVComponents'-10c1-'10*InitialV1'.dat"
containg four columns: time, our V_1 process, an OU process driven by the same noise as V_1, and the difference process v;
and a figure file with the same name showing the evolution of the three processes (V_1, OU and v) with extension .png or .eps .
The extension type, and all system settings can be changed in the file "data2.in".
Once the executables are generated, one may only change this file in order to get different results.


The second executable prints in terminal the Absolute Error (in the spirit of
Kloeden,Platen,Schurz), the number of velocity components (D) and a third number (ns)
corresponding to the amount of different paths generated in the Error estimate.

One crucial difference between this programs and the last one, is the dynamic allocation of memory
for all vectors and arrays involved. Particularly, I wrote a function "Make2dArray.c"
that does this allocation for two dimensional arrays. This allows us to run the program
with a larger number of particles (the last one had problems for 100 partciles, this one runs
for over 1000 particles in few minutes -- in a 32 bits machine).

OBS.: 	The generation of the figures demands installation of gnuplot on terminal.
		Execution demands gcc compiler.
		The ".gp" files are the scripts on gnuplot to generate the plots.
