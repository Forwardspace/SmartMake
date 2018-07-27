#pragma once
#include "../misc.hpp"
#include <fstream>

void generateMakefile(Options& opts, std::vector<fs::path> inputs, std::string rootDir);