// main.cpp
//
// What it does:
//   Starts the Digital Games Distribution Front End. The Front End reads
//   transactions (login, logout, create, delete, sell, buy, refund, addcredit,
//   list, listaccounts) one line at a time, checks each one against the rules,
//   prints a prompt, confirmation or error for each, and records every
//   successful transaction for the Back End. main only checks the command line
//   and hands control to FrontEnd; it contains no transaction logic.
//
// Input files:
//   standard input       - the transactions and answers typed by the user,
//                          one per line (can be redirected from a file)
//   user accounts file   - current accounts, read at each login (argument 1)
//   available games file - games for sale, read at each login (argument 2)
//
// Output files:
//   standard output          - prompts, confirmations, lists and error messages
//   standard error           - the usage message if the arguments are wrong
//   daily transaction file   - written at each logout, one line per successful
//                              transaction plus the 00 logout line (argument 3)
//
// How to run:
//   make
//   ./frontend accounts.txt games.txt daily.txt < input.txt

#include <iostream>
#include "FrontEnd.h"
#include "Session.h"

// main
// Checks there are exactly three file arguments, builds the file paths,
// then runs the Front End until the input ends. Returns 1 on a usage error.
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
                  << " <accounts_file> <games_file> <daily_transaction_file>" << std::endl;
        return 1;
    }

    FilePaths paths;
    paths.accountsFile = argv[1];
    paths.gamesFile = argv[2];
    paths.dailyFile = argv[3];

    FrontEnd frontEnd(paths, std::cin, std::cout);
    frontEnd.run();
    return 0;
}
