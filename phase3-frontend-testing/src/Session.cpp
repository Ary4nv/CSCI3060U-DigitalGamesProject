#include "Session.h"
#include "Constants.h"

// Starts with nobody logged in. Keeps the file names for later.
Session::Session(const FilePaths& newFilePaths)
    : filePaths(newFilePaths), loggedIn(false), currentUsername("") {
}

// Returns the four file names.
const FilePaths& Session::getFilePaths() const {
    return filePaths;
}

// Returns the accounts for this session.
AccountRegistry& Session::getAccounts() {
    return accounts;
}

// Returns the games for sale for this session.
GameCatalog& Session::getGames() {
    return games;
}

// Returns the daily transaction lines collected so far.
DailyTransactionLog& Session::getLog() {
    return log;
}

// True while someone is logged in.
bool Session::isLoggedIn() const {
    return loggedIn;
}

// Starts a new session for this user. The accounts and games must already be
// loaded. Clears everything left from the last session.
void Session::begin(const std::string& username) {
    loggedIn = true;
    currentUsername = username;
    log.clear();
    creditAddedPerAccount.clear();
    purchases.clear();
}

// Returns the username of whoever is logged in.
std::string Session::getCurrentUsername() const {
    return currentUsername;
}

// Returns the logged in user's account, or NULL if nobody is logged in.
Account* Session::getCurrentUser() {
    if (!loggedIn) {
        return NULL;
    }
    return accounts.find(currentUsername);
}

// Ends the session. Adds the final logout (00) line using the given account,
// writes the daily transaction file and logs the user out.
// The account is passed in because a user who deleted themselves is no longer in the registry.
// Returns false if the daily file could not be written.
bool Session::end(const Account& finalAccountState) {
    log.recordAccountLine(Constants::LOGOUT_CODE, finalAccountState.getUsername(),
                          finalAccountState.getType(), finalAccountState.getCredit());
    // the 00 line always goes last
    bool written = log.writeToFile(filePaths.dailyFile);
    loggedIn = false;
    currentUsername = "";
    return written;
}

// Returns how much credit (in cents) was added to this account so far this session.
Cents Session::getCreditAddedThisSession(const std::string& username) const {
    std::map<std::string, Cents>::const_iterator found = creditAddedPerAccount.find(username);
    if (found == creditAddedPerAccount.end()) {
        return 0;
    }
    return found->second;
}

// Adds to the total credit added to this account this session.
void Session::rememberCreditAdded(const std::string& username, Cents amount) {
    creditAddedPerAccount[username] += amount;
}

// True if this buyer already bought this game earlier in the session.
bool Session::hasPurchased(const std::string& buyer, const std::string& gameName) const {
    return purchases.count(std::make_pair(buyer, gameName)) > 0;
}

// Remembers that this buyer bought this game.
void Session::rememberPurchase(const std::string& buyer, const std::string& gameName) {
    purchases.insert(std::make_pair(buyer, gameName));
}
