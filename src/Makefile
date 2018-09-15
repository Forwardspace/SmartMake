#Note: this Makefile is intended to be read by computers, proceed at your own risk

smake: ./scanner/scanner.cpp ./main.cpp ./parser/parser.cpp ./generator/generator.cpp
	g++ $^ -o $@ -lstdc++fs
.PHONY: clean
clean:
	rm smake
