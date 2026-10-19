#ifndef BUYTRANSACTION_H
#define BUYTRANSACTION_H

#include "Transaction.h"

// The buy transaction (admin, full-standard, buy-standard). The logged in
// user buys a game from a seller. Credit moves from buyer to seller.
class BuyTransaction : public Transaction {
public:
    // Makes a buy transaction.
    BuyTransaction(Console& console, Session& session);
    // Asks for the game and the seller, checks the purchase is allowed and completes it.
    virtual void execute();
    // Sell-standard accounts can't buy, everyone else can.
    virtual bool isPermittedFor(const Account& user) const;

private:
    // Asks for the game name and finds it in the catalog.
    // Returns NULL after showing an error if there is no game with that name.
    Game* askForGameOnSale();
    // Asks for the seller's username and checks the seller has an account and
    // is the one selling this game. Returns NULL after showing an error otherwise.
    Account* askForSeller(const Game& game);
    // Checks all the rules for a purchase in order. Shows an error and returns
    // false for the first rule that is broken.
    bool buyerMayPurchase(const Game& game, const Account& buyer, const Account& seller);
    // Moves the price from the buyer to the seller, remembers the purchase and
    // records a buy (04) line. The game stays in the catalog.
    void completePurchase(const Game& game, Account& buyer, Account& seller);
};

#endif
