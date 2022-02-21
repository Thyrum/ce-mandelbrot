# Mandelbrot for TI CE calculator

![Mandelbrot screenshot](screenshot.png)

This application renders the mandelbrot set (in an acceptable time) on your TI
CE calculator.

## Building

In order to compile the mandelbrot set, please follow the steps at the
[CE Toolchain documentation](https://ce-programming.github.io/toolchain/static/getting-started.html)
"Getting Started" section in order to set up your CE development environment.
Then run `make` in the project root in order to compile the program.

## Developer notes

Note the program uses a custom fixed point integer implementation. This has been
done in order to optimize performance. The program can be switched to using
floats by changing
```cpp
using T = fp<int24_t, 9>;
```
to
```cpp
using T = float;
```
in `src/mandelbrot.cpp`. This results in a more detailed image at the cost of
vastly increased rendering times. The `9` fraction bits for the fixed point
numbers are chosen to reduce the amount of overflow errors (which are
automatically detected when making the debug build). As it is, a total of only 4
overflow errors is produced (probably causing 4 pixels to have the wrong color).
