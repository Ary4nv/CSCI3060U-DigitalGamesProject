#include "RecordFile.h"
#include "Constants.h"
#include "FieldFormat.h"

#include <fstream>

// Opens the file and puts every line before the END line into lines.
// Returns FILE_CANNOT_OPEN if the file is missing and FILE_BAD_FORMAT if there is no END line.
FileLoadStatus RecordFile::readLines(const std::string& path, std::vector<std::string>& lines) {
    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        return FILE_CANNOT_OPEN;
    }

    lines.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        if (FieldFormat::trimRight(line) == Constants::END_MARKER) {
            return FILE_LOADED;
        }
        lines.push_back(line);
    }
    return FILE_BAD_FORMAT;
}
