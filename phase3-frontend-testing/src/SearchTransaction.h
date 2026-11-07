#ifndef SEARCHTRANSACTION_H
#define SEARCHTRANSACTION_H

#include <string>
#include "Account.h"
#include "Transaction.h"

// The search transaction (every account type). Asks for some text and shows
// the games whose name contains it, then the users whose username contains it.
// The match is case sensitive. Read only, so nothing is added to the daily
// transaction file.
class SearchTransaction : public Transaction {
public:
    // Makes a search transaction.
    SearchTransaction(Console& console, Session& session);
    // Asks for the search text and prints the matching games and users,
    // or a message saying nothing matched.
    virtual void execute();

private:
    // True if this account should show up in the results for the logged in user.
    // An admin with no game for sale is only shown to other admins.
    bool isVisible(const Account& account);
};

#endif
