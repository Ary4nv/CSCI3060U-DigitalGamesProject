#ifndef LOGINTRANSACTION_H
#define LOGINTRANSACTION_H

#include "Transaction.h"

// The login transaction. Loads the accounts file, asks for a username, loads
// the games file and starts the session.
class LoginTransaction : public Transaction {
public:
    // Makes a login transaction.
    LoginTransaction(Console& console, Session& session);
    // Logs a user in: refuses if someone is already logged in, loads the accounts
    // file, asks for the username, checks it exists, loads the games file and starts the session.
    virtual void execute();
    // Login can be used when nobody is logged in yet.
    virtual bool requiresLogin() const;

private:
    // Loads the accounts file into the session. Shows the right error and
    // returns false if the file is missing or not in the correct format.
    bool loadAccountsFile();
    // Loads the games file into the session. Shows the right error and
    // returns false if the file is missing or not in the correct format.
    bool loadGamesFile();
};

#endif
