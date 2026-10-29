#ifndef GAME_H
#define GAME_H

#include <string>
#include "Constants.h"

// Game
// One game for sale: its name, the username of its seller and its price in
// cents. It also remembers whether it was put up for sale during the current
// session, because such a game can't be bought until a later session.
class Game
{
public:
    // Game
    // Makes an empty game (no name, no seller, 0 price) so that parseFileLine
    // has a game to fill in.
    Game();

    // Game
    // Makes a game with the given name, seller username and price in cents.
    // It starts out as not listed this session.
    Game(const std::string& name, const std::string& seller, Cents price);

    // parseFileLine
    // Reads one 48 character available games file line ("name seller price")
    // into game. Returns false, leaving game unchanged, if the line is the
    // wrong length, is missing a separating space, has a blank name or seller,
    // or a badly formatted price field.
    static bool parseFileLine(const std::string& line, Game& game);

    // getName
    // Returns the game name.
    std::string getName() const;

    // getSeller
    // Returns the seller's username.
    std::string getSeller() const;

    // getPrice
    // Returns the price in cents.
    Cents getPrice() const;

    // wasListedThisSession
    // True if the game was put up for sale during the current session.
    bool wasListedThisSession() const;

    // markListedThisSession
    // Marks the game as a new listing for the current session.
    void markListedThisSession();

private:
    // The game's name, with no trailing spaces.
    std::string name;

    // The username of the account selling the game, with no trailing spaces.
    std::string seller;

    // The game's price in cents.
    Cents price;

    // True if the game was put up for sale during the current session.
    bool listedThisSession;
};

#endif
