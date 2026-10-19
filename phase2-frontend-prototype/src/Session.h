#ifndef SESSION_H
#define SESSION_H

#include <map>
#include <set>
#include <string>
#include <utility>
#include "Account.h"
#include "AccountRegistry.h"
#include "DailyTransactionLog.h"
#include "GameCatalog.h"

// The three file names given on the command line.
struct FilePaths {
    std::string accountsFile;
    std::string gamesFile;
    std::string dailyFile;
};

// Everything the front end knows while it runs: who is logged in, the
// accounts and games loaded for this session, the daily transaction lines,
// how much credit was added per account and which games were bought.
// Transactions get a Session and read or change it.
class Session {
public:
    // Starts with nobody logged in. Keeps the file names for later.
    Session(const FilePaths& filePaths);

    // Returns the three file names.
    const FilePaths& getFilePaths() const;
    // Returns the accounts for this session.
    AccountRegistry& getAccounts();
    // Returns the games for sale for this session.
    GameCatalog& getGames();
    // Returns the daily transaction lines collected so far.
    DailyTransactionLog& getLog();

    // True while someone is logged in.
    bool isLoggedIn() const;
    // Starts a new session for this user. The accounts and games must already be
    // loaded. Clears everything left from the last session.
    void begin(const std::string& username);
    // Returns the username of whoever is logged in.
    std::string getCurrentUsername() const;
    // Returns the logged in user's account, or NULL if nobody is logged in.
    Account* getCurrentUser();
    // Ends the session. Adds the final logout (00) line using the given account,
    // writes the daily transaction file and logs the user out.
    // The account is passed in because a user who deleted themselves is no longer in the registry.
    // Returns false if the daily file could not be written.
    bool end(const Account& finalAccountState);

    // Returns how much credit (in cents) was added to this account so far this session.
    Cents getCreditAddedThisSession(const std::string& username) const;
    // Adds to the total credit added to this account this session.
    void rememberCreditAdded(const std::string& username, Cents amount);

    // True if this buyer already bought this game earlier in the session.
    bool hasPurchased(const std::string& buyer, const std::string& gameName) const;
    // Remembers that this buyer bought this game.
    void rememberPurchase(const std::string& buyer, const std::string& gameName);

private:
    FilePaths filePaths;
    AccountRegistry accounts;
    GameCatalog games;
    DailyTransactionLog log;

    bool loggedIn;
    std::string currentUsername;
    std::map<std::string, Cents> creditAddedPerAccount;
    std::set<std::pair<std::string, std::string> > purchases;
};

#endif
