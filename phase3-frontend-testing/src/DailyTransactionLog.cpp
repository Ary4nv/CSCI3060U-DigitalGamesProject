#include "DailyTransactionLog.h"
#include "FieldFormat.h"

#include <fstream>

// Forgets all the lines, used when a new session starts.
void DailyTransactionLog::clear() {
    lines.clear();
}

// Adds a line for the transactions that look like an account line:
// logout (00), create (01), delete (02) and addcredit (06).
// For addcredit the amount is the credit that was added, for the others it is the account's credit.
void DailyTransactionLog::recordAccountLine(const std::string& code, const std::string& username,
                                            const std::string& accountType, Cents amount) {
    lines.push_back(code + " " + FieldFormat::padRight(username, Constants::MAX_USERNAME_LENGTH)
                    + " " + accountType + " "
                    + FieldFormat::moneyField(amount, Constants::CREDIT_FIELD_WIDTH));
}

// Adds a sell (03) line: game name, seller and price.
void DailyTransactionLog::recordSell(const std::string& gameName, const std::string& seller,
                                     Cents price) {
    lines.push_back(Constants::SELL_CODE + " "
                    + FieldFormat::padRight(gameName, Constants::MAX_GAME_NAME_LENGTH) + " "
                    + FieldFormat::padRight(seller, Constants::MAX_USERNAME_LENGTH) + " "
                    + FieldFormat::moneyField(price, Constants::PRICE_FIELD_WIDTH));
}

// Adds a buy (04) line: game name, seller, buyer and price.
void DailyTransactionLog::recordBuy(const std::string& gameName, const std::string& seller,
                                    const std::string& buyer, Cents price) {
    lines.push_back(Constants::BUY_CODE + " "
                    + FieldFormat::padRight(gameName, Constants::MAX_GAME_NAME_LENGTH) + " "
                    + FieldFormat::padRight(seller, Constants::MAX_USERNAME_LENGTH) + " "
                    + FieldFormat::padRight(buyer, Constants::MAX_USERNAME_LENGTH) + " "
                    + FieldFormat::moneyField(price, Constants::PRICE_FIELD_WIDTH));
}

// Adds a refund (05) line: buyer, seller and the amount refunded.
void DailyTransactionLog::recordRefund(const std::string& buyer, const std::string& seller,
                                       Cents amount) {
    lines.push_back(Constants::REFUND_CODE + " "
                    + FieldFormat::padRight(buyer, Constants::MAX_USERNAME_LENGTH) + " "
                    + FieldFormat::padRight(seller, Constants::MAX_USERNAME_LENGTH) + " "
                    + FieldFormat::moneyField(amount, Constants::CREDIT_FIELD_WIDTH));
}

// Writes all the lines to the daily transaction file, replacing what was in it.
// Returns false if the file can't be written.
bool DailyTransactionLog::writeToFile(const std::string& path) const {
    std::ofstream file(path.c_str());
    if (!file.is_open()) {
        return false;
    }
    for (std::size_t i = 0; i < lines.size(); i++) {
        file << lines[i] << "\n";
    }
    return file.good();
}
