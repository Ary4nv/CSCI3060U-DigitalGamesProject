#ifndef DAILYTRANSACTIONLOG_H
#define DAILYTRANSACTIONLOG_H

#include <string>
#include <vector>
#include "Constants.h"

// Collects the lines of the daily transaction file while a session runs.
// Only finished transactions are added, failed ones never are. The lines are
// written to the file when the session ends.
class DailyTransactionLog {
public:
    // Forgets all the lines, used when a new session starts.
    void clear();
    // Adds a line for the transactions that look like an account line:
    // logout (00), create (01), delete (02) and addcredit (06).
    // For addcredit the amount is the credit that was added, for the others it is the account's credit.
    void recordAccountLine(const std::string& code, const std::string& username,
                           const std::string& accountType, Cents amount);
    // Adds a sell (03) line: game name, seller and price.
    void recordSell(const std::string& gameName, const std::string& seller, Cents price);
    // Adds a buy (04) line: game name, seller, buyer and price.
    void recordBuy(const std::string& gameName, const std::string& seller,
                   const std::string& buyer, Cents price);
    // Adds a refund (05) line: buyer, seller and the amount refunded.
    void recordRefund(const std::string& buyer, const std::string& seller, Cents amount);
    // Writes all the lines to the daily transaction file, replacing what was in it.
    // Returns false if the file can't be written.
    bool writeToFile(const std::string& path) const;

private:
    std::vector<std::string> lines;
};

#endif
