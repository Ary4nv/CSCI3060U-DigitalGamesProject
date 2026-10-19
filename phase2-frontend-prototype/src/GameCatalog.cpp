#include "GameCatalog.h"

// Replaces the games in memory with the ones in the available games file.
// Returns what went wrong if the file can't be opened or has a bad line.
FileLoadStatus GameCatalog::loadFromFile(const std::string& path) {
    std::vector<std::string> lines;
    FileLoadStatus status = RecordFile::readLines(path, lines);
    if (status != FILE_LOADED) {
        return status;
    }

    std::vector<Game> loadedGames;
    for (std::size_t i = 0; i < lines.size(); i++) {
        Game game;
        if (!Game::parseFileLine(lines[i], game)) {
            return FILE_BAD_FORMAT;
        }
        loadedGames.push_back(game);
    }

    games = loadedGames;
    return FILE_LOADED;
}

// Returns the game with this exact name or NULL if no game has it.
// Names are unique across all sellers so there is at most one.
Game* GameCatalog::findByName(const std::string& name) {
    for (std::size_t i = 0; i < games.size(); i++) {
        if (games[i].getName() == name) {
            return &games[i];
        }
    }
    return NULL;
}

// Adds a game to the end of the list.
void GameCatalog::add(const Game& game) {
    games.push_back(game);
}

// Returns every game, in the order they were loaded or listed.
const std::vector<Game>& GameCatalog::getAll() const {
    return games;
}
