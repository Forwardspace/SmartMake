#pragma once
#include <fstream>
#include "../misc.hpp"

std::vector<std::string> splitBySpace(std::string s);
void missingValue(std::string name);

Options parseSmakeFile(std::ifstream& file);
