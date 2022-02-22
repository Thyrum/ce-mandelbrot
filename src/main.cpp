#include <tice.h>
#include <graphx.h>

#include <cstring>

#include "mandelbrot.h"
#include "types.h"

//const uint8_t COLORS[] = {0,1,2,3,4,5,6,7,39,71,103,135,167,199,231,255};
//const uint8_t COLORS[] = {0,8,16,24,25,26,27,28,29,30,31,63,95,127,159,191,223};
const uint8_t COLORS[] = {0,16,25,26,27,28,29,30,31,63,95,127,159,191,223};
const uint8_t NUM_COLORS = sizeof(COLORS)/sizeof(uint8_t);
const uint8_t MAX_ITERATIONS = NUM_COLORS-1;


void drawPixel(int24_t x, int24_t y, uint8_t iterations) {
	uint8_t color = COLORS[MAX_ITERATIONS-iterations];
	gfx_SetColor(color);
	gfx_SetPixel(x, y);
}

int main(void) {
	gfx_Begin();
	gfx_SetDrawScreen();

	// Clear the screen
	gfx_FillScreen(255);

	timer_Disable(1);
	timer_Set(1,0);
	timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_UP);

	if (MandelBrot::calculate( LCD_WIDTH, LCD_HEIGHT, MAX_ITERATIONS, drawPixel)) {
		// Calculate and print the elapsed time
		float elapsed = (float)timer_GetSafe(1, TIMER_UP) / 32768;
		real_t elapsed_real;

		// Max stopwatch value is (2^32 - 1) / 32768 = 131072.00,
		// so create a buffer with room for 9 characters for elapsed time plus
		// another 5 characters for the ` sec` affix and null terminator
		char str[14];

		// If the elapsed time is small enough that the OS would print it using
		// scientific notation, force it down to zero before conversion
		elapsed_real = os_FloatToReal(elapsed <= 0.001f ? 0.0f : elapsed);

		os_RealToStr(str, &elapsed_real, 8, 1, 2);
		strcat(str, " sec");

		gfx_PrintStringXY(str, 5, 5);
		while (!os_GetCSC());
	}

	gfx_End();

	return 0;
}
