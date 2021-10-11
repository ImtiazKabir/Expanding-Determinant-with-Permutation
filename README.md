# Expanding determinant with permutation (NO RECURSION)
*This README is a work in progress, right now it does not contain the algorithm. But feel free to contact me and have a look at the source code (it is fairly simple)*

The `det.c` contains necessary source code, and the driver code is in `main.c`.

To use the program,
1. Compile the project with `make` (or just follow the recipe mentioned in the `Makefile`)
2. Change the content of `matrix.txt` according to your need (As it stands for now, any dimension should be okay), *the entries are parsed in float*
3. run the output with the address of the text file. (eg. `main matrix.txt`)

*This project uses [the vector implementation of stb](http://nothings.org/stb_ds/)*