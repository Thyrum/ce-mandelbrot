#pragma once

#include <tice.h>

namespace MandelBrot {

bool calculate(int24_t width, int24_t height, uint8_t maxIterations, void(*draw)(int24_t,int24_t,uint8_t));

}

