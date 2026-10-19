#ifndef CREATETRANSACTION_H
#define CREATETRANSACTION_H

#include "Transaction.h"

// The create transaction (admin only). Makes a new account with 0 credit.
class CreateTransaction : public Transaction {
public:
    // Makes a create transaction.
    CreateTransaction(Console& console, Session& session);
    // Asks for the new username and account type, checks both, adds the
    // account with 0 credit and records a create (01) line.
    virtual void execute();
    // Only admins can create accounts.
    virtual bool isPermittedFor(const Account& user) const;
};

#endif
