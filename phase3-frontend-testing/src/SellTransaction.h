#ifndef SELLTRANSACTION_H
#define SELLTRANSACTION_H

#include "Transaction.h"

// The sell transaction (admin, full-standard, sell-standard). Puts a new
// game up for sale under the logged in user's name.
class SellTransaction : public Transaction {
public:
    // Makes a sell transaction.
    SellTransaction(Console& console, Session& session);
    // Gets a valid game name and price, adds the game to the catalog as a new
    // listing for this session and records a sell (03) line.
    virtual void execute();
    // Buy-standard accounts can't sell, everyone else can.
    virtual bool isPermittedFor(const Account& user) const;

private:
    // Asks for the game name and checks it (not blank, not END, not over 25
    // characters, not already for sale). Returns false after showing an error.
    bool askForGameName(std::string& gameName);
    // Asks for the price and checks it is a number that is not over 999.99.
    // Returns false after showing an error.
    bool askForPrice(Cents& price);
};

#endif
