#Note: this Makefile is intended to be read by computers, proceed at your own risk
projectName: input1 input2 input3 inputN
	opts.compiler $^ -o $@
clean:

