#ifndef LISTACCOUNTSTRANSACTION_H
#define LISTACCOUNTSTRANSACTION_H

#include "Transaction.h"

// The listaccounts transaction (admin only). Shows every active account.
// Read only, so nothing is added to the daily transaction file.
// The command name "listaccounts" is provisional until the client confirms it.
class ListAccountsTransaction : public Transaction {
public:
    // Makes a listaccounts transaction.
    ListAccountsTransaction(Console& console, Session& session);
    // Prints a heading and one "username | type | credit" line per account.
    virtual void execute();
    // Only admins can list accounts.
    virtual bool isPermittedFor(const Account& user) const;
};

#endif
