#ifndef LISTTRANSACTION_H
#define LISTTRANSACTION_H

#include "Transaction.h"

// The list transaction (every account type). Shows every game for sale.
// Read only, so nothing is added to the daily transaction file.
class ListTransaction : public Transaction {
public:
    // Makes a list transaction.
    ListTransaction(Console& console, Session& session);
    // Prints a heading and one "name | seller | price" line per game,
    // or a message saying no games are for sale.
    virtual void execute();
};

#endif
