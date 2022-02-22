# Mandelbrot for TI CE calculator

![Mandelbrot screenshot](screenshot.png)

This application renders the mandelbrot set (in an acceptable time) on your TI
CE calculator.

## Installing & running

Download the `MBROT.8xp` of the [latest release](https://github.com/Thyrum/ce-mandelbrot/releases/latest)
from the github page. Transfer this file to your calculator using
[TI connect](https://education.ti.com/en/products/computer-software/ti-connect-sw)
or send it to your emulator. Then run the program by pressing the `prgm` button,
selecting the program `MBROT` and pressing `enter` twice (to select and run
`MBROT`).

Note the program will draw the mandelbrot set in about 90 seconds, after which
you can press any key to return to the home screen. The drawing can also be
aborted by pressing the `on` key.


## Building

In order to compile the mandelbrot set, please follow the steps at the
[CE Toolchain documentation](https://ce-programming.github.io/toolchain/static/getting-started.html)
"Getting Started" section in order to set up your CE development environment.
Then run `make` in the project root in order to compile the program. The program
can then be found in `bin/MBROT.8xp`.


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
more than doubled rendering times. The `9` fraction bits for the fixed point
numbers are chosen to reduce the amount of overflow errors (which are
automatically detected when making the debug build). As it is, a total of only 4
overflow errors is produced (probably causing 4 pixels to have the wrong color).
