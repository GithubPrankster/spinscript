CC = gcc
CPPC = g++
C_OPTS = -Ofast -march=bdver2
CPP_OPTS = -std=c++17

ttsvm:
	$(CC) $(CPP_OPTS) $(C_OPTS) ttsvm.cpp -o ttsvm

parasc:
	$(CPPC) $(CPP_OPTS) $(C_OPTS) parasc.cpp -o parasc

.PHONY: clean
clean:
	rm -rf parasc
	rm -rf ttsvm