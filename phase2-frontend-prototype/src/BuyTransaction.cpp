#include "BuyTransaction.h"
#include "Constants.h"
#include "Messages.h"

// Makes a buy transaction.
BuyTransaction::BuyTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Sell-standard accounts can't buy, everyone else can.
bool BuyTransaction::isPermittedFor(const Account& user) const {
    return user.canBuy();
}

// Asks for the game name and finds it in the catalog.
// Returns NULL after showing an error if there is no game with that name.
Game* BuyTransaction::askForGameOnSale() {
    std::string gameName;
    if (!console.ask(Messages::GAME_NAME_PROMPT, gameName)) {
        return NULL;
    }

    Game* game = session.getGames().findByName(gameName);
    if (game == NULL) {
        console.showError(Messages::GAME_NOT_FOUND);
    }
    return game;
}

// Asks for the seller's username and checks the seller has an account and
// is the one selling this game. Returns NULL after showing an error otherwise.
Account* BuyTransaction::askForSeller(const Game& game) {
    Account* seller = askForExistingAccount(Messages::SELLER_USERNAME_PROMPT);
    if (seller == NULL) {
        return NULL;
    }
    if (seller->getUsername() != game.getSeller()) {
        console.showError(Messages::SELLER_DOES_NOT_MATCH);
        return NULL;
    }
    return seller;
}

// Checks all the rules for a purchase in order. Shows an error and returns
// false for the first rule that is broken.
bool BuyTransaction::buyerMayPurchase(const Game& game, const Account& buyer, const Account& seller) {
    // a game that was just listed can't be bought in the same session
    if (game.wasListedThisSession()) {
        console.showError(Messages::GAME_NOT_AVAILABLE_THIS_SESSION);
        return false;
    }
    if (buyer.getUsername() == seller.getUsername()) {
        console.showError(Messages::CANNOT_BUY_OWN_GAME);
        return false;
    }
    if (session.hasPurchased(buyer.getUsername(), game.getName())) {
        console.showError(Messages::GAME_ALREADY_OWNED);
        return false;
    }
    if (buyer.getCredit() < game.getPrice()) {
        console.showError(Messages::NOT_ENOUGH_CREDIT);
        return false;
    }
    if (!seller.canReceive(game.getPrice())) {
        console.showError(Messages::SELLER_CREDIT_LIMIT_EXCEEDED);
        return false;
    }
    return true;
}

// Moves the price from the buyer to the seller, remembers the purchase and
// records a buy (04) line. The game stays in the catalog.
void BuyTransaction::completePurchase(const Game& game, Account& buyer, Account& seller) {
    // seller gets paid right away
    buyer.removeCredit(game.getPrice());
    seller.addCredit(game.getPrice());
    session.rememberPurchase(buyer.getUsername(), game.getName());
    session.getLog().recordBuy(game.getName(), seller.getUsername(), buyer.getUsername(),
                               game.getPrice());
    console.show(Messages::GAME_PURCHASED);
}

// Asks for the game and the seller, checks the purchase is allowed and completes it.
void BuyTransaction::execute() {
    Game* game = askForGameOnSale();
    if (game == NULL) {
        return;
    }
    Account* seller = askForSeller(*game);
    if (seller == NULL) {
        return;
    }

    // the buyer is whoever is logged in
    Account* buyer = session.getCurrentUser();
    if (buyerMayPurchase(*game, *buyer, *seller)) {
        completePurchase(*game, *buyer, *seller);
    }
}
