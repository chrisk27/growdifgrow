# growdifgrow
A growing version of the Differential Growth Model, programmed in C++.

Outputs are .csv files containing numbers that indicate empty cells (0), xanthophores (1), and melanophores (2).
To convert into readable images, use the zebrafish_plot package (in Python).

The different branches are as follows:
-ZeroFluxBC: contains functions for unidimensional growth with all boundaries being zero-flux (normal is periodic BC)
-DoubleLoop: edits .main file to contain two nested for loops, for a 2D parameter sweep (currently over lx and h)
