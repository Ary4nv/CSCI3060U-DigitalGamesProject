#ifndef FRONTEND_H
#define FRONTEND_H

#include <iostream>
#include "Console.h"
#include "Session.h"
#include "TransactionFactory.h"

// The main controller. Keeps asking for transactions until the input ends,
// and for each one checks the user is logged in and allowed to use it
// before running it.
class FrontEnd {
public:
    // Sets up the console, the session and the factory that makes transactions.
    FrontEnd(const FilePaths& filePaths, std::istream& input, std::ostream& output);
    // Main loop: prints "Enter transaction:", reads a command and handles it,
    // until there is no more input.
    void run();

private:
    // Handles one command. Unknown words are invalid, known ones need a login
    // (except login itself), and the logged in account type must be allowed to use it.
    void handleCommand(const std::string& command);

    Console console;
    Session session;
    TransactionFactory factory;
};

#endif
