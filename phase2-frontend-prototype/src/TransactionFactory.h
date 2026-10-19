#ifndef TRANSACTIONFACTORY_H
#define TRANSACTIONFACTORY_H

#include <memory>
#include <string>
#include "Console.h"
#include "Session.h"
#include "Transaction.h"

// Turns the command the user typed into the matching Transaction object.
// This is the only place that knows which command word goes with which class.
class TransactionFactory {
public:
    // Keeps the console and session to hand to each transaction it makes.
    TransactionFactory(Console& console, Session& session);
    // Makes the transaction for this command word (case sensitive).
    // Returns an empty pointer if the word is not a transaction.
    std::unique_ptr<Transaction> create(const std::string& command);

private:
    Console& console;
    Session& session;
};

#endif
