#include <fstream>

#include "misc.hpp"
#include "scanner/scanner.hpp"
#include "generator/generator.hpp"

Options parseSmakeFile(std::ifstream& file);

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

std::vector<std::string> splitBySpace(std::string s) {
	std::vector<std::string> result;
	std::string nextToken;

	for (char c : s) {
		if (c != ' ') {
			nextToken += c;
		}
		else {
			result.push_back(nextToken);
			nextToken = "";
		}
	}

	if (nextToken != "") {
		result.push_back(nextToken);
	}

	return result;
}

void missingValue(std::string name) {
	std::cerr << name << " - Missing value. Generation cancelled." << std::endl;
	std::exit(-1);
}

Options parseSmakeFile(std::ifstream& file) {
	Options opts;
	
	std::string line;
	while (std::getline(file, line)) {
		if (line == "") {
			continue;
		}

		std::vector<std::string> tokens = splitBySpace(line);
		for (int i = 0; i < tokens.size(); i++) {
			//Project modifier - Usage: Project <name> 
			if (tokens[i] == "Project") {
				if (tokens.size() > i) {
					opts.projectName = tokens[i + 1];
					break;
				}
				else {
					missingValue("Project modifier");
				}
			}
			else if (tokens[i] == "Link") {
				if (tokens.size() > i) {
					opts.libraries.push_back(tokens[i + 1]);
					break;
				}
				else {
					missingValue("Link modifier");
				}
			}
			else if (tokens[i] == "Build.") {
				//We're done here - return opts.
				return opts;
			}
			else {
				std::cerr << "Invalid modifier: " << tokens[i] << std::endl;
				std::exit(-1);
			}
		}
	}

	std::cerr << "Generation cancelled. (You probably forgot the 'Build.' modifier.)" << std::endl;
	std::exit(-1);
}
