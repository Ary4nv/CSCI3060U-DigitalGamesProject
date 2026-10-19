#ifndef RECORDFILE_H
#define RECORDFILE_H

#include <string>
#include <vector>

// Result of trying to load one of the input files.
enum FileLoadStatus {
    FILE_LOADED,
    FILE_CANNOT_OPEN,
    FILE_BAD_FORMAT
};

// Reads the lines of a fixed width input file (accounts or games) up to the
// END line. It only deals with the file itself. AccountRegistry and GameCatalog
// then check each line with Account::parseFileLine and Game::parseFileLine.
class RecordFile {
public:
    // Opens the file and puts every line before the END line into lines.
    // Returns FILE_CANNOT_OPEN if the file is missing and FILE_BAD_FORMAT if there is no END line.
    static FileLoadStatus readLines(const std::string& path, std::vector<std::string>& lines);
};

#endif
