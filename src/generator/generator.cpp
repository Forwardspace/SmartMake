#include "generator.hpp"

const char* makefilePreface = "#Note: this Makefile is intended to be read by computers, proceed at your own risk\n";
const char* defaultCompileBase = " $^ -o $@";
const char* phonyClean = ".PHONY: clean";
const char* cleanBase = "clean:\n\trm ";

//Generates a makefile, for example
//hworld: hello.cpp main.cpp
//  g++ $^ -o $@
//.PHONY: clean
//clean:
//  rm hworld
void generateMakefile(Options& opts, std::vector<fs::path> inputs, std::string rootDir) {
    std::ofstream makefile(fs::path(rootDir) / "Makefile");
    if (!makefile) {
        std::cerr << "Generation cancelled: cannot open Makefile for writing!" << std::endl;
        std::exit(-1);
    }

    //the very useful preface
    makefile << makefilePreface << "\n";
    
    //<projectname>: input1 input2 inputN
    makefile << opts.projectName << ":";
    for (auto& fname : inputs) {
        makefile << " " << fname.string();
    }
    makefile << "\n";

    //  <compiler> $^ -o $@ -llib1 -llib2 -llibN
    //TODO: more options
    bool compileWithDefaultBase = true;
    if (compileWithDefaultBase) {
        makefile << "\t" << opts.compiler << defaultCompileBase;
    }
    for (std::string lib : opts.libraries) {
        makefile << " -l" << lib;
    }
    makefile << "\n";

    //.PHONY: clean
    //clean:
    //  rm <projectname>
    makefile << phonyClean << "\n";
    makefile << cleanBase << opts.projectName << "\n";
}