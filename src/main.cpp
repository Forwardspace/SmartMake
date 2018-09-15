#include <fstream>

#include "misc.hpp"
#include "scanner/scanner.hpp"
#include "generator/generator.hpp"
#include "parser/parser.hpp"

//By default it's the directory in which the program is invoked
std::string rootDir = ".";

const std::string smakeFilename = "SMakeFile";

int main(int argc, char** argv) {
	//An optional root directory argument can be given, check for it
	if (argc > 2) {
		std::cerr << "Invalid number of arguments: SmartMake takes just an optional\n";
		std::cerr << "alternate root directory argument" << std::endl;
		std::exit(-1);	
	}
	else if (argc == 2) {
		rootDir = argv[1];
	}

	//This is the main options file for SmartMake
	std::ifstream smakeFile("" + smakeFilename);

	if (!smakeFile) {
		std::cerr << "Unable to open " << smakeFilename << "!";
	}

	Options opts = parseSmakeFile(smakeFile);
	std::vector<fs::path> inputFiles = scanForInputFiles(rootDir, opts);
	generateMakefile(opts, inputFiles, rootDir);

	std::cout << "Success! Run make to compile " << opts.projectName << "!\n";
}
