#ifndef LOGOUTTRANSACTION_H
#define LOGOUTTRANSACTION_H

#include "Transaction.h"

// The logout transaction (every account type). Ends the session: adds the
// logout (00) line, writes the daily transaction file and logs the user out.
class LogoutTransaction : public Transaction {
public:
    // Makes a logout transaction.
    LogoutTransaction(Console& console, Session& session);
    // Ends the session with the user's final account state and prints
    // "Logout successful.", or an error if the daily file can't be written.
    virtual void execute();
};

#endif
