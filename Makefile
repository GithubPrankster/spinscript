CC = gcc
CPPC = g++
C_OPTS = -s -Ofast -m64
CPP_OPTS = -std=c++2a

ttsvm:
	$(CC) $(C_OPTS) ttsvm.c -o ttsvm

parasc:
	$(CPPC) $(CPP_OPTS) $(C_OPTS) parasc.cpp -o parasc

.PHONY: clean
clean:
	rm -rf parasc
	rm -rf ttsvm