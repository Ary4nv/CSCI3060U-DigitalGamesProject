#include "SellTransaction.h"
#include "Constants.h"
#include "FieldFormat.h"
#include "Messages.h"

// Makes a sell transaction.
SellTransaction::SellTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Buy-standard accounts can't sell, everyone else can.
bool SellTransaction::isPermittedFor(const Account& user) const {
    return user.canSell();
}

// Asks for the game name and checks it (not blank, not END, not over 25
// characters, not already for sale). Returns false after showing an error.
bool SellTransaction::askForGameName(std::string& gameName) {
    if (!console.ask(Messages::GAME_NAME_PROMPT, gameName)) {
        return false;
    }
    if (isBlankOrEndMarker(gameName)) {
        console.showError(Messages::INVALID_GAME_NAME);
        return false;
    }
    if (gameName.size() > Constants::MAX_GAME_NAME_LENGTH) {
        console.showError(Messages::GAME_NAME_TOO_LONG);
        return false;
    }
    if (session.getGames().findByName(gameName) != NULL) {
        console.showError(Messages::GAME_ALREADY_FOR_SALE);
        return false;
    }
    return true;
}

// Asks for the price and checks it is a number that is not over 999.99.
// Returns false after showing an error.
bool SellTransaction::askForPrice(Cents& price) {
    std::string priceText;
    if (!console.ask(Messages::PRICE_PROMPT, priceText)) {
        return false;
    }
    if (!FieldFormat::parseMoney(priceText, price)) {
        console.showError(Messages::INVALID_PRICE);
        return false;
    }
    if (price > Constants::MAX_PRICE) {
        console.showError(Messages::PRICE_TOO_HIGH);
        return false;
    }
    return true;
}

// Gets a valid game name and price, adds the game to the catalog as a new
// listing for this session and records a sell (03) line.
void SellTransaction::execute() {
    std::string gameName;
    Cents price = 0;
    if (!askForGameName(gameName) || !askForPrice(price)) {
        return;
    }

    Game newGame(gameName, session.getCurrentUsername(), price);
    newGame.markListedThisSession();
    session.getGames().add(newGame);
    session.getLog().recordSell(gameName, session.getCurrentUsername(), price);
    console.show(Messages::GAME_PUT_UP_FOR_SALE);
}
