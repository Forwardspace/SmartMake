#pragma once
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

struct Options {
	std::string projectName = "Project";
	fs::path projectDir = "src";
	std::vector<std::string> srcExts = {".cpp"};
	std::string compiler = "g++";
	std::vector<std::string> libraries;
};
