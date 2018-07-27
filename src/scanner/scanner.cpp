#include "scanner.hpp"

std::vector<fs::path> scanForInputFiles(fs::path rootDir, Options& opts) {
    std::vector<fs::path> inputFiles;

	for (auto& item : fs::directory_iterator(rootDir)) {
        if (fs::is_directory(item)) {
            //Recursively scan all files
            std::vector<fs::path> paths = scanForInputFiles(item.path(), opts);
            inputFiles.insert(inputFiles.end(), paths.begin(), paths.end());
        }
        else {
            for (std::string& s : opts.srcExts) {
                if (item.path().extension() == s) {
                    //We've got a match; add it to the list of input files
                    inputFiles.push_back(item.path());
                }
            }
        }
    }

    return inputFiles;
}
