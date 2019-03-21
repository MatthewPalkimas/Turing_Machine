~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MATTHEW PALKIMAS
TURING MACHINE EXECUTOR
:To run just compile TuringMachineExecutor.cpp and use the format
a.out tmFile input
or
a.out tmFile -f (input text file)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
You can make your own tmFiles if you would like to
attempt to solve a compuatable problem in a logical way.
The format:
State, Input, Next State, Output, Direction
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The first state is always going to be start
The last state has to include stop as the first four characters.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Example Turing Machine File (add_one.tm) 
This will add one to a binary number
Example: #100# will go to #101#
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
start, #, 1, #, R
1, 0, 1, 0, R
1, 1, 1, 1, R
1, #, 2, #, L
2, 1, 2, 0, L
2, 0, 3, 1, L
2, #, 4, 1, L
3, 0, 3, 0, L
3, 1, 3, 1, L
3, #, stop, #, -
4, ?, stop, #, -
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
