#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Account.h"
#include "Console.h"
#include "Session.h"

// Base class for every transaction (login, sell, buy, ...). A transaction
// says if it needs a login, which account types may use it, and does its
// job in execute(). It also has the small helpers that several
// transactions share, like asking for an amount or for an existing user.
class Transaction {
public:
    // Keeps the console and session so the transaction can use them.
    Transaction(Console& console, Session& session);
    // Needed so a transaction can be deleted through a Transaction pointer.
    virtual ~Transaction();

    // Does the whole transaction (prompts, checks, changes, daily file line). Each subclass fills this in.
    virtual void execute() = 0;
    // Most transactions need someone to be logged in. Login overrides this.
    virtual bool requiresLogin() const;
    // Most transactions are allowed for every account type. The restricted ones override this.
    virtual bool isPermittedFor(const Account& user) const;

protected:
    // True if the typed text is empty or is the END marker, neither can be a name.
    static bool isBlankOrEndMarker(const std::string& text);
    // Shows the prompt, reads a username and looks it up.
    // Returns the account, or NULL if the input ended or there is no such user (error already shown).
    Account* askForExistingAccount(const std::string& prompt);
    // Asks "Enter amount of credit:" and reads a money amount above zero.
    // Returns false if the input ended or the amount is not valid (error already shown).
    bool askForPositiveAmount(Cents& amount);

    Console& console;
    Session& session;
};

#endif
