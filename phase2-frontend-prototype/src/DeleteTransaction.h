#ifndef DELETETRANSACTION_H
#define DELETETRANSACTION_H

#include "Transaction.h"

// The delete transaction (admin only). Removes an account. An admin may
// delete their own account, which ends the session right away.
class DeleteTransaction : public Transaction {
public:
    // Makes a delete transaction.
    DeleteTransaction(Console& console, Session& session);
    // Asks for the username, removes that account and records a delete (02)
    // line. If the admin deleted themselves, the session ends with no
    // "Logout successful." message.
    virtual void execute();
    // Only admins can delete accounts.
    virtual bool isPermittedFor(const Account& user) const;
};

#endif
