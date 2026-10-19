#ifndef GAMECATALOG_H
#define GAMECATALOG_H

#include <string>
#include <vector>
#include "Game.h"
#include "RecordFile.h"

// All the games for sale during a session. It loads them from the available
// games file and lets transactions look up games and add new listings.
class GameCatalog {
public:
    // Replaces the games in memory with the ones in the available games file.
    // Returns what went wrong if the file can't be opened or has a bad line.
    FileLoadStatus loadFromFile(const std::string& path);
    // Returns the game with this exact name or NULL if no game has it.
    // Names are unique across all sellers so there is at most one.
    Game* findByName(const std::string& name);
    // Adds a game to the end of the list.
    void add(const Game& game);
    // Returns every game, in the order they were loaded or listed.
    const std::vector<Game>& getAll() const;

private:
    std::vector<Game> games;
};

#endif
