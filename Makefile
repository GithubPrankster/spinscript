GXX = gcc
GXX_OPTS = -s -Ofast -m64

all:
	$(GXX) $(GXX_OPTS) machina.c -o machina.exe