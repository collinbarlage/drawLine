# drawLine 🔥
CS430 A3
Collin Barlage  
11/8/2017

## Features

In this program, a user can input a .ps file with the *-f* flag as an argument. This program will then parse this file of points, connect them as polgon lines, then fill the shape and write an image to a .xpm file.  

## Languages

Languages used to implement this program include C++, .ps, and .xpm.  

This program is designed to run on the UNIX environment *TUX*.

## Compiler

This program compiles with g++

## Main()

The `main()` method for this program can be found in `drawLine.cpp`.

## How to run

To run drawLine in TUX, simply exicute `make` in the program's root directory. Then, exicute the program by typing `./drawLine INSERT ARGUMENTS HERE`.  
For example:  
```
> make
> ./drawLine -f hw1_8.ps -x
```

🔥🔥🔥