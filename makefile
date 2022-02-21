# ----------------------------
# Makefile Options
# ----------------------------

NAME = MBROT
ICON = icon.png
DESCRIPTION = "Mandelbrot set renderer"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Ofast -Iinclude
CXXFLAGS = -Wall -Wextra -Ofast -Iinclude

# ----------------------------

include $(shell cedev-config --makefile)
