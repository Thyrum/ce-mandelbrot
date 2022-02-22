#include "mandelbrot.h"
#include "types.h"
#include "fixed-point.h"

#include <tice.h>
#include <keypadc.h>
#include <graphx.h>

namespace MandelBrot {

//using T = float;
using T = fp<int24_t, 9>;


cplx<T> xyToCoord(int24_t x, int24_t y) {
	static double minX = -2.0;
	static double maxX = 1.0;
	static double scaler = (maxX-minX)/(double)LCD_WIDTH;

	T real = static_cast<T>((double)(x) * scaler + minX);
	T imag = static_cast<T>((double)(LCD_HEIGHT/2.0-y) * scaler);

	return cplx<T>(real, imag);
}

uint8_t calculateCoord(const cplx<T>& coord, uint8_t maxIterations) {
	cplx<T> c(0.0, 0.0);
	for (uint8_t i = 0; i < maxIterations; ++i) {
		c = c*c + coord;
		if (c.real * c.real + c.imag * c.imag > static_cast<T>(4.0)) {
			return i;
		}
	}
	return maxIterations;
}

bool calculate(
	int24_t width,
	int24_t height,
	const uint8_t* colors,
	uint8_t numColors
) {
	kb_EnableOnLatch();
	kb_ClearOnLatch();

	const uint8_t maxIterations = numColors-1;

	for (int24_t x = 0; x < width; ++x) {
		for (int24_t y = height/2; y >= 0; --y) {
			const cplx<T> coord = xyToCoord(x, y);
			const uint8_t iterations = calculateCoord(coord, maxIterations);

			gfx_vbuffer[y][x] = colors[maxIterations-iterations];
			gfx_vbuffer[height-y][x] = colors[maxIterations-iterations];
		}

		if (kb_On) {
			kb_ClearOnLatch();
			kb_DisableOnLatch();
			return false;
		}
	}
	return true;
}

}
