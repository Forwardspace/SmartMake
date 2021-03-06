#include "parser.hpp"

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
