#ifndef ADDCREDITTRANSACTION_H
#define ADDCREDITTRANSACTION_H

#include "Transaction.h"

// The addcredit transaction (all account types). Standard users add credit to
// their own account, admins also pick which account. No account can get more
// than 1000.00 added in one session.
class AddCreditTransaction : public Transaction {
public:
    // Makes an addcredit transaction.
    AddCreditTransaction(Console& console, Session& session);
    // Asks for the amount (and the username for admins), checks the limits, adds the
    // credit and records an addcredit (06) line with the amount that was added.
    virtual void execute();

private:
    // Admins are asked which account gets the credit, everyone else only adds to
    // their own. Returns NULL if the admin's answer is not an existing user (error already shown).
    Account* askForTargetAccount();
    // Checks the account wouldn't go over the maximum credit or over the session
    // limit. Shows an error and returns false if it would.
    bool amountIsAllowed(const Account& target, Cents amount);
};

#endif
