#Note: this Makefile is intended to be read by computers, proceed at your own risk

smake: ./generator/generator.cpp ./scanner/scanner.cpp ./main.cpp
	g++ $^ -o $@ -lstdc++fs
.PHONY: clean
clean:
	rm smake
