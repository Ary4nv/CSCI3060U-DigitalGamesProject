#include "Game.h"

#include "FieldFormat.h"

// Where each field starts in an available games file line:
// name (25), space, seller (15), space, price (6).
static const int SELLER_START = Constants::MAX_GAME_NAME_LENGTH + 1;
static const int PRICE_START = SELLER_START + Constants::MAX_USERNAME_LENGTH + 1;

// Game
// Makes an empty game for parseFileLine to fill in.
Game::Game()
    : name(""), seller(""), price(0), listedThisSession(false)
{
}

// Game
// Makes a game with these values. It starts as not listed this session.
Game::Game(const std::string& name, const std::string& seller, Cents price)
    : name(name), seller(seller), price(price), listedThisSession(false)
{
}

// parseFileLine
// Splits a 48 character line into its three fields and checks each one.
bool Game::parseFileLine(const std::string& line, Game& game)
{
    if (static_cast<int>(line.size()) != Constants::GAME_LINE_LENGTH)
    {
        return false;
    }

    bool separatorsArePresent = line[SELLER_START - 1] == Constants::FIELD_SEPARATOR
                                && line[PRICE_START - 1] == Constants::FIELD_SEPARATOR;
    if (!separatorsArePresent)
    {
        return false;
    }

    std::string name = FieldFormat::trimRight(line.substr(0, Constants::MAX_GAME_NAME_LENGTH));
    std::string seller = FieldFormat::trimRight(line.substr(SELLER_START, Constants::MAX_USERNAME_LENGTH));
    std::string priceField = line.substr(PRICE_START, Constants::PRICE_FIELD_WIDTH);

    Cents price = 0;
    bool fieldsAreValid = !name.empty()
                          && !seller.empty()
                          && FieldFormat::parseMoneyField(priceField, price);
    if (!fieldsAreValid)
    {
        return false;
    }

    game = Game(name, seller, price);
    return true;
}

// getName
// Returns the game name.
std::string Game::getName() const
{
    return name;
}

// getSeller
// Returns the seller's username.
std::string Game::getSeller() const
{
    return seller;
}

// getPrice
// Returns the price in cents.
Cents Game::getPrice() const
{
    return price;
}

// wasListedThisSession
// True if the game was put up for sale this session.
bool Game::wasListedThisSession() const
{
    return listedThisSession;
}

// markListedThisSession
// Marks the game as a new listing for this session.
void Game::markListedThisSession()
{
    listedThisSession = true;
}
